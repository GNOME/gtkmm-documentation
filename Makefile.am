## This file is part of gtkmm-documentation.

ACLOCAL_AMFLAGS	= -I build ${ACLOCAL_FLAGS}
DISTCHECK_CONFIGURE_FLAGS = --enable-warnings=fatal

if HAVE_GNOME_DOC_UTILS
doc_subdirs = docs
else
doc_subdirs =
endif
SUBDIRS = examples $(doc_subdirs)

dist_noinst_DATA = COPYING.examples README.SUN
dist_noinst_SCRIPTS = autogen.sh
