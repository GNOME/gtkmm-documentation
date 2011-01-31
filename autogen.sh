#! /bin/sh -e
test -n "$srcdir" || srcdir=`dirname "$0"`
test -n "$srcdir" || srcdir=.
 # gtkmm-documentation depends on the mm-common module. Stop if it's not installed.
mm-common-prepare --version

(
  cd "$srcdir" &&
  gnome-doc-prepare --automake --copy --force &&
  autoreconf --force --install --verbose
) || exit
test -n "$NOCONFIGURE" || "$srcdir/configure" --enable-maintainer-mode "$@"
