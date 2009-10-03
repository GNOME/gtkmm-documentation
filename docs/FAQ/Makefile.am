## This file is part of gtkmm-documentation.

gtkmm_docdir = $(datadir)/doc/gtkmm-2.4
faq_htmldir  = $(gtkmm_docdir)/FAQ/html
docbook_docs = gtkmm-faq.xml

DOCBOOK_STYLESHEET ?= http://docbook.sourceforge.net/release/xsl/current/html/chunk.xsl
XSLTPROC = xsltproc

# Function: $(call vpath_listall,PATTERN ...)
# Get all filenames which match a PATTERN from the list.  Look for files
# relative to either the current directory or $(srcdir).  Strip $(srcdir)/
# again before returning and remove any duplicates.
vpath_srclist = $(patsubst $(srcdir)/%,%,$(wildcard $(addprefix $(srcdir)/,$(1))))
vpath_listall = $(sort $(wildcard $(1)) $(if $(srcdir:.=),$(vpath_srclist)))

faq_html_files = $(call vpath_listall,html/*.html)
faq_html_inst  = $(foreach file,$(faq_html_files),$(or $(wildcard $(file)),$(srcdir)/$(file)))

dist_noinst_DATA = $(docbook_docs) $(call vpath_listall,html/*.html)

MAINTAINERCLEANFILES = html/*.html $(srcdir)/html/*.html

all-local: html/index.html

install-data-local: install-faq

uninstall-local: uninstall-faq

install-faq: html/index.html
	@$(NORMAL_INSTALL)
	$(MKDIR_P) '$(DESTDIR)$(faq_htmldir)'
	$(INSTALL_DATA) $(faq_html_inst) '$(DESTDIR)$(faq_htmldir)/'

uninstall-faq:
	@$(NORMAL_UNINSTALL)
	rm -f '$(DESTDIR)$(faq_htmldir)'/*.html

html/index.html: $(docbook_docs)
	$(AM_V_at)rm -fr html
	$(AM_V_at)$(MKDIR_P) html
	$(AM_V_GEN)$(XSLTPROC) -o html/ --catalogs $(DOCBOOK_STYLESHEET) $<

.PHONY: install-faq uninstall-faq

# Instruct GNU make to delete the targets of a rule after it failed, in
# order to avoid the complication of handling that situation manually.
.DELETE_ON_ERROR:
