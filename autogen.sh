#! /bin/sh -e
test -n "$srcdir" || srcdir=`dirname "$0"`
test -n "$srcdir" || srcdir=.

# gtkmm-documentation depends on the mm-common module. Stop if it's not
# installed.
# Also copy files from mm-common to the build/ directory so that things like
# auto-generating the ChangeLog from the git commit messages on 'make dist' is
# possible.
mm-common-prepare --copy --force "$srcdir"

(
  cd "$srcdir" &&
  autoreconf --force --install --verbose
) || exit
test -n "$NOCONFIGURE" || "$srcdir/configure" --enable-maintainer-mode "$@"
