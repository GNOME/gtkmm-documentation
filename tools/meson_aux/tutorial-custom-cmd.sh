#!/bin/bash

# External command, intended to be called with custom_target() in meson.build

case $1 in
html)
  # tutorial-custom-cmd.sh html <relative_dir_name> <build_dir>  <input_xml_file> <output_html_dir>

  # Set the use.id.as.filename param so that we don't use the chapter / section
  # number as the filename, otherwise the url will change every time anything is
  # re-ordered or inserted in the documentation.
  # For a list of available parameters, see http://docbook.sourceforge.net/release/xsl/current/doc/html/
  xslt_params='
    --param       toc.section.depth 1
    --stringparam html.stylesheet style.css
    --stringparam admon.graphics 1
    --stringparam admon.graphics.path icons/
    --stringparam admon.graphics.extension .png
    --stringparam chunker.output.indent yes
    --stringparam chunker.output.encoding UTF-8
    --stringparam navig.graphics yes
    --stringparam navig.graphics.extension .png
    --stringparam navig.graphics.path icons/
    --stringparam toc.list.type ul
    --stringparam use.id.as.filename 1'
  xslt_stylesheet='http://docbook.sourceforge.net/release/xsl/current/html/chunk.xsl'

  ( cd "$3"; rm --force --recursive "$2"; mkdir --parents "$2" )
  # Don't use grep instead of sed. grep returns a non-zero exit status if no line
  # is selected, which is the normal case.
  set -o pipefail # Return the exit status of xsltproc, if sed succeeds.
  xsltproc $xslt_params -o "$5/" --xinclude $xslt_stylesheet "$4" |& sed '/^Writing /d'
  ;;
po2mo)
  # tutorial-custom-cmd.sh po2mo <relative_dir_name> <build_dir> <input_po_file> <output_mo_file> <stamp_file_path>
  ( cd "$3"; mkdir --parents "$2" )
  msgfmt -o "$5" "$4"
  touch "$6"
  ;;
xmltrans)
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
dblatex)
  # tutorial-custom-cmd.sh dblatex <input_xml_file> <figures_dir> <output_pdf_file>
  # Create a PDF file, using dblatex.

  # For a list of available parameters, see http://dblatex.sourceforge.net/doc/manual/
  dblatex_params='
    -P toc.section.depth=2
    -P paper.type=a4paper'
  figures_dir_parent="$(dirname "$3")"
  dblatex $dblatex_params -I "$figures_dir_parent" -o "$4" --pdf "$2"
  ;;
docbook2pdf)
  # tutorial-custom-cmd.sh docbook2pdf <input_xml_file> <figures_dir> <output_pdf_file>
  # Create a PDF file, using docbook2pdf.
  output_dir="$(dirname "$4")"
  output_basename="$(basename -s .pdf "$4")"
  xml_file="$output_dir/$output_basename.xml"

  # We need to produce a full examples XML with all of the XIncludes done.
	xmllint --xinclude --postvalid --output "$xml_file" "$2"

	# We also need to copy the figures from the source directory, so they
	# can be found from the XML file.
	cp --preserve --recursive "$3" "$output_dir/$(basename "$3")"

	docbook2pdf --output "$output_dir" "$xml_file"
	;;
esac

