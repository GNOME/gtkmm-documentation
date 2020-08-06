## This file is part of gtkmm-documentation.

AUTOMAKE_OPTIONS = subdir-objects

AM_CPPFLAGS = $(GTKMM_CFLAGS)
AM_CXXFLAGS = $(EXAMPLES_WXXFLAGS)
LDADD       = $(GTKMM_LIBS)

check_PROGRAMS = \
  step1/exampleapp \
  step2/exampleapp \
  step3/exampleapp \
  step4/exampleapp \
  step5/exampleapp \
  step6/exampleapp \
  step7/exampleapp \
  step8/exampleapp \
  step9/exampleapp

check_DATA = $(GSCHEMAS_COMPILED)

dist_noinst_DATA = \
  README \
  step1/exampleapp.desktop.in \
  step1/exampleapp.png \
  step1/Makefile.example \
  $(STEP2_RESOURCES) \
  step2/Makefile.example \
  $(STEP3_RESOURCES) \
  step3/Makefile.example \
  $(STEP4_RESOURCES) \
  step4/Makefile.example \
  $(STEP5_RESOURCES) \
  step5/Makefile.example \
  $(STEP6_RESOURCES) \
  step6/Makefile.example \
  $(STEP7_RESOURCES) \
  step7/Makefile.example \
  $(STEP8_RESOURCES) \
  step8/Makefile.example \
  $(STEP9_RESOURCES) \
  step9/Makefile.example \
  $(gsettings_SCHEMAS)

# Distribute files needed when building with Meson.
EXTRA_DIST = \
  step1/install-cmd.py \
  step1/meson.build \
  step2/meson.build \
  step3/meson.build \
  step4/meson.build \
  step5/meson.build \
  step6/meson.build \
  step7/meson.build \
  step8/meson.build \
  step9/meson.build

step1_exampleapp_SOURCES = \
  step1/exampleapplication.cc \
  step1/exampleapplication.h \
  step1/exampleappwindow.cc \
  step1/exampleappwindow.h \
  step1/main.cc

nodist_step2_exampleapp_SOURCES = step2/resources.c
step2_exampleapp_SOURCES = \
  step2/exampleapplication.cc \
  step2/exampleapplication.h \
  step2/exampleappwindow.cc \
  step2/exampleappwindow.h \
  step2/main.cc

nodist_step3_exampleapp_SOURCES = step3/resources.c
step3_exampleapp_SOURCES = \
  step3/exampleapplication.cc \
  step3/exampleapplication.h \
  step3/exampleappwindow.cc \
  step3/exampleappwindow.h \
  step3/main.cc

nodist_step4_exampleapp_SOURCES = step4/resources.c
step4_exampleapp_SOURCES = \
  step4/exampleapplication.cc \
  step4/exampleapplication.h \
  step4/exampleappwindow.cc \
  step4/exampleappwindow.h \
  step4/main.cc

nodist_step5_exampleapp_SOURCES = step5/resources.c
step5_exampleapp_SOURCES = \
  step5/exampleapplication.cc \
  step5/exampleapplication.h \
  step5/exampleappwindow.cc \
  step5/exampleappwindow.h \
  step5/exampleappprefs.cc \
  step5/exampleappprefs.h \
  step5/main.cc

nodist_step6_exampleapp_SOURCES = step6/resources.c
step6_exampleapp_SOURCES = \
  step6/exampleapplication.cc \
  step6/exampleapplication.h \
  step6/exampleappwindow.cc \
  step6/exampleappwindow.h \
  step6/exampleappprefs.cc \
  step6/exampleappprefs.h \
  step6/main.cc

nodist_step7_exampleapp_SOURCES = step7/resources.c
step7_exampleapp_SOURCES = \
  step7/exampleapplication.cc \
  step7/exampleapplication.h \
  step7/exampleappwindow.cc \
  step7/exampleappwindow.h \
  step7/exampleappprefs.cc \
  step7/exampleappprefs.h \
  step7/main.cc

nodist_step8_exampleapp_SOURCES = step8/resources.c
step8_exampleapp_SOURCES = \
  step8/exampleapplication.cc \
  step8/exampleapplication.h \
  step8/exampleappwindow.cc \
  step8/exampleappwindow.h \
  step8/exampleappprefs.cc \
  step8/exampleappprefs.h \
  step8/main.cc

nodist_step9_exampleapp_SOURCES = step9/resources.c
step9_exampleapp_SOURCES = \
  step9/exampleapplication.cc \
  step9/exampleapplication.h \
  step9/exampleappwindow.cc \
  step9/exampleappwindow.h \
  step9/exampleappprefs.cc \
  step9/exampleappprefs.h \
  step9/main.cc

