#!/usr/bin/env python3

# Generate screenshots for the gtkmm tutorial.
#
# This Python script starts one or more programs, one at a time. The started
# programs are assumed to open a window. The script catches a screenshot of
# each started program's window.
# The script can't correctly generate screenshots that require some kind of
# user input before or after the program has been started.
#
# Which programs to start and where to save the screenshots is read from a
# file, where each line contains
#   program [parameter-to-program...] figure [delay-in-seconds] [# comment]
# Lines that don't contain both 'program' and 'figure' are ignored.

# The screenshots are saved by gnome-screenshot.

# make_screenshots.py [option...] [input-file]
# Options:
# --program-src-prefix=SRCDIR      Default: $GMMPROC_GEN_SOURCE_DIR/gtkmm-documentation/examples or ../../examples
# --program-build-prefix=BUILDDIR  Default: $GMMPROC_GEN_BUILD_DIR/gtkmm-documentation/examples or SRCDIR
# --figure-dir=FIGUREDIR           Default: newfigures
# input-file                       Default: progs-and-figs.txt

# When the default values of SRCDIR and BUILDDIR are computed, it's assumed that
# this script is stored two directory levels below gtkmm-documentation, e.g.
# in gtkmm-documentation/tools/make_screenshots/.
# 'gtkmm-documentation' is just a typical directory name. Other directory names
# are possible.

import os
import sys
import argparse
import time
import signal
import subprocess

# Compute default values of SRCDIR and BUILDDIR.
pkg_dir = os.path.abspath(sys.argv[0])
for i in range(3):
  pkg_dir = os.path.dirname(pkg_dir)
pkg_name = os.path.basename(pkg_dir)
if not pkg_name:
  pkg_name = 'gtkmm-documentation'

gmmproc_gen_source_dir = os.environ.get('GMMPROC_GEN_SOURCE_DIR', None)
if gmmproc_gen_source_dir:
  src_default = os.path.join(gmmproc_gen_source_dir, pkg_name, 'examples')
else: 
  src_default = os.path.join(pkg_dir, 'examples')

gmmproc_gen_build_dir = os.environ.get('GMMPROC_GEN_BUILD_DIR', None)
if gmmproc_gen_build_dir:
  build_default = os.path.join(gmmproc_gen_build_dir, pkg_name, 'examples')
else: 
  build_default = gmmproc_gen_source_dir

parser = argparse.ArgumentParser(
  formatter_class=argparse.RawTextHelpFormatter,
  description='Make screenshots for the gtkmm tutorial.')
parser.add_argument('--program-src-prefix', metavar='SRCDIR',
  dest='src_prefix', default=src_default,
  help='source directory prefix (default: %(default)s)')
parser.add_argument('--program-build-prefix', metavar='BUILDDIR',
  dest='build_prefix', default=build_default,
  help='build directory prefix (default: %(default)s)')
parser.add_argument('--figure-dir', metavar='FIGUREDIR',
  dest='figure_dir', default='newfigures',
  help='figure directory (default: %(default)s)')
parser.add_argument('input_file', nargs='?',
  default='progs-and-figs.txt',
  help='''file format, each line:
program [parameter-to-program...] figure [delay-in-seconds] [# comment]
(default: %(default)s) ''')

# Parse arguments.
args = parser.parse_args()

with open(args.input_file, mode='r') as infile:

  # Create the figure directory, if it does not exist.
  os.makedirs(args.figure_dir, exist_ok=True)

  for line in infile:
    # Remove comments.
    # Split the remainder of the line into blank-separated fields.
    fields = line.split('#')[0].split()

    # Skip lines with less than two fields.
    # These are blank lines, comment lines, and lines with the name of a program
    # from which no screenshot is required.
    if len(fields) < 2:
      continue

    delay = 2;
    if len(fields) >= 3 and fields[-1].isdecimal():
      # The last field consists of only decimal digits. It's the required delay.
      delay = int(fields.pop())

    program = os.path.join(args.build_prefix, fields[0])
    program_src_dir = os.path.join(args.src_prefix, os.path.dirname(fields[0]))
    figure = os.path.join(args.figure_dir, fields[-1])
    cmd_pars = fields[:-1]

    print('Making screenshot from', fields[0])

    process_id = os.fork()
    if not process_id:
      # Child process.
      # Execute the program in its source directory.
      # Some programs will find necessary data files only if they are executed in
      # their source directory.
      try:
        os.chdir(program_src_dir)
      except OSError:
        print("Can't chdir to", program_src_dir)
        sys.exit(1)
      try:
        os.execv(program, cmd_pars)
        # os.execv() does not return.
      except OSError:
        print("Can't execute program", program)
        sys.exit(1)

    # Parent process.
    # Wait for the child process to show its main window.
    time.sleep(delay)

    # Reap the child process, if it has become a zombie.
    os.waitpid(process_id, os.WNOHANG)

    # Check if the child process still exists.
    try:
      os.kill(process_id, 0)
    except ProcessLookupError:
      print("Could not start program from line:", line)
      sys.exit(1)

    result = subprocess.run(['gnome-screenshot', '--window', '--file='+figure])
    os.kill(process_id, signal.SIGKILL)
    if result.returncode:
      print("Can't save screenshot from line:", line)
      sys.exit(result.returncode)

sys.exit(0)
