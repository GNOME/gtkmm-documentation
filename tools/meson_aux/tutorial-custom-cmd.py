#!/usr/bin/env python3

# External command, intended to be called with custom_target() in meson.build

#                           argv[1]   argv[2:]
# tutorial-custom-cmd.py <subcommand> <xxx>...

import os
import sys
import subprocess
import shutil

subcommand = sys.argv[1]

def insert_ex_code():
  #     argv[2]          argv[3]            argv[4]          argv[5]
  # <py_script_dir> <examples_book_dir> <input_xml_file> <output_xml_file>

  # Search for insert_example_code.py first in <py_script_dir>.
  sys.path.insert(0, sys.argv[2])
  from insert_example_code import insert_example_code

  examples_book_dir = sys.argv[3]
  input_xml_file = sys.argv[4]
  output_xml_file = sys.argv[5]

  returncode = insert_example_code(examples_book_dir, input_xml_file, output_xml_file)
  if returncode:
    return returncode

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
    '--param', 'admon.graphics', '1',
    '--stringparam', 'admon.graphics.path', 'icons/',
    '--stringparam', 'admon.graphics.extension', '.png',
    '--stringparam', 'chunker.output.indent', 'yes',
    '--stringparam', 'chunker.output.encoding', 'UTF-8',
    '--param', 'navig.graphics', '1',
    '--stringparam', 'navig.graphics.extension', '.png',
    '--stringparam', 'navig.graphics.path', 'icons/',
    '--stringparam', 'toc.list.type', 'ul',
    '--param', 'use.id.as.filename', '1',
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
    '--nonet',
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
  from pathlib import Path

  #  argv[2]       argv[3]          argv[4]
  # <validate> <input_xml_file> <stamp_file_path>

  validate = sys.argv[2]
  input_xml_file = sys.argv[3]
  stamp_file_path = sys.argv[4]

  relax_ng_schema = 'http://docbook.org/xml/5.0/rng/docbook.rng'
  # schematron_schema = 'http://docbook.org/xml/5.0/sch/docbook.sch'

  # Validation against the Schematron schema does not work on Ubuntu 21.04:
  # file:///usr/share/xml/docbook/schema/schematron/5.0/docbook.sch:6: element rule:
  #   Schemas parser error : Failed to compile context expression db:firstterm[@linkend]
  # .....
  # Schematron schema http://docbook.org/xml/5.0/sch/docbook.sch failed to compile

  cmd = [
    'xmllint',
    '--noout',
    '--noent',
    '--xinclude',
  ]
  if validate == 'true':
    cmd += [
      '--relaxng', relax_ng_schema,
      #'--schematron', schematron_schema,
    ]
  cmd += [input_xml_file]
  result = subprocess.run(cmd)
  if result.returncode:
    return result.returncode

  Path(stamp_file_path).touch(exist_ok=True)
  return 0

# dblatex and xsltproc+fop generate a PDF file.
# docbook2pdf can generate PDF files from DocBook4 files, but not from DocBook5 files.
# xsltproc+xmlroff (version 0.6.3) does not seem to work acceptably.
def dblatex():
  #      argv[2]        argv[3]        argv[4]
  # <input_xml_file> <figures_dir> <output_pdf_file>
  # Create a PDF file, using dblatex.

  input_xml_file = sys.argv[2]
  figures_dir = sys.argv[3]
  output_pdf_file = sys.argv[4]

  # For a list of available parameters, see http://dblatex.sourceforge.net/doc/manual/
  dblatex_params = [
    '-P', 'toc.section.depth=1',
    '-P', 'paper.type=a4paper',
    '-P', 'doc.collab.show=1',
    '-P', 'latex.output.revhistory=0',
  ]
  figures_dir_parent = os.path.dirname(figures_dir)

  cmd = [
    'dblatex',
  ] + dblatex_params + [
    '-I', figures_dir_parent,
    '-o', output_pdf_file,
    '--pdf',
    input_xml_file,
  ]
  return subprocess.run(cmd).returncode

def fop():
  #      argv[2]        argv[3]        argv[4]
  # <input_xml_file> <figures_dir> <output_pdf_file>
  # Create a PDF file, using fop.

  input_xml_file = sys.argv[2]
  figures_dir = sys.argv[3]
  output_pdf_file = sys.argv[4]

  fo_file = os.path.splitext(output_pdf_file)[0] + '.fo'

  figures_dir_parent = os.path.dirname(figures_dir)
  if figures_dir_parent:
    figures_dir_parent += '/'

  # For a list of available parameters, see http://docbook.sourceforge.net/release/xsl/current/doc/fo/
  # For a list of available paper types, see the description of the page.width.portrait parameter.
  xslt_params = [
    '--param', 'toc.section.depth', '1',
    '--stringparam', 'fop1.extensions', '1',
    '--stringparam', 'page.orientation', 'portrait',
    '--stringparam', 'paper.type', 'A4',
    '--param', 'keep.relative.image.uris', '1',
    '--stringparam', 'img.src.path', figures_dir_parent,
  ]

  xslt_stylesheet = 'http://docbook.sourceforge.net/release/xsl/current/fo/docbook.xsl'

  # Generate a .fo (formatting object) file.
  # fop can take an xslt stylesheet parameter, but it can only read local files.
  # xsltproc is necessary if you want to read the stylesheet from the internet.
  cmd = [
    'xsltproc',
  ] + xslt_params + [
    '-o', fo_file,
    '--xinclude',
    '--nonet',
    xslt_stylesheet,
    input_xml_file,
  ]
  result = subprocess.run(cmd)
  if result.returncode:
    return result.returncode

  cmd = [
    'fop',
    '-fo', fo_file,
    '-pdf', output_pdf_file,
  ]
  return subprocess.run(cmd).returncode

# ----- Main -----
if subcommand == 'insert_example_code':
  sys.exit(insert_ex_code())
if subcommand == 'html':
  sys.exit(html())
if subcommand == 'xmllint':
  sys.exit(xmllint())
if subcommand == 'dblatex':
  sys.exit(dblatex())
if subcommand == 'fop':
  sys.exit(fop())
print(sys.argv[0], ': illegal subcommand,', subcommand)
sys.exit(1)
