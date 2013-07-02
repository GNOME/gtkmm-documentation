## This file is part of gtkmm-documentation.

ACLOCAL_AMFLAGS	= -I build ${ACLOCAL_FLAGS}
DISTCHECK_CONFIGURE_FLAGS = --enable-warnings=fatal

if HAVE_GNOME_DOC_UTILS
doc_subdirs = docs/tutorial
else
doc_subdirs =
endif
SUBDIRS = examples $(doc_subdirs)

dist_noinst_DATA = COPYING.examples
dist_noinst_SCRIPTS = autogen.sh

# Auto-generate the ChangeLog file from the git log on make dist
include $(top_srcdir)/build/dist-changelog.am
