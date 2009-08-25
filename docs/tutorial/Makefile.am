include $(top_srcdir)/docs/Makefile_web.am_fragment

gtkmm_tut_path = $(web_path_docs)tutorial

DOCBOOK_PHPWEBNOTES_TRANSFORM = docbook_phpwebnotes.xsl

# Function: $(call vpath_listall,PATTERN ...)
# Get all filenames which match a PATTERN from the list.  Look for files
# relative to either the current directory or $(srcdir).  Strip $(srcdir)/
# again before returning and remove any duplicates.
vpath_srclist = $(patsubst $(srcdir)/%,%,$(wildcard $(addprefix $(srcdir)/,$(1))))
vpath_listall = $(sort $(wildcard $(1)) $(if $(srcdir:.=),$(vpath_srclist)))

EXTRA_DIST = README insert_example_code.pl C/gtkmm-tut.xml C/gtkmm-tut-with-examples.xml $(DOCBOOK_PHPWEBNOTES_TRANSFORM)

DOCBOOK_STYLESHEET ?= http://docbook.sourceforge.net/release/xsl/current/html/chunk.xsl
XMLLINT = xmllint
XSLTPROC = xsltproc
DB2PDF = docbook2pdf

DOC_MODULE = gtkmm-tut-with-examples
DOC_ENTITIES =
DOC_INCLUDES =
DOC_FIGURES =					\
	figures/alignment.png			\
	figures/aspectframe.png			\
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
	figures/dialogs_about.png		\
	figures/dialogs_colorselectiondialog.png\
	figures/dialogs_filechooser.png		\
	figures/dialogs_fontselectiondialog.png	\
	figures/dialogs_messagedialog.png	\
	figures/dialogs_simple.png		\
	figures/drag_and_drop.png		\
	figures/drawingarea_arcs.png		\
	figures/drawingarea_curve.png		\
	figures/drawingarea_lines.png		\
	figures/drawingarea_text.png		\
	figures/entry.png			\
	figures/eventbox.png			\
	figures/expander.png			\
	figures/filechooserbutton.png		\
	figures/frame.png			\
	figures/helloworld.png			\
	figures/helloworld2.png			\
	figures/idle.png			\
	figures/label.png			\
	figures/main_menu.png			\
	figures/menu_popup.png			\
	figures/menus_and_toolbars.png		\
	figures/menus_menu.png			\
	figures/menus_menubar.png		\
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
	figures/table.png			\
	figures/textview.png			\
	figures/toolbar.png			\
	figures/treeview_combo_renderer.png	\
	figures/treeview_draganddrop.png	\
	figures/treeview_editablecells.png	\
	figures/treeview_list.png		\
	figures/treeview_popup.png		\
	figures/treeview_tree.png		\
	figures/update_ui.png

DOC_LINGUAS = de

DISTCLEANFILES = html/*.html
MAINTAINERCLEANFILES = $(srcdir)/html/*.html

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
tutorial_figuresdir = $(tutorialdir)/figures
tutorial_iconsdir   = $(tutorialdir)/icons

tutorial_html_files = $(call vpath_listall,html/*.html) style.css
tutorial_html_inst  = $(foreach\
	file,$(tutorial_html_files),$(or $(wildcard $(file)),$(srcdir)/$(file)))

dist_noinst_DATA = $(tutorial_html_files)

tutorial_figures_DATA = $(addprefix C/,$(DOC_FIGURES))
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

dist-hook: doc-dist-hook

all-local: $(addsuffix /gtkmm-tut-with-examples.xml,C $(DOC_LINGUAS)) html/index.html

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
	-test ! -r '$(DESTDIR)$(tutorial_htmldir)' || rmdir '$(DESTDIR)$(tutorial_htmldir)'

# Create a html generation of the C locale's version of the DocBook, 
# using our custom stylesheet and graphics:
# Set the use.id.as.filename param so that we don't use the chapter / section
# number as the filename, otherwise the url will change every time anything is
# re-ordered or inserted in the documentation
html/index.html: $(srcdir)/C/gtkmm-tut-with-examples.xml
	rm -fr html
	$(MKDIR_P) html
	$(XSLTPROC) $(xslt_params) -o html/ --xinclude --catalogs '$(DOCBOOK_STYLESHEET)' $<

# Make sure that the documentation will always have been generated before
# executing the commands of a rule that depends on files in html/.
html/%: | html/index.html

# Create a DocBook source file that doesn't have the examples' comments blocks:
$(srcdir)/C/gtkmm-tut-with-examples.xml: $(srcdir)/C/gtkmm-tut.xml $(srcdir)/insert_example_code.pl
	$(PERL) -- $(srcdir)/insert_example_code.pl $(top_srcdir)/examples/book $< >$@

validate_original: $(srcdir)/C/gtkmm-tut.xml
	$(XMLLINT) --xinclude --postvalid --noout $<

validate: $(srcdir)/C/gtkmm-tut-with-examples.xml
	$(XMLLINT) --xinclude --postvalid --noout $<

#gtkmm-tut-html.tar.gz: html/index.html
#	tar cf - C/figures html | gzip -c --best >$@

#post-html: html/index.html html/style.css pdf
#	rsync $(rsync_args) C/figures/*.png $$USER@$(web_host):$(gtkmm_tut_path)/figures/
#	rsync $(rsync_args) icons/*.png $$USER@$(web_host):$(gtkmm_tut_path)/icons/
#	rsync $(rsync_args) -r html/ $$USER@$(web_host):$(gtkmm_tut_path)/html/
#	rsync $(rsync_args) *.css $$USER@$(web_host):$(gtkmm_tut_path)/html/
#	rsync $(rsync_args) -r pdf/ $$USER@$(web_host):$(gtkmm_tut_path)/pdf/

# we need to produce a full examples with all of the XIncludes done so that it
# can processed for PDF
C/programming-with-gtkmm-pdf.xml: $(srcdir)/C/gtkmm-tut-with-examples.xml
	$(MKDIR_P) C
	$(XMLLINT) --xinclude --postvalid $< -o $@

# We have to generate the pdf in a subdirectory (e.g. pdf/) because the tutorial
# specifies the path to the figures as '../figures' so if we build it in this
# directory, it won't find the images.
pdf/programming-with-gtkmm-pdf.pdf: C/programming-with-gtkmm-pdf.xml
	$(MKDIR_P) pdf
	$(DB2PDF) --output pdf/ $<

#pdf: pdf/programming-with-gtkmm-pdf.pdf

#doc-clean:
#	-rm -f C/gtkmm-tut-with-examples.xml gtkmm-tut-html.tar.gz C/programming-with-gtkmm-pdf.xml
#	-rm -rf pdf

.PHONY: install-tutorial uninstall-tutorial

# Instruct GNU make to delete the targets of a rule after it failed, in
# order to avoid the complication of handling that situation manually.
.DELETE_ON_ERROR:
