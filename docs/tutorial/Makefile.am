## This file is part of gtkmm-documentation.

@YELP_HELP_RULES@

gtkmm_docdir = $(datadir)/doc/gtkmm-4.0

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

HELP_ID = gtkmm-tutorial

# HELP_FILES is defined in an included file instead of in Makefile.am itself.
# Then DocFormat.source_files() in Infrastructure/damned-lies/stats/utils.py
# won't find it. That's a good thing. The help file is not stored in the git repo.
# damned-lies is confused, if it finds the file name but does not find the file.
# https://gitlab.gnome.org/Infrastructure/damned-lies/-/issues/58
include $(srcdir)/help-files.am

HELP_MEDIA =					\
	figures/aspectframe.png			\
	figures/assistant.png			\
	figures/box_packing1.png		\
	figures/box_packing2.png		\
	figures/buildapp_menu.png \
	figures/buildapp_header_bar.png \
	figures/buildapp_opening_files.png \
	figures/buildapp_populating_window.png \
	figures/buildapp_pref_dialog.png \
	figures/buildapp_properties.png \
	figures/buildapp_search_bar.png \
	figures/buildapp_side_bar.png \
	figures/buildapp_trivial_app.png \
	figures/buttons.png			\
	figures/cairo_clock.png			\
	figures/cairo_joins.png			\
	figures/checkbutton.png			\
	figures/clipboard_ideal.png		\
	figures/clipboard_simple.png		\
	figures/combobox_complex.png		\
	figures/combobox_text.png		\
	figures/comboboxentry_complex.png	\
	figures/comboboxentry_text.png		\
	figures/custom_container.png		\
	figures/custom_css_name.png \
	figures/custom_widget.png		\
	figures/dialogs_about.png		\
	figures/dialogs_alertdialog.png	\
	figures/dialogs_colordialog.png\
	figures/dialogs_filedialog.png		\
	figures/dialogs_fontdialog.png	\
	figures/dialogs_windowdialog.png	\
	figures/drag_and_drop.png		\
	figures/drawingarea_arcs.png		\
	figures/drawingarea_curve.png		\
	figures/drawingarea_image.png		\
	figures/drawingarea_lines.png		\
	figures/drawingarea_pango_text.png		\
	figures/drawingarea_thin_lines.png		\
	figures/dropdown_complex.png \
	figures/dropdown_search_font.png \
	figures/dropdown_search_string.png \
	figures/dropdown_string.png \
	figures/entry.png			\
	figures/entry_completion.png		\
	figures/entry_icon.png		\
	figures/entry_progress.png		\
	figures/events_mouse.png			\
	figures/events_propagation.png \
	figures/events_simple.png			\
	figures/frame.png			\
	figures/grid.png			\
	figures/helloworld.png			\
	figures/helloworld2.png			\
	figures/i18n.png			\
	figures/infobar.png			\
	figures/label.png			\
	figures/listmodel_columnview.png \
	figures/listmodel_filter.png \
	figures/listmodel_gridview.png \
	figures/listmodel_listview.png \
	figures/listmodel_sort.png \
	figures/listmodel_tree.png \
	figures/main_menu.png			\
	figures/menu_popup.png			\
	figures/menus_and_toolbars.png		\
	figures/multithread.png		\
	figures/notebook.png			\
	figures/paned.png			\
	figures/printing_printdialog.png \
	figures/printing_simple.png \
	figures/progressbar.png			\
	figures/radiobuttons.png		\
	figures/range_widgets.png		\
	figures/recentfiles.png		\
	figures/scrolledwindow.png		\
	figures/spinbutton.png			\
	figures/textview.png			\
	figures/tooltip.png			\
	figures/treeview_draganddrop.png	\
	figures/treeview_editablecells.png	\
	figures/treeview_list.png		\
	figures/treeview_popup.png		\
	figures/treeview_tree.png

# Do not define the environment variable LINGUAS.
# If the environment variable LINGUAS exists, YELP_HELP_RULES generate
# make rules for creating files only for languages that are listed in both
# LINGUAS and HELP_LINGUAS, but this Makefile.am assumes that files for
# all languages in HELP_LINGUAS can be created.

HELP_LINGUAS = cs de el es fr pt_BR sl zh_CN

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

tutorial_xml_files  = $(addsuffix /index.docbook,C $(HELP_LINGUAS))
tutorial_po_files   = $(foreach lang,$(lang)/$(lang).po,$(HELP_LINGUAS))

dist_noinst_DATA =		\
	insert_example_code.pl	\
	C/index-in.docbook	\
	$(tutorial_po_files)	\
	$(tutorial_xml_files)	\
	$(tutorial_html_files)

dist_tutorial_figures_DATA = $(addprefix C/,$(HELP_MEDIA))

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


all-local: $(addsuffix /index.docbook,C $(HELP_LINGUAS)) html/index.html

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

# Create a html generation of the C locale's version of the DocBook,
# using our custom stylesheet and graphics:
html/index.html: $(srcdir)/C/index.docbook
	$(AM_V_at)rm -fr html
	$(AM_V_at)$(MKDIR_P) html
	$(AM_V_GEN)$(XSLTPROC) $(xslt_params) -o html/ --xinclude --catalogs \
		'$(DOCBOOK_STYLESHEET_HTML)' $<

# TODO: I'm not sure how useful this output is, or what we can do with it. murrayc.
epub_via_xsl: $(srcdir)/C/index.docbook
	$(AM_V_at)rm -fr epub
	$(AM_V_at)$(MKDIR_P) epub
	$(AM_V_GEN)$(XSLTPROC) $(xslt_params) -o epub/ --xinclude --catalogs \
		'$(DOCBOOK_STYLESHEET_EPUB)' $<

# This epub/mobi generation is experimental. murrayc.
epub: $(srcdir)/gtkmm-tutorial.epub

# Create an epub generation of the C locale's version of the DocBook,
# using our custom stylesheet and graphics.
# This apparently uses the XSL stylesheets that we try to use in epub_via_xsl above.
gtkmm-tutorial.epub: $(srcdir)/C/index.docbook
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
$(srcdir)/C/index.docbook: $(srcdir)/C/index-in.docbook $(srcdir)/insert_example_code.pl
	$(AM_V_GEN)$(PERL) -- $(srcdir)/insert_example_code.pl $(top_srcdir)/examples/book $< >$@

validate_original: $(srcdir)/C/index-in.docbook
	$(XMLLINT) --xinclude --postvalid --noout $<

validate: $(srcdir)/C/index.docbook
	$(XMLLINT) --xinclude --postvalid --noout $<

# we need to produce a full examples with all of the XIncludes done so that it
# can be processed for PDF
C/programming-with-gtkmm-onefile.xml: $(srcdir)/C/index.docbook
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
