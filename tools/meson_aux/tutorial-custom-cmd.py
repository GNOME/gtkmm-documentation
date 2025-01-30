#!/usr/bin/env python3

# External command, intended to be called in meson.build

#                           argv[1]   argv[2:]
# tutorial-custom-cmd.py <subcommand> <xxx>...

import os
import sys
import subprocess
import shutil
from pathlib import Path

subcommand = sys.argv[1]

# Called from run_command()
def get_languages():
  #   argv[2]
  # <input_dir>

  input_dir = sys.argv[2]

  # Syntax of the LINGUAS file is documented here:
  # https://www.gnu.org/software/gettext/manual/html_node/po_002fLINGUAS.html
  linguas_file = os.path.join(input_dir, 'LINGUAS')
  try:
    with open(linguas_file, encoding='utf-8') as f:
      for line in f:
        line = line.strip()
        if line and not line.startswith('#'):
          print(line, end=' ')
  except (FileNotFoundError, PermissionError):
    print('Could not find file LINGUAS in', input_dir, file=sys.stderr)
    return 1
  return 0

# Called from custom_target()
def insert_ex_code():
  #     argv[2]          argv[3]            argv[4]          argv[5]
  # <py_script_dir> <examples_book_dir> <input_xml_file> <output_xml_file>

  # Search for insert_example_code.py first in <py_script_dir>.
  sys.path.insert(0, sys.argv[2])
  from insert_example_code import insert_example_code

  examples_book_dir = sys.argv[3]
  input_xml_file = sys.argv[4]
  output_xml_file = sys.argv[5]

  return insert_example_code(examples_book_dir, input_xml_file, output_xml_file)

# Called from custom_target()
def html():
  #      argv[2]               argv[3]           argv[4]          argv[5]
  # <allow_network_access> <input_xsl_file> <input_xml_file> <output_html_dir>

  allow_network_access = sys.argv[2] == 'true'
  input_xsl_file = sys.argv[3]
  input_xml_file = sys.argv[4]
  output_html_dir = sys.argv[5]

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

  # Remove old files and create the destination directory.
  shutil.rmtree(output_html_dir, ignore_errors=True)
  os.makedirs(output_html_dir, exist_ok=True)

  cmd = [
    'xsltproc',
  ] + xslt_params + [
    '-o', output_html_dir + '/',
    '--xinclude',
  ]
  if not allow_network_access:
    cmd += ['--nonet']
  cmd += [
    input_xsl_file,
    input_xml_file,
  ]
  result = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                          universal_newlines=True)
  # xsltproc prints the names of all written files. Don't print those lines.
  for line in result.stdout.splitlines():
    if not line.startswith('Writing '):
      print(line)

  return result.returncode

# Called from custom_target()
def copy_files():
  #   argv[2]       argv[3]              argv[4:]
  # <input_dir> <stamp_file_path> <files_and_output_dirs>...

  # Each element in files_and_output_dirs is either an absolute path
  # to an output directory, which may or may not exist,
  # or a relative path to an input file, relative to input_dir.
  # The first element must be an output directory.

  input_dir = sys.argv[2]
  stamp_file_path = sys.argv[3]
  files_and_output_dirs = sys.argv[4:]
  output_dir = ''

  for f in files_and_output_dirs:
    if os.path.isabs(f):
      # It's an output directory.
      output_dir = f
      # Create the destination directory, if it does not exist.
      os.makedirs(output_dir, exist_ok=True)
    else:
      input_path = os.path.join(input_dir, f)
      output_path = os.path.join(output_dir, os.path.basename(f))
      if os.path.isfile(input_path):
        # shutil.copy2() copies timestamps and some other file metadata.
        shutil.copy2(input_path, output_path)
      else:
        # Ignore non-existent files.
        print(input_path, 'not found, not copied.')

  Path(stamp_file_path).touch(exist_ok=True)
  return 0

# Called from custom_target()
def xmllint():

  #  argv[2]          argv[3]              argv[4]          argv[5]
  # <validate> <allow_network_access> <input_xml_file> <stamp_file_path>

  validate = sys.argv[2]
  allow_network_access = sys.argv[3] == 'true'
  input_xml_file = sys.argv[4]
  stamp_file_path = sys.argv[5]

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
  if not allow_network_access:
    cmd += ['--nonet']
  cmd += [input_xml_file]
  result = subprocess.run(cmd)
  if result.returncode:
    return result.returncode

  Path(stamp_file_path).touch(exist_ok=True)
  return 0

