## This file is part of gtkmm-documentation.

AC_PREREQ([2.59])
AC_INIT([gtkmm-documentation], [2.16.0], [http://bugzilla.gnome.org/enter_bug.cgi?product=gtkmm],
        [gtkmm-documentation], [http://www.gtkmm.org/])

AC_CONFIG_SRCDIR([examples/book/box/packbox.cc])
AC_CONFIG_AUX_DIR([build])
AC_CONFIG_MACRO_DIR([build])
AC_CONFIG_HEADERS([build/config.h])

AM_INIT_AUTOMAKE([1.9 -Wno-portability dist-bzip2 no-define nostdinc tar-pax])
AM_MAINTAINER_MODE
AC_ARG_VAR([ACLOCAL_FLAGS], [aclocal flags, e.g. -I <macro dir>])

AC_PROG_CXX
AC_PATH_PROG([PERL], [perl], [perl])

PKG_CHECK_MODULES([EXAMPLES], [giomm-2.4 >= 2.16.0 gtkmm-2.4 >= 2.16.0 libglademm-2.4 >= 2.6.0])
MM_PKG_CONFIG_SUBST([GTHREAD_CFLAGS], [--cflags-only-other gthread-2.0])

AC_LANG([C++])
AC_CHECK_FUNCS([mkfifo flockfile funlockfile getc_unlocked])

MM_ARG_ENABLE_WARNINGS([EXAMPLES_WXXFLAGS],
                       [-Wall],
                       [-pedantic -Wall -Wextra]
                       [G PANGO ATK GDK GDK_PIXBUF GTK])

GNOME_DOC_INIT([0.9.0],,
  [AC_MSG_WARN([[gnome-doc-utils not found: tutorial will not be built.]])])

AC_CONFIG_FILES([Makefile
                 examples/Makefile
                 docs/Makefile
                 docs/FAQ/Makefile
                 docs/images/Makefile
                 docs/tutorial/Makefile
                 docs/tutorial/icons/Makefile])
AC_OUTPUT