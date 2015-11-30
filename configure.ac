## This file is part of gtkmm-documentation.

AC_PREREQ([2.59])
AC_INIT([gtkmm-documentation], [3.17.50],
        [http://bugzilla.gnome.org/enter_bug.cgi?product=gtkmm],
        [gtkmm-documentation], [http://www.gtkmm.org/])

AC_CONFIG_SRCDIR([examples/book/box/packbox.cc])
AC_CONFIG_AUX_DIR([build])
AC_CONFIG_MACRO_DIR([build])
AC_CONFIG_HEADERS([build/config.h])

AM_INIT_AUTOMAKE([1.9 -Wno-portability check-news dist-bzip2 no-define nostdinc tar-ustar])
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES])
AM_MAINTAINER_MODE
AC_ARG_VAR([ACLOCAL_FLAGS], [aclocal flags, e.g. -I <macro dir>])

MM_PREREQ([0.9.8])

AC_PROG_CXX
MM_AX_CXX_COMPILE_STDCXX_11([noext],[mandatory])

AC_PATH_PROG([PERL], [perl], [perl])
AC_PROG_SED

PKG_CHECK_MODULES([GIOMM], [giomm-2.4 >= 2.47.3.1])
PKG_CHECK_MODULES([GTKMM], [gtkmm-3.0 >= 3.19.3])
MM_PKG_CONFIG_SUBST([GTHREAD_CFLAGS], [--cflags-only-other gthread-2.0])

# glib-compile-resources and C compiler are needed to generate and compile
# resource files in example programs.
AC_SUBST(GLIB_COMPILE_RESOURCES, [`$PKG_CONFIG --variable=glib_compile_resources gio-2.0`])
AC_PROG_CC

AC_LANG([C++])
AC_CHECK_FUNCS([mkfifo])

MM_ARG_ENABLE_WARNINGS([EXAMPLES_WXXFLAGS],
                       [-Wall],
                       [-pedantic -Wall -Wextra -Wformat-security -Wsuggest-override -Wshadow -Wno-long-long],
                       [G PANGO ATK GDK GDK_PIXBUF GTK GLIBMM GIOMM GDKMM ATKMM PANGOMM GTKMM SIGCXX])

YELP_HELP_INIT

AC_CONFIG_FILES([Makefile
                 examples/Makefile
                 docs/tutorial/Makefile])
AC_OUTPUT