# Called from custom_target()
def translate_xml():
  #      argv[2]         argv[3]          argv[4]          argv[5]
  # <input_po_file> <input_xml_file> <output_xml_dir> <stamp_file_path>

  input_po_file = sys.argv[2]
  input_xml_file = sys.argv[3]
  output_xml_dir = sys.argv[4] # Absolute path
  stamp_file_path = sys.argv[5]
  input_xml_dir, input_xml_basename = os.path.split(input_xml_file)

  # Create the destination directory, if it does not exist.
  os.makedirs(output_xml_dir, exist_ok=True)

  # Create an .mo file.
  language = os.path.splitext(os.path.basename(input_po_file))[0]
  mo_file = os.path.join(output_xml_dir, language + '.mo')
  cmd = [
    'msgfmt',
    '-o', mo_file,
    input_po_file,
  ]
  result = subprocess.run(cmd)
  if result.returncode:
    return result.returncode

  # Create translated XML files.
  cmd = [
    'itstool',
    '-m', mo_file,
    '-o', output_xml_dir,
  ] + [input_xml_basename]
  result = subprocess.run(cmd, cwd=input_xml_dir)
  if result.returncode:
    return result.returncode

  Path(stamp_file_path).touch(exist_ok=True)
  return 0

# dblatex and xsltproc+fop generate a PDF file.
# docbook2pdf can generate PDF files from DocBook4 files, but not from DocBook5 files.
# xsltproc+xmlroff (version 0.6.3) does not seem to work acceptably.
# Called from custom_target()
def dblatex():
  #        argv[2]              argv[3]        argv[4]         argv[5]
  # <allow_network_access> <input_xml_file> <figures_dir> <output_pdf_file>
  # Create a PDF file, using dblatex.

  allow_network_access = sys.argv[2] == 'true'
  input_xml_file = sys.argv[3]
  figures_dir = sys.argv[4]
  output_pdf_file = sys.argv[5]

  # For a list of available parameters, see http://dblatex.sourceforge.net/doc/manual/
  dblatex_params = [
    '-P', 'toc.section.depth=1',
    '-P', 'paper.type=a4paper',
    '-P', 'doc.collab.show=1',
    '-P', 'output.quietly=1',
    '-P', 'latex.output.revhistory=0',
  ]
  figures_dir_parent = os.path.dirname(figures_dir)

  cmd = [
    'dblatex',
  ] + dblatex_params + [
    '-I', figures_dir_parent,
    '-o', output_pdf_file,
    '--pdf',
  ]
  if not allow_network_access:
    cmd += ['-x', '--nonet'] # --nonet is passed to xsltproc
  cmd += [
    input_xml_file,
  ]
  return subprocess.run(cmd).returncode

# Called from custom_target()
def fop():
  #         argv[2]            argv[3]         argv[4]         argv[5]
  # <allow_network_access> <input_xml_file> <figures_dir> <output_pdf_file>
  # Create a PDF file, using fop.

  allow_network_access = sys.argv[2] == 'true'
  input_xml_file = sys.argv[3]
  figures_dir = sys.argv[4]
  output_pdf_file = sys.argv[5]

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
  ]
  if not allow_network_access:
    cmd += ['--nonet']
  cmd += [
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

# Called from meson.add_install_script()
def install():
  #      argv[2]           argv[3]              argv[4]         argv[5]       argv[6:]
  # <input_xml_dir> <rel_install_xml_dir> <input_xml_file> <symlink_src_dir> <figures>...

  # <rel_install_xml_dir> is the installation directory, relative to {prefix}.
  input_xml_dir = sys.argv[2]
  rel_install_xml_dir = sys.argv[3]
  input_xml_file =  sys.argv[4]
  symlink_src_dir = sys.argv[5]
  figures = sys.argv[6:]
  destdir_xmldir = os.path.join(os.getenv('MESON_INSTALL_DESTDIR_PREFIX'), rel_install_xml_dir)
  symlink_dest_dir = os.path.join(destdir_xmldir, 'figures')

  # Create the installation directory, if it does not exist.
  os.makedirs(symlink_dest_dir, exist_ok=True)

  quiet = bool(os.getenv('MESON_INSTALL_QUIET'))
  input_xml_path = os.path.join(input_xml_dir, input_xml_file)
  if not quiet:
    print('Installing ', input_xml_path, ' to ', destdir_xmldir)
  # shutil.copy2() copies timestamps and some other file metadata.
  shutil.copy2(input_xml_path, destdir_xmldir)

  # Create symlinks from figure files in destdir_xmldir to the C locale's
  # figure files.
  if not quiet:
    print('Installing symlinks pointing to ', symlink_src_dir, ' to ', symlink_dest_dir)
  for f in figures:
    symlink_dest_file = os.path.join(symlink_dest_dir, f)
    if os.path.lexists(symlink_dest_file):
      os.remove(symlink_dest_file)
    os.symlink(os.path.join(symlink_src_dir, f), symlink_dest_file)
  return 0

# ----- Main -----
if subcommand == 'get_languages':
  sys.exit(get_languages())
if subcommand == 'insert_example_code':
  sys.exit(insert_ex_code())
if subcommand == 'html':
  sys.exit(html())
if subcommand == 'copy_files':
  sys.exit(copy_files())
if subcommand == 'xmllint':
  sys.exit(xmllint())
if subcommand == 'translate_xml':
  sys.exit(translate_xml())
if subcommand == 'dblatex':
  sys.exit(dblatex())
if subcommand == 'fop':
  sys.exit(fop())
if subcommand == 'install':
  sys.exit(install())
print(sys.argv[0], ': illegal subcommand,', subcommand)
sys.exit(1)
