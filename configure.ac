## This file is part of gtkmm-documentation.

AC_PREREQ([2.59])
AC_INIT([gtkmm-documentation], [4.12.0],
        [https://gitlab.gnome.org/GNOME/gtkmm-documentation/issues/],
        [gtkmm-documentation], [https://gtkmm.gnome.org/])

AC_CONFIG_SRCDIR([examples/book/box/packbox.cc])
AC_CONFIG_AUX_DIR([build])
AC_CONFIG_MACRO_DIR([build])
AC_CONFIG_HEADERS([build/config.h])

AM_INIT_AUTOMAKE([1.9 -Wno-portability check-news no-dist-gzip dist-xz tar-ustar no-define nostdinc foreign])
# Support silent build rules.
# Disable by either passing --disable-silent-rules to configure or passing V=1 to make.
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])
AM_MAINTAINER_MODE
AC_ARG_VAR([ACLOCAL_FLAGS], [aclocal flags, e.g. -I <macro dir>])

MM_PREREQ([0.9.12])

AC_PROG_CXX
MM_AX_CXX_COMPILE_STDCXX([17], [noext], [mandatory])

AC_PATH_PROG([PERL], [perl], [perl])
AC_PROG_SED

PKG_CHECK_MODULES([GIOMM], [giomm-2.68 >= 2.68.0])
PKG_CHECK_MODULES([GTKMM], [gtkmm-4.0  >= 4.10.0])
MM_PKG_CONFIG_SUBST([GTHREAD_CFLAGS], [--cflags-only-other gthread-2.0])

# glib-compile-resources and C compiler are needed to generate and compile
# resource files in example programs.
AC_SUBST(GLIB_COMPILE_RESOURCES, [`$PKG_CONFIG --variable=glib_compile_resources gio-2.0`])
AC_PROG_CC

# Some example programs use GSettings schema XML files.
GLIB_GSETTINGS

AC_LANG([C++])
AC_CHECK_FUNCS([mkfifo])
AM_CONDITIONAL([MKFIFO_EXISTS], [test "x$ac_cv_func_mkfifo" = xyes])

MM_ARG_ENABLE_WARNINGS([EXAMPLES_WXXFLAGS],
                       [-Wall],
                       [-pedantic -Wall -Wextra -Wformat-security -Wsuggest-override -Wshadow -Wno-long-long],
                       [G PANGO GDK GDK_PIXBUF GTK GLIBMM GIOMM GDKMM PANGOMM GTKMM SIGCXX])

YELP_HELP_INIT

AC_CONFIG_FILES([Makefile
                 examples/Makefile
                 examples/book/buildapp/Makefile
                 docs/tutorial/Makefile])
AC_OUTPUT
