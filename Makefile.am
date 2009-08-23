## This file is part of gtkmm-documentation.

ACLOCAL_AMFLAGS	= -I build ${ACLOCAL_FLAGS}
DISTCHECK_CONFIGURE_FLAGS = --enable-warnings=fatal

if HAVE_GNOME_DOC_UTILS
doc_subdirs = docs/FAQ docs/tutorial
else
doc_subdirs =
endif
SUBDIRS = examples $(doc_subdirs)

gtkmm_docdir = $(datadir)/doc/gtkmm-2.4
imagesdir = $(gtkmm_docdir)/images
dist_images_DATA = docs/images/gtkmm_logo.gif docs/images/top.gif

dist_noinst_DATA = COPYING.examples README.SUN
dist_noinst_SCRIPTS = autogen.sh
