#!/bin/bash

# External command, intended to be called with add_dist_script() in meson.build

# extra-dist-cmd.sh <root_source_dir> <root_build_dir> <relative_dist_dir> <tutorial_languages>

# relative_dist_dir is the distribution directory path relative to root_build_dir.
# Meson does not preserve timestamps on distributed files. Neither does this script.

# Make a ChangeLog file for distribution.
git --git-dir="$1/.git" --work-tree="$1" log --no-merges --date=short --max-count=200 \
    --pretty='tformat:%cd  %an  <%ae>%n%n  %s%n%w(0,0,2)%+b' > "$2/$3/ChangeLog"

# Distribute some built files in addition to the files in the local git clone.
cd "$2"
dist_docs_tutorial="$3/docs/tutorial"

# English index.docbook and html files.
cp "docs/tutorial/index.docbook" "$dist_docs_tutorial/C/"
cp --recursive "docs/tutorial/html/" "$dist_docs_tutorial/"

# .mo files with translations and translated index.docbook files.
for lang in $4; do
  cp "docs/tutorial/$lang/$lang.mo" "docs/tutorial/$lang/index.docbook" "$dist_docs_tutorial/$lang/"
done

# If there is an updated PDF file, include it in the tarball.
pdf_file="docs/tutorial/programming-with-gtkmm.pdf"
if [ -f "$pdf_file" -a "$pdf_file" -nt "docs/tutorial/index.docbook" ]; then
  cp "$pdf_file" "$dist_docs_tutorial/C/"
fi

# Remove all .gitignore files and an empty $3/build directory.
find "$3" -name ".gitignore" -exec rm '{}' \;
rmdir --ignore-fail-on-non-empty "$3/build"
