## This file is part of gtkmm-documentation.

gtkmm_docdir = $(datadir)/doc/gtkmm-3.0

# Function: $(call vpath_listall,PATTERN ...)
# Get all filenames which match a PATTERN from the list.  Look for files
# relative to either the current directory or $(srcdir).  Strip $(srcdir)/
# again before returning and remove any duplicates.
vpath_srclist = $(patsubst $(srcdir)/%,%,$(wildcard $(addprefix $(srcdir)/,$(1))))
vpath_listall = $(sort $(wildcard $(1)) $(if $(srcdir:.=),$(vpath_srclist)))

DOCBOOK_STYLESHEET_HTML ?= http://docbook.sourceforge.net/release/xsl/current/html/chunk.xsl
XMLLINT = xmllint
XSLTPROC = xsltproc
DB2PDF = docbook2pdf

DOCBOOK_STYLESHEET_EPUB ?= http://docbook.sourceforge.net/release/xsl/current/epub/docbook.xsl

DOC_MODULE = gtkmm-tutorial
DOC_ENTITIES =
DOC_INCLUDES =
DOC_FIGURES =					\
	figures/alignment.png			\
	figures/aspectframe.png			\
	figures/assistant.png			\
	figures/box_packing1.png		\
	figures/box_packing2.png		\
	figures/box_packing3.png		\
	figures/buttonbox.png			\
	figures/buttons.png			\
	figures/cairo_clock.png			\
	figures/cairo_joins.png			\
	figures/checkbutton.png			\
	figures/clipboard_ideal.png		\
	figures/clipboard_simple.png		\
	figures/combo.png			\
	figures/combobox_complex.png		\
	figures/combobox_text.png		\
	figures/comboboxentry_complex.png	\
	figures/comboboxentry_text.png		\
	figures/custom_container.png		\
	figures/custom_widget.png		\
	figures/dialogs_about.png		\
	figures/dialogs_colorchooserdialog.png\
	figures/dialogs_filechooser.png		\
	figures/dialogs_fontchooserdialog.png	\
	figures/dialogs_messagedialog.png	\
	figures/dialogs_simple.png		\
	figures/drag_and_drop.png		\
	figures/drawingarea_arcs.png		\
	figures/drawingarea_curve.png		\
	figures/drawingarea_image.png		\
	figures/drawingarea_lines.png		\
	figures/drawingarea_pango_text.png		\
	figures/drawingarea_text.png		\
	figures/drawingarea_thin_lines.png		\
	figures/entry.png			\
	figures/entry_completion.png		\
	figures/entry_icon.png		\
	figures/entry_progress.png		\
	figures/eventbox.png			\
	figures/expander.png			\
	figures/filechooserbutton.png		\
	figures/frame.png			\
	figures/grid.png			\
	figures/helloworld.png			\
	figures/helloworld2.png			\
	figures/idle.png			\
	figures/infobar.png			\
	figures/keyboardevents_simple.png			\
	figures/keyboardevents_propagation.png		\
	figures/label.png			\
	figures/main_menu.png			\
	figures/menu_popup.png			\
	figures/menus_and_toolbars.png		\
	figures/menus_menu.png			\
	figures/menus_menubar.png		\
	figures/multithread.png		\
	figures/notebook.png			\
	figures/paned.png			\
	figures/printing.png			\
	figures/progressbar.png			\
	figures/radiobuttons.png		\
	figures/range_widgets.png		\
	figures/recentchooserdialog.png		\
	figures/scrolledwindow.png		\
	figures/socket-fail.png			\
	figures/socket.png			\
	figures/spinbutton.png			\
	figures/textview.png			\
	figures/toolbar.png			\
	figures/toolpalette.png			\
	figures/tooltip.png			\
	figures/treeview_combo_renderer.png	\
	figures/treeview_draganddrop.png	\
	figures/treeview_editablecells.png	\
	figures/treeview_list.png		\
	figures/treeview_popup.png		\
	figures/treeview_tree.png		\
	figures/update_ui.png

DOC_LINGUAS = de el es fr pt_BR sl zh_CN

