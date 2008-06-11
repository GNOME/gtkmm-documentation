include $(top_srcdir)/docs/Makefile_web.am_fragment

gtkmm_tut_path = $(web_path_docs)tutorial

SUBDIRS =

DOCBOOK_PHPWEBNOTES_TRANSFORM = docbook_phpwebnotes.xsl

EXTRA_DIST = README insert_example_code.pl C/gtkmm-tut.xml C/gtkmm-tut-with-examples.xml style.css $(DOCBOOK_PHPWEBNOTES_TRANSFORM)

DOCBOOK_STYLESHEET ?= http://docbook.sourceforge.net/release/xsl/current/html/chunk.xsl
XMLLINT = xmllint
XSLTPROC = xsltproc
DB2PDF = docbook2pdf

# Create a DocBook source file that doesn't have the examples' comments blocks:
C/gtkmm-tut-with-examples.xml: C/gtkmm-tut.xml insert_example_code.pl
	$(PERL_PATH) $(srcdir)/insert_example_code.pl $(top_srcdir)/examples/book $< >$@


include $(top_srcdir)/scripts/gnome-doc-utils.make
dist-hook: doc-dist-hook

DOC_MODULE = gtkmm-tut-with-examples
DOC_ENTITIES =
DOC_INCLUDES =
DOC_FIGURES = \
	figures/alignment.png figures/aspectframe.png \
	figures/box_packing1.png figures/box_packing2.png figures/box_packing3.png \
	figures/buttonbox.png figures/buttons.png figures/checkbutton.png \
	figures/clipboard_simple.png figures/clipboard_ideal.png \
	figures/combo.png figures/combobox_complex.png figures/combobox_text.png figures/comboboxentry_complex.png figures/comboboxentry_text.png figures/custom_container.png \
	figures/dialogs_about.png figures/dialogs_colorselectiondialog.png figures/dialogs_filechooser.png figures/dialogs_fontselectiondialog.png \
	figures/dialogs_messagedialog.png figures/dialogs_simple.png \
	figures/drag_and_drop.png figures/drawingarea_arcs.png figures/drawingarea_curve.png figures/drawingarea_lines.png figures/drawingarea_text.png \
	figures/entry.png figures/eventbox.png figures/expander.png figures/filechooserbutton.png figures/frame.png \
	figures/helloworld.png figures/helloworld2.png figures/idle.png figures/label.png \
	figures/main_menu.png figures/menu_popup.png \
	figures/menus_menubar.png figures/menus_menu.png figures/menus_and_toolbars.png \
	figures/notebook.png \
	figures/paned.png printing.png figures/progressbar.png figures/radiobuttons.png \
	figures/range_widgets.png figures/recentchooserdialog.png \
	figures/scrolledwindow.png figures/socket.png socket-fail.png figures/spinbutton.png \
	figures/table.png toolbar.png figures/textview.png \
	figures/treeview_list.png figures/treeview_tree.png figures/treeview_editablecells.png figures/treeview_combo_renderer.png \
        figures/treeview_draganddrop.png figures/treeview_popup.png \
        figures/devcpp_project_options.png figures/cairo_clock.png figures/cairo_joins.png  \
        figures/update_ui.png \
        figures/msvc_add_existing_property_sheet.png figures/msvc_new_project_menu.png figures/msvc_properties_subsystem_windows.png \
        figures/msvc_application_settings.png figures/msvc_project_created.png msvc_property_files.png \
        figures/msvc_corrected_main.png figures/msvc_project_properties.png figures/msvc_property_manager.png \
        figures/msvc_corrected_stdafx.png figures/msvc_properties_maincrtstartup.png figures/msvc_property_manager_with_gtkmm_properties.png \
        figures/msvc_main_program.png figures/msvc_properties_noinherit.png \
        figures/msvc_new_project_dialog.png figures/msvc_properties_remove_warning_4250.png

DOC_LINGUAS = de


# Create a html generation of the C locale's version of the DocBook, 
# using our custom stylesheet and graphics:
# Set the use.id.as.filename param so that we don't use the chapter / section
# number as the filename, otherwise the url will change every time anything is
# re-ordered or inserted in the documentation
html/index.html: C/gtkmm-tut-with-examples.xml Makefile.am
	rm -rf html
	$(mkinstalldirs) html
	cp style.css html/
	cp -r C/figures html/
	cp -r C/icons html/
	$(XSLTPROC) \
		--param toc.section.depth 1	\
		--stringparam html.stylesheet "style.css"	\
		--stringparam admon.graphics 1	\
		--stringparam admon.graphics.path "icons/"	\
		--stringparam admon.graphics.extension ".png"	\
		--stringparam chunker.output.indent yes	\
		--stringparam chunker.output.encoding UTF-8	\
		--stringparam navig.graphics yes	\
		--stringparam navig.graphics.extension ".png"	\
		--stringparam navig.graphics.path "icons/"	\
		--stringparam toc.list.type "ul"	\
		--stringparam use.id.as.filename "1" \
		-o html/ --xinclude --catalogs $(DOCBOOK_STYLESHEET)	\
		$<

validate_original: gtkmm-tut.xml
	$(XMLLINT) --xinclude --postvalid --noout $<

validate: C/gtkmm-tut-with-examples.xml
	$(XMLLINT) --xinclude --postvalid --noout $<

gtkmm-tut-html.tar.gz: html/index.html
	tar cf - C/figures html | gzip -c --best >$@

post-html: html/index.html style.css pdf
	rsync $(rsync_args) C/figures/*.png $$USER@$(web_host):$(gtkmm_tut_path)/figures/
	rsync $(rsync_args) C/icons/*.png $$USER@$(web_host):$(gtkmm_tut_path)/icons/
	rsync $(rsync_args) -r html/ $$USER@$(web_host):$(gtkmm_tut_path)/html/
	rsync $(rsync_args) *.css $$USER@$(web_host):$(gtkmm_tut_path)/html/
	rsync $(rsync_args) -r pdf/ $$USER@$(web_host):$(gtkmm_tut_path)/pdf/

# we need to produce a full examples with all of the XIncludes done so that it
# can processed for PDF
C/programming-with-gtkmm-pdf.xml: C/gtkmm-tut-with-examples.xml
	rm -rf html
	$(mkinstalldirs) html
	$(XMLLINT) --xinclude --postvalid $< -o $@

# We have to generate the pdf in a subdirectory (e.g. pdf/) because the tutorial
# specifies the path to the figures as '../figures' so if we build it in this
# directory, it won't find the images.
pdf/programming-with-gtkmm-pdf.pdf: C/programming-with-gtkmm-pdf.xml
	$(DB2PDF) --output pdf $<

pdf : pdf/programming-with-gtkmm-pdf.pdf

doc-clean:
	-rm -f C/gtkmm-tut-with-examples.xml gtkmm-tut-html.tar.gz C/programming-with-gtkmm-pdf.xml
	-rm -rf pdf

tutorialdir = $(gtkmm_docdir)/tutorial/html

all-local: html/index.html

install-data-local: install-tutorial

uninstall-local: uninstall-tutorial

maintainer-clean-local: doc-clean

.PHONY: post-html doc-clean install-tutorial uninstall-tutorial