gsettings_SCHEMAS = \
  step5/org.gtkmm.exampleapp.gschema.xml \
  step6/org.gtkmm.exampleapp.gschema.xml \
  step7/org.gtkmm.exampleapp.gschema.xml \
  step8/org.gtkmm.exampleapp.gschema.xml \
  step9/org.gtkmm.exampleapp.gschema.xml

GSCHEMAS_COMPILED = \
  step5/gschemas.compiled \
  step6/gschemas.compiled \
  step7/gschemas.compiled \
  step8/gschemas.compiled \
  step9/gschemas.compiled

## $(dir $<) is the source directory, $(dir $@) is the build directory.
## They are different during make distcheck.
%/gschemas.compiled: %/org.gtkmm.exampleapp.gschema.xml
	$(AM_V_GEN) $(GLIB_COMPILE_SCHEMAS) --strict --dry-run --schema-file=$<
	@$(GLIB_COMPILE_SCHEMAS) --targetdir=$(dir $@) $(dir $<)

## In most programs you would use @GSETTINGS_RULES@ instead of some of the
## schema rules in this Makefile.am, but gtkmm-documentation is different.
## The GSettings schema files belong to the example programs. They shall not be
## installed. gschemas.compiled files shall be created only by make check.

DISTCLEANFILES = \
  step2/resources.c \
  step3/resources.c \
  step4/resources.c \
  step5/resources.c \
  step6/resources.c \
  step7/resources.c \
  step8/resources.c \
  step9/resources.c \
  $(GSCHEMAS_COMPILED)

STEP2_RESOURCES = \
  step2/exampleapp.gresource.xml \
  step2/window.ui

step2/resources.c: $(STEP2_RESOURCES)
	$(AM_V_GEN) $(GLIB_COMPILE_RESOURCES) --target=$@ --sourcedir=$(dir $<) --generate-source $<

STEP3_RESOURCES = \
  step3/exampleapp.gresource.xml \
  step3/window.ui

step3/resources.c: $(STEP3_RESOURCES)
	$(AM_V_GEN) $(GLIB_COMPILE_RESOURCES) --target=$@ --sourcedir=$(dir $<) --generate-source $<

STEP4_RESOURCES = \
  step4/exampleapp.gresource.xml \
  step4/window.ui \
  step4/gears_menu.ui

step4/resources.c: $(STEP4_RESOURCES)
	$(AM_V_GEN) $(GLIB_COMPILE_RESOURCES) --target=$@ --sourcedir=$(dir $<) --generate-source $<

STEP5_RESOURCES = \
  step5/exampleapp.gresource.xml \
  step5/window.ui \
  step5/gears_menu.ui \
  step5/prefs.ui

step5/resources.c: $(STEP5_RESOURCES)
	$(AM_V_GEN) $(GLIB_COMPILE_RESOURCES) --target=$@ --sourcedir=$(dir $<) --generate-source $<

STEP6_RESOURCES = \
  step6/exampleapp.gresource.xml \
  step6/window.ui \
  step6/gears_menu.ui \
  step6/prefs.ui

step6/resources.c: $(STEP6_RESOURCES)
	$(AM_V_GEN) $(GLIB_COMPILE_RESOURCES) --target=$@ --sourcedir=$(dir $<) --generate-source $<

STEP7_RESOURCES = \
  step7/exampleapp.gresource.xml \
  step7/window.ui \
  step7/gears_menu.ui \
  step7/prefs.ui

step7/resources.c: $(STEP7_RESOURCES)
	$(AM_V_GEN) $(GLIB_COMPILE_RESOURCES) --target=$@ --sourcedir=$(dir $<) --generate-source $<

STEP8_RESOURCES = \
  step8/exampleapp.gresource.xml \
  step8/window.ui \
  step8/gears_menu.ui \
  step8/prefs.ui

step8/resources.c: $(STEP8_RESOURCES)
	$(AM_V_GEN) $(GLIB_COMPILE_RESOURCES) --target=$@ --sourcedir=$(dir $<) --generate-source $<

STEP9_RESOURCES = \
  step9/exampleapp.gresource.xml \
  step9/window.ui \
  step9/gears_menu.ui \
  step9/prefs.ui \
  step9/exampleapp.png

step9/resources.c: $(STEP9_RESOURCES)
	$(AM_V_GEN) $(GLIB_COMPILE_RESOURCES) --target=$@ --sourcedir=$(dir $<) --generate-source $<

