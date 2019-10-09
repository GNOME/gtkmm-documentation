#!/usr/bin/env python3

# External command, intended to be called from
#   ninja install-desktop-file
# and
#   ninja install-gschema-file

import os
import sys
import shutil
import subprocess

# install-cmd.py desktop <program_name> <desktop_file> <icon_file>
def desktop():
  program_name = sys.argv[2]
  desktop_file = sys.argv[3]
  icon_file = sys.argv[4]

  desktop_install_dir = os.path.expanduser(
    os.path.join('~' , '.local', 'share', 'applications'))
  icon_install_dir = os.path.expanduser(
    os.path.join('~' , '.local', 'share', 'icons', 'hicolor', '48x48', 'apps'))

  # Create the installation directories, if they do not exist.
  os.makedirs(desktop_install_dir, exist_ok=True)
  os.makedirs(icon_install_dir, exist_ok=True)

  shutil.copy(desktop_file, os.path.join(desktop_install_dir, program_name + '.desktop'))
  shutil.copy(icon_file, icon_install_dir)
  return 0

# install-cmd.py gschema <gschema_file>
def gschema():
  gschema_file = sys.argv[2]

  # Don't do anything, if GSETTINGS_SCHEMA_DIR is not set,
  # or if it is set to the current directory ('.').
  gschema_install_dir = os.environ.get('GSETTINGS_SCHEMA_DIR', None)
  if not gschema_install_dir or gschema_install_dir == os.curdir:
    return 0

  # Create the installation directory, if it does not exist.
  os.makedirs(gschema_install_dir, exist_ok=True)

  shutil.copy(gschema_file, gschema_install_dir)
  return subprocess.run(['glib-compile-schemas', gschema_install_dir]).returncode

# ----- Main -----
subcommand = sys.argv[1]
if subcommand == 'desktop':
  sys.exit(desktop())
if subcommand == 'gschema':
  sys.exit(gschema())
print(sys.argv[0], ': illegal subcommand,', subcommand)
sys.exit(1)
