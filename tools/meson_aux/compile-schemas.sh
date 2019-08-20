#!/bin/sh -e

# External command, intended to be called with custom_target() in meson.build

# compile-schemas.sh <relative_dir_name> <source_dir> <build_dir> <output_file>

# <relative_dir_name> Where the .gschema.xml file is located, relative to source_dir.
# <source_dir> Where the meson.build file is located.
# <build_dir> The corresponding location in the build tree.
# <output_file> Contains the path relative to the directory where this script starts executing.

# -p == --parents (Posix does not support long options.)
mkdir -p "$3/$1"
glib-compile-schemas --strict --targetdir="$3/$1" "$2/$1"
cp "$3/$1/gschemas.compiled" "$4"


