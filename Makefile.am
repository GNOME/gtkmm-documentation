## This file is part of gtkmm-documentation.

ACLOCAL_AMFLAGS	= -I build ${ACLOCAL_FLAGS}
DISTCHECK_CONFIGURE_FLAGS = --enable-warnings=max

SUBDIRS = examples docs/tutorial

dist_noinst_DATA = COPYING.examples README.md
dist_noinst_SCRIPTS = autogen.sh

# Distribute files needed when building with Meson.
EXTRA_DIST = \
  meson.build \
  meson_options.txt \
  docs/tutorial/book.xsl \
  docs/tutorial/can_use_xmllint.xml \
  docs/tutorial/insert_example_code.py \
  docs/tutorial/meson.build \
  docs/tutorial/LINGUAS \
  docs/tutorial/highlight.js/highlight.min.css \
  docs/tutorial/highlight.js/highlight.min.js \
  examples/meson.build \
  examples/book/meson.build \
  examples/book/buildapp/meson.build \
  examples/book/giomm/meson.build \
  examples/book/treeview/meson.build \
  examples/others/meson.build \
  tools/meson_aux/compile-schemas.py \
  tools/meson_aux/copy-to-subdir.py \
  tools/meson_aux/extra-dist-cmd.py \
  tools/meson_aux/tutorial-custom-cmd.py

# Auto-generate the ChangeLog file from the git log on make dist
include $(top_srcdir)/build/dist-changelog.am
