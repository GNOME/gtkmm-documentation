## This file is part of gtkmm-documentation.

AUTOMAKE_OPTIONS = subdir-objects

AM_CPPFLAGS = $(GTKMM_CFLAGS)
AM_CXXFLAGS = $(EXAMPLES_WXXFLAGS)
LDADD       = $(GTKMM_LIBS)

check_PROGRAMS = \
  step1/exampleapp \
  step2/exampleapp \
  step3/exampleapp

dist_noinst_DATA = \
  README \
  step1/exampleapp.desktop \
  step1/exampleapp.png \
  step1/Makefile.example \
  $(STEP2_RESOURCES) \
  step2/Makefile.example \
  $(STEP3_RESOURCES) \
  step3/Makefile.example

step1_exampleapp_SOURCES = \
  step1/exampleapplication.cc \
  step1/exampleapplication.h \
  step1/exampleappwindow.cc \
  step1/exampleappwindow.h \
  step1/main.cc

step2_exampleapp_SOURCES = \
  step2/resources.c \
  step2/exampleapplication.cc \
  step2/exampleapplication.h \
  step2/exampleappwindow.cc \
  step2/exampleappwindow.h \
  step2/main.cc

step3_exampleapp_SOURCES = \
  step3/resources.c \
  step3/exampleapplication.cc \
  step3/exampleapplication.h \
  step3/exampleappwindow.cc \
  step3/exampleappwindow.h \
  step3/main.cc

MAINTAINERCLEANFILES = \
  step2/resources.c \
  step3/resources.c

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

