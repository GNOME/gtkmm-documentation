#!/bin/bash

# External command, intended to be called with custom_target() in meson.build

if [ "x$1" = "xpo2mo" ]; then
  # tutorial-custom-cmd.sh po2mo <relative_dir_name> <build_dir> <input_po_file> <output_mo_file> <stamp_file_path>
  ( cd "$3"; mkdir --parents "$2" )
  msgfmt -o "$5" "$4"
  touch "$6"
elif [ "x$1" = "xdocbook" ]; then
  # tutorial-custom-cmd.sh docbook <input_mo_file> <input_xml_file> <output_xml_dir> <stamp_file_path>
  itstool -m "$2" -o "$4" "$3"
  touch "$5"
elif [ "x$1" = "xxmllint" ]; then
  # tutorial-custom-cmd.sh xmllint <input_xml_file> <stamp_file_path>
  xmllint --nonet --noout --noent --path "$(dirname "$2")" --xinclude "$2"
  touch "$3"
fi