MAINTAINERCLEANFILES = html/*.html $(srcdir)/html/*.html

# Set the use.id.as.filename param so that we don't use the chapter / section
# number as the filename, otherwise the url will change every time anything is
# re-ordered or inserted in the documentation
xslt_params = $(strip						\
	--param       toc.section.depth		1		\
	--stringparam html.stylesheet		'style.css'	\
	--stringparam admon.graphics		'1'		\
	--stringparam admon.graphics.path	'icons/'	\
	--stringparam admon.graphics.extension	'.png'		\
	--stringparam chunker.output.indent	'yes'		\
	--stringparam chunker.output.encoding	'UTF-8'		\
	--stringparam navig.graphics		'yes'		\
	--stringparam navig.graphics.extension	'.png'		\
	--stringparam navig.graphics.path	'icons/'	\
	--stringparam toc.list.type		'ul'		\
	--stringparam use.id.as.filename	'1'		\
	)

tutorialdir         = $(gtkmm_docdir)/tutorial
tutorial_htmldir    = $(tutorialdir)/html
tutorial_figuresdir = $(tutorial_htmldir)/figures
tutorial_iconsdir   = $(tutorial_htmldir)/icons

tutorial_html_files = $(call vpath_listall,html/*.html) style.css
tutorial_html_inst  = $(foreach\
	file,$(tutorial_html_files),$(or $(wildcard $(file)),$(srcdir)/$(file)))

tutorial_xml_files  = $(addsuffix /gtkmm-tutorial.xml,C $(DOC_LINGUAS))
tutorial_po_files   = $(foreach lang,$(lang)/$(lang).po,$(DOC_LINGUAS))

dist_noinst_DATA =		\
	insert_example_code.pl	\
	C/gtkmm-tutorial-in.xml	\
	$(tutorial_po_files)	\
	$(tutorial_xml_files)	\
	$(tutorial_html_files)

dist_tutorial_figures_DATA = $(addprefix C/,$(DOC_FIGURES))

dist_tutorial_icons_DATA =	\
	icons/caution.png	\
	icons/home.png		\
	icons/important.png	\
	icons/next.png		\
	icons/note.png		\
	icons/prev.png		\
	icons/tip.png		\
	icons/up.png		\
	icons/warning.png

include $(top_srcdir)/build/gnome-doc-utils.make

all-local: $(DOC_LINGUAS) $(addsuffix /gtkmm-tutorial.xml,C $(DOC_LINGUAS)) html/index.html

install-data-local: install-tutorial

uninstall-local: uninstall-tutorial

install-tutorial: html/index.html
	@$(NORMAL_INSTALL)
	$(MKDIR_P) '$(DESTDIR)$(tutorial_htmldir)'
	$(INSTALL_DATA) $(tutorial_html_inst) '$(DESTDIR)$(tutorial_htmldir)/'

uninstall-tutorial:
	@$(NORMAL_UNINSTALL)
	rm -f '$(DESTDIR)$(tutorial_htmldir)'/*.html
	rm -f '$(DESTDIR)$(tutorial_htmldir)/style.css'

$(DOC_LINGUAS):
	@$(MKDIR_P) $@

# Create a html generation of the C locale's version of the DocBook,
# using our custom stylesheet and graphics:
html/index.html: $(srcdir)/C/gtkmm-tutorial.xml
	$(AM_V_at)rm -fr html
	$(AM_V_at)$(MKDIR_P) html
	$(AM_V_GEN)$(XSLTPROC) $(xslt_params) -o html/ --xinclude --catalogs \
		'$(DOCBOOK_STYLESHEET_HTML)' $<

# TODO: I'm not sure how useful this output is, or what we can do with it. murrayc.
epub_via_xsl: $(srcdir)/C/gtkmm-tutorial.xml
	$(AM_V_at)rm -fr epub
	$(AM_V_at)$(MKDIR_P) epub
	$(AM_V_GEN)$(XSLTPROC) $(xslt_params) -o epub/ --xinclude --catalogs \
		'$(DOCBOOK_STYLESHEET_EPUB)' $<

# This epub/mobi generation is experimental. murrayc.
epub: $(srcdir)/gtkmm-tutorial.epub

# Create an epub generation of the C locale's version of the DocBook,
# using our custom stylesheet and graphics.
# This apparently uses the XSL stylesheets that we try to use in epub_via_xsl above.
gtkmm-tutorial.epub: $(srcdir)/C/gtkmm-tutorial.xml
	dbtoepub $<

mobi: $(srcdir)/gtkmm-tutorial.mobi

# ebook-convert is provided by the calibre UI app.
# TODO: Use --cover kindle_cover.jpg when this ImageMagik problem is fixed:
# Exception: no decode delegate for this image format `' @ error/blob.c/BlobToImage/348
gtkmm-tutorial.mobi: $(srcdir)/gtkmm-tutorial.epub $(srcdir)/kindle_cover.jpg
	ebook-convert $< gtkmm-tutorial.mobi --input-profile=kindle

# Make sure that the documentation will always have been generated before
# executing the commands of a rule that depends on files in html/.
html/chapter-%.html html/sec-%.html: | html/index.html

# Create a DocBook source file that doesn't have the examples' comments blocks:
$(srcdir)/C/gtkmm-tutorial.xml: $(srcdir)/C/gtkmm-tutorial-in.xml $(srcdir)/insert_example_code.pl
	$(AM_V_GEN)$(PERL) -- $(srcdir)/insert_example_code.pl $(top_srcdir)/examples/book $< >$@

validate_original: $(srcdir)/C/gtkmm-tutorial-in.xml
	$(XMLLINT) --xinclude --postvalid --noout $<

validate: $(srcdir)/C/gtkmm-tutorial.xml
	$(XMLLINT) --xinclude --postvalid --noout $<

# we need to produce a full examples with all of the XIncludes done so that it
# can be processed for PDF
C/programming-with-gtkmm-onefile.xml: $(srcdir)/C/gtkmm-tutorial.xml
	$(AM_V_at)$(MKDIR_P) C
	$(AM_V_GEN)$(XMLLINT) --xinclude --postvalid -o $@ $<

# We have to generate the pdf in a subdirectory (e.g. pdf/) because the tutorial
# specifies the path to the figures as '../figures' so if we build it in this
# directory, it won't find the images.
pdf/programming-with-gtkmm-pdf.pdf: C/programming-with-gtkmm-onefile.xml
	$(AM_V_at)$(MKDIR_P) pdf
	$(AM_V_GEN)$(DB2PDF) --output pdf/ $<

.PHONY: install-tutorial uninstall-tutorial

# Instruct GNU make to delete the targets of a rule after it failed, in
# order to avoid the complication of handling that situation manually.
.DELETE_ON_ERROR:
