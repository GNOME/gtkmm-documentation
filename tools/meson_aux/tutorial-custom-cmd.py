#!/usr/bin/env python3

# External command, intended to be called with custom_target() in meson.build

#                           argv[1]   argv[2:]
# tutorial-custom-cmd.py <subcommand> <xxx>...

import os
import sys
import subprocess
from pathlib import Path
import shutil

subcommand = sys.argv[1]

def insert_example_code():
  #      argv[2]            argv[3]             argv[4]         argv[5]
  # <perl_script_file> <examples_book_dir> <input_xml_file> <output_xml_file>

  perl_script_file = sys.argv[2]
  examples_book_dir = sys.argv[3]
  input_xml_file = sys.argv[4]
  output_xml_file = sys.argv[5]

  cmd = [
    'perl',
    '--',
    perl_script_file,
    examples_book_dir,
    input_xml_file,
  ]
  with open(output_xml_file, mode='w') as xml_file:
    result = subprocess.run(cmd, stdout=xml_file)
    if result.returncode:
      return result.returncode

  # Copy output_xml_file to the source directory.
  shutil.copy(output_xml_file, os.path.dirname(input_xml_file))
  return 0

def html():
  #      argv[2]          argv[3]
  # <input_xml_file> <output_html_dir>

  input_xml_file = sys.argv[2]
  output_html_dir = sys.argv[3]

  # Set the use.id.as.filename param so that we don't use the chapter / section
  # number as the filename, otherwise the url will change every time anything is
  # re-ordered or inserted in the documentation.
  # For a list of available parameters, see http://docbook.sourceforge.net/release/xsl/current/doc/html/
  xslt_params = [
    '--param', 'toc.section.depth', '1',
    '--stringparam', 'html.stylesheet', 'style.css',
    '--stringparam', 'admon.graphics', '1',
    '--stringparam', 'admon.graphics.path', 'icons/',
    '--stringparam', 'admon.graphics.extension', '.png',
    '--stringparam', 'chunker.output.indent', 'yes',
    '--stringparam', 'chunker.output.encoding', 'UTF-8',
    '--stringparam', 'navig.graphics', 'yes',
    '--stringparam', 'navig.graphics.extension', '.png',
    '--stringparam', 'navig.graphics.path', 'icons/',
    '--stringparam', 'toc.list.type', 'ul',
    '--stringparam', 'use.id.as.filename', '1',
  ]
  xslt_stylesheet = 'http://docbook.sourceforge.net/release/xsl/current/html/chunk.xsl'

  # Remove old files and create the destination directory.
  shutil.rmtree(output_html_dir, ignore_errors=True)
  os.makedirs(output_html_dir, exist_ok=True)

  cmd = [
    'xsltproc',
  ] + xslt_params + [
    '-o', output_html_dir + '/',
    '--xinclude',
    xslt_stylesheet,
    input_xml_file,
  ]
  result = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                          universal_newlines=True)
  # xsltproc prints the names of all written files. Don't print those lines.
  for line in result.stdout.splitlines():
    if not line.startswith('Writing '):
      print(line)

  return result.returncode

def xmllint():
  #  argv[2]       argv[3]          argv[4]
  # <validate> <input_xml_file> <stamp_file_path>

  validate = sys.argv[2]
  input_xml_file = sys.argv[3]
  stamp_file_path = sys.argv[4]

  cmd = [
    'xmllint',
    '--noout',
    '--noent',
    '--xinclude',
  ]
  if validate == 'true':
    cmd += ['--postvalid']
  cmd += [input_xml_file]
  result = subprocess.run(cmd)
  if result.returncode:
    return result.returncode

  Path(stamp_file_path).touch(exist_ok=True)
  return 0

def dblatex():
  #      argv[2]        argv[3]        argv[4]
  # <input_xml_file> <figures_dir> <output_pdf_file>
  # Create a PDF file, using dblatex.

  input_xml_file = sys.argv[2]
  figures_dir = sys.argv[3]
  output_pdf_file = sys.argv[4]

  # For a list of available parameters, see http://dblatex.sourceforge.net/doc/manual/
  dblatex_params = [
    '-P', 'toc.section.depth=2',
    '-P', 'paper.type=a4paper',
  ]
  figures_dir_parent = os.path.dirname(figures_dir)

  cmd = [
    'dblatex',
  ] + dblatex_params + [
    '-I', figures_dir_parent,
    '-o', output_pdf_file,
    '--pdf', input_xml_file,
  ]
  return subprocess.run(cmd).returncode

def docbook2pdf():
  #      argv[2]        argv[3]        argv[4]
  # <input_xml_file> <figures_dir> <output_pdf_file>
  # Create a PDF file, using docbook2pdf.

  input_xml_file = sys.argv[2]
  figures_dir = sys.argv[3]
  output_pdf_file = sys.argv[4]

  output_dir = os.path.dirname(output_pdf_file)
  if not output_dir:
    output_dir = '.'
  output_basename = os.path.basename(output_pdf_file)
  if output_basename.endswith('.pdf'):
    output_basename = output_basename[:-4]
  xml_file = os.path.join(output_dir, output_basename + '.xml')

  # We need to produce a full examples XML with all of the XIncludes done.
  cmd = [
    'xmllint',
    '--xinclude',
    '--postvalid',
    '--output', xml_file,
    input_xml_file,
  ]
  result = subprocess.run(cmd)
  if result.returncode:
    return result.returncode

  # We also need to copy the figures from the source directory, so they
  # can be found from the XML file.
  # By default, shutil.copytree() copies files with shutil.copy2(),
  # which copies timestamps and some other file metadata.
  # The destination directory must not exist when shutil.copytree() is called.
  output_figures_dir = os.path.join(output_dir, os.path.basename(figures_dir))
  shutil.rmtree(output_figures_dir, ignore_errors=True)
  shutil.copytree(figures_dir, output_figures_dir)

  cmd = [
    'docbook2pdf',
    '--output', output_dir,
    xml_file,
  ]
  return subprocess.run(cmd).returncode

# ----- Main -----
if subcommand == 'insert_example_code':
  sys.exit(insert_example_code())
if subcommand == 'html':
  sys.exit(html())
if subcommand == 'xmllint':
  sys.exit(xmllint())
if subcommand == 'dblatex':
  sys.exit(dblatex())
if subcommand == 'docbook2pdf':
  sys.exit(docbook2pdf())
print(sys.argv[0], ': illegal subcommand,', subcommand)
sys.exit(1)
