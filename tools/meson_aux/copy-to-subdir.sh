#!/bin/sh -e

# External command, intended to be called with custom_target() in meson.build

# copy-to-subdir.sh <input_file_path> <relative_subdir> <output_file_name> <stamp_file_path>

# input_file_path: input file, possibly including path.
# relative_subdir: to where the file shall be copied, relative to the input file's directory.
# output_file_name: output file, without path.
# stamp_file_path: stamp file, possibly including path.

# Paths can be either absolute paths, or paths relative to the directory which
# is current when this script is called.

input_dir_path="$(dirname "$1")"
( cd "$input_dir_path"; mkdir --parents "$2" )
cp --preserve "$1" "$input_dir_path/$2/$3"
touch "$4"

