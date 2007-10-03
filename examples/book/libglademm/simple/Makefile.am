include $(top_srcdir)/examples/Makefile.am_fragment

#Build the executable, but don't install it.
noinst_PROGRAMS = basic
basic_SOURCES = basic.cc

#basic.glade is read at runtime, and edited by glade-2.
#It seems that basic.gladep must exist also, when editing basic.glade,
#so that glade-2 knows that it should not add libgnomeui widgets instead of GTK+ widgets.
EXTRA_DIST = basic.glade basic.gladep
