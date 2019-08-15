#!/bin/sh -e

# External command, intended to be called with custom_target() in meson.build

# compile-schemas.sh <relative_dir_name> <source_dir> <build_dir> <output_file>

# relative_dir_name: where the .gschema.xml file is located, relative to source_dir 
# source_dir: where the meson.build file is located.
# build_dir: the corresponding location in the build tree.
# output_file: contains the path relative to the directory where this script starts executing.

( cd "$3"; mkdir --parents "$1" )
glib-compile-schemas --strict --targetdir="$3/$1" "$2/$1"
cp "$3/$1/gschemas.compiled" "$4"


