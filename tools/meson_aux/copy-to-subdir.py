#!/usr/bin/env python3

# External command, intended to be called with custom_target() in meson.build

#                        argv[1]           argv[2]           argv[3]          argv[4]
# copy-to-subdir.py <input_file_path> <relative_subdir> <output_file_name> <stamp_file_path>

# <input_file_path> Input file, possibly including path.
# <relative_subdir> To where the file shall be copied, relative to the input file's directory.
# <output_file_name> Output file, without path.
# <stamp_file_path> Stamp file, possibly including path.

# Paths can be either absolute paths, or paths relative to the directory which
# is current when this script is called.

import os
import sys
import shutil
from pathlib import Path

input_file_path = sys.argv[1]
relative_subdir = sys.argv[2]
output_file_name = sys.argv[3]
stamp_file_path = sys.argv[4]

input_dir = os.path.dirname(input_file_path)
target_dir = os.path.join(input_dir, relative_subdir)

# Create the target directory, if it does not exist.
os.makedirs(target_dir, exist_ok=True)

# shutil.copy2() copies timestamps and some other file metadata.
shutil.copy2(input_file_path, os.path.join(target_dir, output_file_name))

Path(stamp_file_path).touch(exist_ok=True)
