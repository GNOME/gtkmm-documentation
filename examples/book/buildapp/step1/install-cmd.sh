#!/bin/sh -e

# External command, intended to be called from
#   ninja install-desktop-file
# and
#   ninja install-gschema-file

cd $MESON_SOURCE_ROOT

if [ "x$1" = "xdesktop" ]; then
  # ./install-cmd.sh desktop <program_name> <desktop_file> <icon_file>
  mkdir -p ~/.local/share/applications
  sed -e "s#@bindir@#$MESON_BUILD_ROOT#" "$3" > ~/.local/share/applications/$2.desktop
  mkdir -p ~/.local/share/icons/hicolor/48x48/apps
  cp "$4" ~/.local/share/icons/hicolor/48x48/apps

elif [ "x$1" = "xgschema" ]; then
  # ./install-cmd.sh gschema <gschema_file>
  if [ -n "$GSETTINGS_SCHEMA_DIR" -a "$GSETTINGS_SCHEMA_DIR" != . ]; then
    mkdir -p "$GSETTINGS_SCHEMA_DIR"
    cp "$2" "$GSETTINGS_SCHEMA_DIR"
    glib-compile-schemas "$GSETTINGS_SCHEMA_DIR"
  fi

else
  echo Unknown subcommand: $*
  exit 1
fi
