#!/bin/bash

# External command, intended to be called with custom_target() in meson.build

case $1 in
po2mo)
  # tutorial-custom-cmd.sh po2mo <relative_dir_name> <build_dir> <input_po_file> <output_mo_file> <stamp_file_path>
  ( cd "$3"; mkdir --parents "$2" )
  msgfmt -o "$5" "$4"
  touch "$6"
  ;;
docbook)
  # tutorial-custom-cmd.sh docbook <input_mo_file> <input_xml_file> <output_xml_dir> <stamp_file_path>
  # Create XML file with translation.
  itstool -m "$2" -o "$4" "$3"
  touch "$5"
  ;;
xmllint)
  # tutorial-custom-cmd.sh xmllint <validate> <input_xml_file> <stamp_file_path>
  validate=""
  if [ "x$2" = "xtrue" ]; then
    validate="--postvalid"
  fi
  xmllint --noout --noent --xinclude $validate "$3"
  touch "$4"
  ;;
pdf)
  # tutorial-custom-cmd.sh pdf <input_xml_file> <figures_dir> <output_pdf_file>
  output_dir="$(dirname "$4")"
  output_basename="$(basename -s .pdf "$4")"
  xml_file="$output_dir/$output_basename.xml"

  # We need to produce a full examples XML with all of the XIncludes done.
	xmllint --xinclude --postvalid --output "$xml_file" "$2"

	# We also need to copy the figures from the source directory, so they
	# can be found from the XML files.
	cp --preserve --recursive "$3" "$output_dir/$(basename "$3")"

	docbook2pdf --output "$output_dir" "$xml_file"
	;;
esac

