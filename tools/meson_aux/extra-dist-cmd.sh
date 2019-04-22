#!/bin/bash

# External command, intended to be called with add_dist_script() in meson.build

# extra-dist-cmd.sh <root_build_dir> <relative_dist_dir> <tutorial_languages>

# relative_dist_dir is the distribution directory path relative to root_build_dir.

# Distribute some built files in addition to the files in the local git clone.
cd "$1"
# English index.docbook and html files
cp "docs/tutorial/index.docbook" "$2/docs/tutorial/C/"
cp --recursive "docs/tutorial/html/" "$2/docs/tutorial/"
# .mo files with translations and translated index.docbook files.
for lang in $3; do
  cp "docs/tutorial/$lang/$lang.mo" "docs/tutorial/$lang/index.docbook" "$2/docs/tutorial/$lang/"
done
