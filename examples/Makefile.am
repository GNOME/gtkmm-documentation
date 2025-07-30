## This file is part of gtkmm-documentation.

SUBDIRS = book/buildapp

AUTOMAKE_OPTIONS = subdir-objects

AM_CPPFLAGS = -I$(top_builddir) $(GTHREAD_CFLAGS) $(GTKMM_CFLAGS)
AM_CXXFLAGS = $(EXAMPLES_WXXFLAGS)
LDADD       = $(GTKMM_LIBS)

check_PROGRAMS =					\
	book/actionbar/example				\
	book/application/simple/example \
	book/application/command_line_handling/example \
	book/application/menubar/example \
	book/aspectframe/example			\
	book/assistant/example				\
	book/base/base					\
	book/box/example				\
	book/builder/basic/example			\
	book/builder/derived/example			\
	book/buttons/button/buttons			\
	book/buttons/checkbutton/example		\
	book/buttons/radiobutton/radiobuttons		\
	book/buttons/scalebutton/example			\
	book/buttons/togglebutton/example		\
	book/clipboard/ideal/example			\
	book/clipboard/simple/example			\
	book/combobox/complex/example			\
	book/combobox/text/example			\
	book/combobox/entry_complex/example		\
	book/combobox/entry_text/example		\
	book/custom/custom_container/example		\
	book/custom/custom_css_name/example \
	book/custom/custom_widget/example		\
	book/dialogs/aboutdialog/example		\
	book/dialogs/alertdialog/example		\
	book/dialogs/colordialog/example	\
	book/dialogs/filedialog/example		\
	book/dialogs/fontdialog/example	\
	book/dialogs/windowdialog/example			\
	book/drag_and_drop/drag_and_drop		\
	book/drawingarea/arcs/drawingareaarcs		\
	book/drawingarea/clock/cairoclock		\
	book/drawingarea/curve/drawingareacurve		\
	book/drawingarea/image/drawingareaimage		\
	book/drawingarea/joins/cairojoins		\
	book/drawingarea/pango_text/example		\
	book/drawingarea/simple/drawingarea		\
	book/drawingarea/thin_lines/example		\
	book/dropdown/complex/example			\
	book/dropdown/search_font/example			\
	book/dropdown/search_string/example		\
	book/dropdown/string/example		\
	book/entry/completion/example			\
	book/entry/icon/example				\
	book/entry/progress/example			\
	book/entry/simple/example			\
	book/events/keyboard_propagation/example	\
	book/events/keyboard_simple/example	\
	book/events/mouse/example	\
	book/expander/example				\
	book/frame/example				\
	book/giomm/directory_list/example		\
	book/giomm/getline/getline			\
	book/giomm/monitor_directory/monitor_directory	\
	book/giomm/read_file/example			\
	book/giomm/read_file_async/example		\
	book/giomm/usage/usage				\
	book/giomm/volumes/example			\
	book/giomm/write_file/example			\
	book/grid/example				\
	book/headerbar/example				\
	book/helloworld/helloworld			\
	book/helloworld2/helloworld2			\
	book/i18n/example					\
	book/idle/idle					\
	book/infobar/example				\
	book/input/example				\
	book/label/example				\
	book/listbox_flowbox/flowbox/example \
	book/listbox_flowbox/listbox/example \
	book/listbox_flowbox/listmodel/example \
	book/listmodelviews/editable_cells/example \
	book/listmodelviews/filter/example \
	book/listmodelviews/gridview/example \
	book/listmodelviews/list_columnview/example \
	book/listmodelviews/list_listview/example \
	book/listmodelviews/sort/example \
	book/listmodelviews/tree_columnview/example \
	book/listmodelviews/tree_listview/example \
	book/menus/main_menu/main_menu			\
	book/menus/popup/popup				\
	book/menus_and_toolbars/example			\
	book/multithread/example			\
	book/notebook/example				\
	book/paned/example				\
	book/popover/example			\
	book/printing/advanced/example			\
	book/printing/print_dialog/example \
	book/printing/simple/example			\
	book/progressbar/example			\
	book/range_widgets/example			\
	book/recent_files/example \
	book/revealer/example				\
	book/scrolledwindow/example			\
	book/searchbar/example				\
	book/signals/custom/example			\
	book/spinbutton/example				\
	book/textview/example				\
	book/timeout/timeout				\
	book/toolbar/example				\
	book/tooltips/example				\
	book/treeview/combo_renderer/example		\
	book/treeview/custom_treemodel/example	\
	book/treeview/drag_and_drop/example		\
	book/treeview/editable_cells/example		\
	book/treeview/filter/example			\
	book/treeview/filter_modify/example		\
	book/treeview/list/example			\
	book/treeview/listviewtext/example		\
	book/treeview/modelsort/example			\
	book/treeview/popup/example			\
	book/treeview/tree/example			\
	book/update_ui/example				\
	others/calendar/calendar			\
	others/dnd/testdnd				\
	others/exception/exceptiontest			\
	others/tictactoe/ttt_test			\
	others/window/wheelbarrow

dist_noinst_DATA = \
	book/builder/basic/basic.ui \
	book/builder/derived/derived.ui \
	book/buttons/button/info.xpm		\
	book/custom/custom_css_name/custom_gtkmm.css	\
	$(DIALOGS_ABOUTDIALOG_RESOURCES) \
	$(DRAWINGAREA_IMAGE_RESOURCES) \
	book/listmodelviews/gridview/gnome-dice-1.svg		\
	book/listmodelviews/gridview/gnome-dice-2.svg		\
	book/listmodelviews/gridview/gnome-dice-3.svg		\
	book/listmodelviews/gridview/gnome-dice-4.svg		\
	book/listmodelviews/gridview/gnome-dice-5.svg		\
	book/listmodelviews/gridview/gnome-dice-6.svg		\
	book/listmodelviews/gridview/mozilla-firefox.png	\
	book/listmodelviews/gridview/xmms.xpm			\
	$(MENUS_AND_TOOLBARS_RESOURCES)

# The GLArea example can be built only if epoxy and glm are installed.
# The WebKit example can be built only if webkitgtk is installed.
# Meson can build them conditionally. Autotools can't.
dist_noinst_DATA += \
  book/glarea/colors.h \
  book/glarea/exampleglarea.cc \
  book/glarea/exampleglarea.h \
  book/glarea/examplewindow.cc \
  book/glarea/examplewindow.h \
  book/glarea/main.cc \
  book/glarea/shaders.h \
  others/webkit/examplewindow.cc \
  others/webkit/examplewindow.h \
  others/webkit/main.cc

book_actionbar_example_SOURCES = \
	book/actionbar/examplewindow.cc \
	book/actionbar/examplewindow.h \
	book/actionbar/main.cc

book_application_simple_example_SOURCES =		\
	book/application/simple/exampleapplication.cc	\
	book/application/simple/exampleapplication.h	\
	book/application/simple/examplewindow.cc	\
	book/application/simple/examplewindow.h	\
	book/application/simple/main.cc

book_application_command_line_handling_example_SOURCES =		\
	book/application/command_line_handling/exampleapplication.cc	\
	book/application/command_line_handling/exampleapplication.h	\
	book/application/command_line_handling/examplewindow.cc	\
	book/application/command_line_handling/examplewindow.h	\
	book/application/command_line_handling/main.cc

book_application_menubar_example_SOURCES =		\
	book/application/menubar/exampleapplication.cc	\
	book/application/menubar/exampleapplication.h	\
	book/application/menubar/examplewindow.cc	\
	book/application/menubar/examplewindow.h	\
	book/application/menubar/main.cc

book_aspectframe_example_SOURCES =		\
	book/aspectframe/examplewindow.cc	\
	book/aspectframe/examplewindow.h	\
	book/aspectframe/main.cc

book_assistant_example_SOURCES =		\
	book/assistant/exampleassistant.cc	\
	book/assistant/exampleassistant.h	\
	book/assistant/examplewindow.cc		\
	book/assistant/examplewindow.h		\
	book/assistant/main.cc

book_base_base_SOURCES = \
	book/base/base.cc

book_box_example_SOURCES =			\
	book/box/examplewindow.cc		\
	book/box/examplewindow.h		\
	book/box/main.cc			\
	book/box/packbox.cc			\
	book/box/packbox.h

book_builder_basic_example_SOURCES =		\
	book/builder/basic/main.cc

book_builder_derived_example_SOURCES =		\
	book/builder/derived/deriveddialog.cc	\
	book/builder/derived/deriveddialog.h	\
	book/builder/derived/derivedbutton.cc	\
	book/builder/derived/derivedbutton.h	\
	book/builder/derived/main.cc

book_buttons_button_buttons_SOURCES =		\
	book/buttons/button/buttons.cc		\
	book/buttons/button/buttons.h		\
	book/buttons/button/main.cc

book_buttons_checkbutton_example_SOURCES =		\
	book/buttons/checkbutton/examplewindow.cc	\
	book/buttons/checkbutton/examplewindow.h	\
	book/buttons/checkbutton/main.cc

book_buttons_radiobutton_radiobuttons_SOURCES =		\
	book/buttons/radiobutton/main.cc		\
	book/buttons/radiobutton/radiobuttons.cc	\
	book/buttons/radiobutton/radiobuttons.h

book_buttons_scalebutton_example_SOURCES =		\
	book/buttons/scalebutton/examplewindow.cc	\
	book/buttons/scalebutton/examplewindow.h	\
	book/buttons/scalebutton/main.cc

book_buttons_togglebutton_example_SOURCES =		\
	book/buttons/togglebutton/examplewindow.cc	\
	book/buttons/togglebutton/examplewindow.h	\
	book/buttons/togglebutton/main.cc

book_clipboard_ideal_example_SOURCES =		\
	book/clipboard/ideal/examplewindow.cc	\
	book/clipboard/ideal/examplewindow.h	\
	book/clipboard/ideal/main.cc

book_clipboard_simple_example_SOURCES =		\
	book/clipboard/simple/examplewindow.cc	\
	book/clipboard/simple/examplewindow.h	\
	book/clipboard/simple/main.cc

book_combobox_complex_example_SOURCES =		\
	book/combobox/complex/examplewindow.cc	\
	book/combobox/complex/examplewindow.h	\
	book/combobox/complex/main.cc

book_combobox_text_example_SOURCES =		\
	book/combobox/text/examplewindow.cc	\
	book/combobox/text/examplewindow.h	\
	book/combobox/text/main.cc

book_combobox_entry_complex_example_SOURCES =		\
	book/combobox/entry_complex/examplewindow.cc	\
	book/combobox/entry_complex/examplewindow.h	\
	book/combobox/entry_complex/main.cc

book_combobox_entry_text_example_SOURCES =		\
	book/combobox/entry_text/examplewindow.cc	\
	book/combobox/entry_text/examplewindow.h		\
	book/combobox/entry_text/main.cc

book_custom_custom_container_example_SOURCES =		\
	book/custom/custom_container/examplewindow.cc	\
	book/custom/custom_container/examplewindow.h	\
	book/custom/custom_container/main.cc		\
	book/custom/custom_container/mycontainer.cc	\
	book/custom/custom_container/mycontainer.h

book_custom_custom_css_name_example_SOURCES =		\
	book/custom/custom_css_name/examplewindow.cc	\
	book/custom/custom_css_name/examplewindow.h	\
	book/custom/custom_css_name/main.cc		\
	book/custom/custom_css_name/myextrainit.cc \
	book/custom/custom_css_name/myextrainit.h \
	book/custom/custom_css_name/mybutton.cc		\
	book/custom/custom_css_name/mybutton.h

book_custom_custom_widget_example_SOURCES =		\
	book/custom/custom_widget/examplewindow.cc	\
	book/custom/custom_widget/examplewindow.h	\
	book/custom/custom_widget/main.cc		\
	book/custom/custom_widget/mywidget.cc		\
	book/custom/custom_widget/mywidget.h

nodist_book_dialogs_aboutdialog_example_SOURCES = book/dialogs/aboutdialog/resources.c
book_dialogs_aboutdialog_example_SOURCES =		\
	book/dialogs/aboutdialog/examplewindow.cc	\
	book/dialogs/aboutdialog/examplewindow.h	\
	book/dialogs/aboutdialog/main.cc

book_dialogs_alertdialog_example_SOURCES =		\
	book/dialogs/alertdialog/examplewindow.cc	\
	book/dialogs/alertdialog/examplewindow.h	\
	book/dialogs/alertdialog/main.cc

book_dialogs_colordialog_example_SOURCES =		\
	book/dialogs/colordialog/examplewindow.cc	\
	book/dialogs/colordialog/examplewindow.h	\
	book/dialogs/colordialog/main.cc

book_dialogs_filedialog_example_SOURCES =	\
	book/dialogs/filedialog/examplewindow.cc	\
	book/dialogs/filedialog/examplewindow.h	\
	book/dialogs/filedialog/main.cc

book_dialogs_fontdialog_example_SOURCES =		\
	book/dialogs/fontdialog/examplewindow.cc	\
	book/dialogs/fontdialog/examplewindow.h	\
	book/dialogs/fontdialog/main.cc

book_dialogs_windowdialog_example_SOURCES =		\
	book/dialogs/windowdialog/examplewindow.cc	\
	book/dialogs/windowdialog/examplewindow.h	\
	book/dialogs/windowdialog/main.cc \
	book/dialogs/windowdialog/namedialog.cc	\
	book/dialogs/windowdialog/namedialog.h

book_drag_and_drop_drag_and_drop_SOURCES =	\
	book/drag_and_drop/dndwindow.cc		\
	book/drag_and_drop/dndwindow.h		\
	book/drag_and_drop/main.cc

book_drawingarea_arcs_drawingareaarcs_SOURCES =	\
	book/drawingarea/arcs/main.cc		\
	book/drawingarea/arcs/myarea.cc		\
	book/drawingarea/arcs/myarea.h

book_drawingarea_clock_cairoclock_SOURCES =	\
	book/drawingarea/clock/clock.cc		\
	book/drawingarea/clock/clock.h		\
	book/drawingarea/clock/main.cc

book_drawingarea_curve_drawingareacurve_SOURCES =	\
	book/drawingarea/curve/main.cc			\
	book/drawingarea/curve/myarea.cc		\
	book/drawingarea/curve/myarea.h

nodist_book_drawingarea_image_drawingareaimage_SOURCES = book/drawingarea/image/resources.c
book_drawingarea_image_drawingareaimage_SOURCES =	\
	book/drawingarea/image/main.cc			\
	book/drawingarea/image/myarea.cc		\
	book/drawingarea/image/myarea.h

book_drawingarea_joins_cairojoins_SOURCES =	\
	book/drawingarea/joins/main.cc		\
	book/drawingarea/joins/myarea.cc	\
	book/drawingarea/joins/myarea.h

book_drawingarea_pango_text_example_SOURCES =	\
	book/drawingarea/pango_text/main.cc		\
	book/drawingarea/pango_text/myarea.cc	\
	book/drawingarea/pango_text/myarea.h

book_drawingarea_simple_drawingarea_SOURCES =	\
	book/drawingarea/simple/main.cc		\
	book/drawingarea/simple/myarea.cc	\
	book/drawingarea/simple/myarea.h

book_drawingarea_thin_lines_example_SOURCES =	\
	book/drawingarea/thin_lines/main.cc		\
	book/drawingarea/thin_lines/examplewindow.cc	\
	book/drawingarea/thin_lines/examplewindow.h  \
	book/drawingarea/thin_lines/myarea.cc	\
	book/drawingarea/thin_lines/myarea.h

book_dropdown_complex_example_SOURCES =		\
	book/dropdown/complex/examplewindow.cc	\
	book/dropdown/complex/examplewindow.h	\
	book/dropdown/complex/main.cc

book_dropdown_search_font_example_SOURCES =		\
	book/dropdown/search_font/examplewindow.cc	\
	book/dropdown/search_font/examplewindow.h	\
	book/dropdown/search_font/main.cc

book_dropdown_search_string_example_SOURCES =		\
	book/dropdown/search_string/examplewindow.cc	\
	book/dropdown/search_string/examplewindow.h	\
	book/dropdown/search_string/main.cc

book_dropdown_string_example_SOURCES =		\
	book/dropdown/string/examplewindow.cc	\
	book/dropdown/string/examplewindow.h		\
	book/dropdown/string/main.cc

book_entry_completion_example_SOURCES =		\
	book/entry/completion/examplewindow.cc	\
	book/entry/completion/examplewindow.h	\
	book/entry/completion/main.cc

book_entry_icon_example_SOURCES =		\
	book/entry/icon/examplewindow.cc	\
	book/entry/icon/examplewindow.h		\
	book/entry/icon/main.cc

book_entry_progress_example_SOURCES =		\
	book/entry/progress/examplewindow.cc	\
	book/entry/progress/examplewindow.h	\
	book/entry/progress/main.cc

book_entry_simple_example_SOURCES =		\
	book/entry/simple/examplewindow.cc	\
	book/entry/simple/examplewindow.h	\
	book/entry/simple/main.cc

book_events_keyboard_propagation_example_SOURCES =		\
	book/events/keyboard_propagation/examplewindow.cc	\
	book/events/keyboard_propagation/examplewindow.h	\
	book/events/keyboard_propagation/main.cc

book_events_keyboard_simple_example_SOURCES =		\
	book/events/keyboard_simple/examplewindow.cc	\
	book/events/keyboard_simple/examplewindow.h	\
	book/events/keyboard_simple/main.cc

book_events_mouse_example_SOURCES =		\
	book/events/mouse/examplewindow.cc	\
	book/events/mouse/examplewindow.h	\
	book/events/mouse/main.cc

book_expander_example_SOURCES =		\
	book/expander/examplewindow.cc	\
	book/expander/examplewindow.h	\
	book/expander/main.cc

book_frame_example_SOURCES =		\
	book/frame/examplewindow.cc	\
	book/frame/examplewindow.h	\
	book/frame/main.cc

book_giomm_directory_list_example_LDADD = $(GIOMM_LIBS)
book_giomm_directory_list_example_SOURCES = \
	book/giomm/directory_list/main.cc

book_giomm_getline_getline_LDADD = $(GIOMM_LIBS)
book_giomm_getline_getline_SOURCES = \
	book/giomm/getline/getline.cc

book_giomm_monitor_directory_monitor_directory_LDADD = $(GIOMM_LIBS)
book_giomm_monitor_directory_monitor_directory_SOURCES = \
	book/giomm/monitor_directory/monitor_directory.cc

book_giomm_read_file_example_LDADD = $(GIOMM_LIBS)
book_giomm_read_file_example_SOURCES = \
	book/giomm/read_file/main.cc

book_giomm_read_file_async_example_LDADD = $(GIOMM_LIBS)
book_giomm_read_file_async_example_SOURCES = \
	book/giomm/read_file_async/main.cc

book_giomm_usage_usage_LDADD = $(GIOMM_LIBS)
book_giomm_usage_usage_SOURCES = \
	book/giomm/usage/usage.cc

book_giomm_volumes_example_LDADD = $(GIOMM_LIBS)
book_giomm_volumes_example_SOURCES = \
	book/giomm/volumes/main.cc

book_giomm_write_file_example_LDADD = $(GIOMM_LIBS)
book_giomm_write_file_example_SOURCES = \
	book/giomm/write_file/main.cc

book_headerbar_example_SOURCES = \
	book/headerbar/examplewindow.cc \
	book/headerbar/examplewindow.h \
	book/headerbar/main.cc

book_grid_example_SOURCES = \
	book/grid/examplewindow.cc \
	book/grid/examplewindow.h \
	book/grid/main.cc

book_helloworld_helloworld_SOURCES =	\
	book/helloworld/helloworld.cc	\
	book/helloworld/helloworld.h	\
	book/helloworld/main.cc

book_helloworld2_helloworld2_SOURCES =	\
	book/helloworld2/helloworld.cc	\
	book/helloworld2/helloworld.h	\
	book/helloworld2/main.cc

book_i18n_example_SOURCES =		\
	book/i18n/examplewindow.cc	\
	book/i18n/examplewindow.h	\
	book/i18n/main.cc

book_idle_idle_SOURCES =		\
	book/idle/idleexample.cc	\
	book/idle/idleexample.h		\
	book/idle/main.cc

book_infobar_example_SOURCES =		\
	book/infobar/examplewindow.cc	\
	book/infobar/examplewindow.h	\
	book/infobar/main.cc

book_input_example_SOURCES = \
	book/input/main.cc
if !MKFIFO_EXISTS
book_input_example_CXXFLAGS = -DDONT_HAVE_MKFIFO=1
endif

book_label_example_SOURCES =		\
	book/label/examplewindow.cc	\
	book/label/examplewindow.h	\
	book/label/main.cc

book_listbox_flowbox_flowbox_example_SOURCES =		\
	book/listbox_flowbox/flowbox/examplewindow.cc	\
	book//listbox_flowbox/flowbox/examplewindow.h	\
	book//listbox_flowbox/flowbox/main.cc

book_listbox_flowbox_listbox_example_SOURCES =		\
	book/listbox_flowbox/listbox/examplewindow.cc	\
	book/listbox_flowbox/listbox/examplewindow.h	\
	book/listbox_flowbox/listbox/examplerow.cc	\
	book/listbox_flowbox/listbox/examplerow.h	\
	book/listbox_flowbox/listbox/main.cc

book_listbox_flowbox_listmodel_example_SOURCES =		\
	book/listbox_flowbox/listmodel/examplewindow.cc	\
	book/listbox_flowbox/listmodel/examplewindow.h	\
	book/listbox_flowbox/listmodel/myobject.cc	\
	book/listbox_flowbox/listmodel/myobject.h	\
	book/listbox_flowbox/listmodel/main.cc

book_listmodelviews_editable_cells_example_SOURCES = \
	book/listmodelviews/editable_cells/examplewindow.cc \
	book/listmodelviews/editable_cells/examplewindow.h \
	book/listmodelviews/editable_cells/main.cc

book_listmodelviews_filter_example_SOURCES = \
	book/listmodelviews/filter/examplewindow.cc \
	book/listmodelviews/filter/examplewindow.h \
	book/listmodelviews/filter/main.cc

book_listmodelviews_gridview_example_SOURCES =		\
	book/listmodelviews/gridview/examplewindow.cc	\
	book/listmodelviews/gridview/examplewindow.h	\
	book/listmodelviews/gridview/main.cc

book_listmodelviews_list_columnview_example_SOURCES = \
	book/listmodelviews/list_columnview/examplewindow.cc \
	book/listmodelviews/list_columnview/examplewindow.h \
	book/listmodelviews/list_columnview/main.cc

book_listmodelviews_list_listview_example_SOURCES = \
	book/listmodelviews/list_listview/examplewindow.cc \
	book/listmodelviews/list_listview/examplewindow.h \
	book/listmodelviews/list_listview/main.cc

book_listmodelviews_sort_example_SOURCES = \
	book/listmodelviews/sort/examplewindow.cc \
	book/listmodelviews/sort/examplewindow.h \
	book/listmodelviews/sort/main.cc

book_listmodelviews_tree_columnview_example_SOURCES = \
	book/listmodelviews/tree_columnview/examplewindow.cc \
	book/listmodelviews/tree_columnview/examplewindow.h \
	book/listmodelviews/tree_columnview/main.cc

book_listmodelviews_tree_listview_example_SOURCES = \
	book/listmodelviews/tree_listview/examplewindow.cc \
	book/listmodelviews/tree_listview/examplewindow.h \
	book/listmodelviews/tree_listview/main.cc

book_menus_main_menu_main_menu_SOURCES =	\
	book/menus/main_menu/exampleapplication.cc	\
	book/menus/main_menu/exampleapplication.h	\
	book/menus/main_menu/examplewindow.cc	\
	book/menus/main_menu/examplewindow.h	\
	book/menus/main_menu/main.cc

book_menus_popup_popup_SOURCES =		\
	book/menus/popup/examplewindow.cc	\
	book/menus/popup/examplewindow.h	\
	book/menus/popup/main.cc

nodist_book_menus_and_toolbars_example_SOURCES = book/menus_and_toolbars/resources.c
book_menus_and_toolbars_example_SOURCES =	\
	book/menus_and_toolbars/examplewindow.cc\
	book/menus_and_toolbars/examplewindow.h	\
	book/menus_and_toolbars/main.cc

book_multithread_example_SOURCES =	\
	book/multithread/examplewindow.cc\
	book/multithread/examplewindow.h	\
	book/multithread/exampleworker.cc\
	book/multithread/exampleworker.h	\
	book/multithread/main.cc
book_multithread_example_CXXFLAGS = -pthread

book_notebook_example_SOURCES =		\
	book/notebook/examplewindow.cc	\
	book/notebook/examplewindow.h	\
	book/notebook/main.cc

book_paned_example_SOURCES =		\
	book/paned/examplewindow.cc	\
	book/paned/examplewindow.h	\
	book/paned/main.cc		\
	book/paned/messageslist.cc	\
	book/paned/messageslist.h	\
	book/paned/messagetext.cc	\
	book/paned/messagetext.h

book_popover_example_SOURCES =		\
	book/popover/examplewindow.cc		\
	book/popover/examplewindow.h		\
	book/popover/main.cc

book_printing_advanced_example_SOURCES =		\
	book/printing/advanced/examplewindow.cc		\
	book/printing/advanced/examplewindow.h		\
	book/printing/advanced/main.cc			\
	book/printing/advanced/previewdialog.cc		\
	book/printing/advanced/previewdialog.h		\
	book/printing/advanced/printformoperation.cc	\
	book/printing/advanced/printformoperation.h

book_printing_print_dialog_example_SOURCES = \
	book/printing/print_dialog/examplewindow.cc \
	book/printing/print_dialog/examplewindow.h \
	book/printing/print_dialog/main.cc \
	book/printing/print_dialog/printformdialog.cc \
	book/printing/print_dialog/printformdialog.h

book_printing_simple_example_SOURCES =			\
	book/printing/simple/examplewindow.cc		\
	book/printing/simple/examplewindow.h		\
	book/printing/simple/main.cc			\
	book/printing/simple/printformoperation.cc	\
	book/printing/simple/printformoperation.h

book_progressbar_example_SOURCES =		\
	book/progressbar/examplewindow.cc	\
	book/progressbar/examplewindow.h	\
	book/progressbar/main.cc

book_range_widgets_example_SOURCES =		\
	book/range_widgets/examplewindow.cc	\
	book/range_widgets/examplewindow.h	\
	book/range_widgets/main.cc

book_recent_files_example_SOURCES =		\
	book/recent_files/examplewindow.cc	\
	book/recent_files/examplewindow.h	\
	book/recent_files/main.cc

book_revealer_example_SOURCES =		\
	book/revealer/examplewindow.cc	\
	book/revealer/examplewindow.h	\
	book/revealer/main.cc

book_scrolledwindow_example_SOURCES =		\
	book/scrolledwindow/examplewindow.cc	\
	book/scrolledwindow/examplewindow.h	\
	book/scrolledwindow/main.cc

book_searchbar_example_SOURCES =	\
	book/searchbar/examplewindow.cc	\
	book/searchbar/examplewindow.h	\
	book/searchbar/main.cc

book_signals_custom_example_SOURCES =	\
	book/signals/custom/client.cc	\
	book/signals/custom/client.h	\
	book/signals/custom/main.cc	\
	book/signals/custom/server.cc	\
	book/signals/custom/server.h

book_spinbutton_example_SOURCES =		\
	book/spinbutton/examplewindow.cc	\
	book/spinbutton/examplewindow.h		\
	book/spinbutton/main.cc

book_textview_example_SOURCES =		\
	book/textview/examplewindow.cc	\
	book/textview/examplewindow.h	\
	book/textview/main.cc

book_timeout_timeout_SOURCES =		\
	book/timeout/main.cc		\
	book/timeout/timerexample.cc	\
	book/timeout/timerexample.h

book_toolbar_example_SOURCES =		\
	book/toolbar/examplewindow.cc	\
	book/toolbar/examplewindow.h	\
	book/toolbar/main.cc

book_tooltips_example_SOURCES =		\
	book/tooltips/examplewindow.cc	\
	book/tooltips/examplewindow.h	\
	book/tooltips/main.cc

book_treeview_combo_renderer_example_SOURCES =		\
	book/treeview/combo_renderer/examplewindow.cc	\
	book/treeview/combo_renderer/examplewindow.h	\
	book/treeview/combo_renderer/main.cc

book_treeview_custom_treemodel_example_SOURCES = \
	book/treeview/custom_treemodel/examplewindow.cc \
	book/treeview/custom_treemodel/examplewindow.h \
	book/treeview/custom_treemodel/main.cc \
	book/treeview/custom_treemodel/exampletreemodel.cc \
	book/treeview/custom_treemodel/exampletreemodel.h

book_treeview_drag_and_drop_example_SOURCES =		\
	book/treeview/drag_and_drop/examplewindow.cc	\
	book/treeview/drag_and_drop/examplewindow.h	\
	book/treeview/drag_and_drop/main.cc		\
	book/treeview/drag_and_drop/treemodel_dnd.cc	\
	book/treeview/drag_and_drop/treemodel_dnd.h

book_treeview_editable_cells_example_SOURCES =		\
	book/treeview/editable_cells/examplewindow.cc	\
	book/treeview/editable_cells/examplewindow.h	\
	book/treeview/editable_cells/main.cc

book_treeview_filter_example_SOURCES =		\
	book/treeview/filter/examplewindow.cc	\
	book/treeview/filter/examplewindow.h	\
	book/treeview/filter/main.cc

book_treeview_filter_modify_example_SOURCES =		\
	book/treeview/filter_modify/examplewindow.cc	\
	book/treeview/filter_modify/examplewindow.h	\
	book/treeview/filter_modify/main.cc

book_treeview_list_example_SOURCES =		\
	book/treeview/list/examplewindow.cc	\
	book/treeview/list/examplewindow.h	\
	book/treeview/list/main.cc

book_treeview_listviewtext_example_SOURCES =		\
	book/treeview/listviewtext/examplewindow.cc	\
	book/treeview/listviewtext/examplewindow.h	\
	book/treeview/listviewtext/main.cc

book_treeview_modelsort_example_SOURCES =		\
	book/treeview/modelsort/examplewindow.cc	\
	book/treeview/modelsort/examplewindow.h		\
	book/treeview/modelsort/main.cc

book_treeview_popup_example_SOURCES =			\
	book/treeview/popup/examplewindow.cc		\
	book/treeview/popup/examplewindow.h		\
	book/treeview/popup/main.cc			\
	book/treeview/popup/treeview_withpopup.cc	\
	book/treeview/popup/treeview_withpopup.h

book_treeview_tree_example_SOURCES =		\
	book/treeview/tree/examplewindow.cc	\
	book/treeview/tree/examplewindow.h	\
	book/treeview/tree/main.cc

book_update_ui_example_SOURCES =	\
	book/update_ui/examplewindow.cc	\
	book/update_ui/examplewindow.h	\
	book/update_ui/main.cc

others_calendar_calendar_SOURCES = \
	others/calendar/calendar.cc

others_dnd_testdnd_SOURCES =	\
	others/dnd/dnd_images.h	\
	others/dnd/dndwindow.cc	\
	others/dnd/dndwindow.h	\
	others/dnd/main.cc

others_exception_exceptiontest_SOURCES = \
	others/exception/exceptiontest.cc

others_tictactoe_ttt_test_SOURCES =	\
	others/tictactoe/tictactoe.cc	\
	others/tictactoe/tictactoe.h	\
	others/tictactoe/ttt_test.cc

others_window_wheelbarrow_SOURCES = \
	others/window/wheelbarrow.cc

DISTCLEANFILES = \
  book/dialogs/aboutdialog/resources.c \
  book/drawingarea/image/resources.c \
  book/menus_and_toolbars/resources.c

DIALOGS_ABOUTDIALOG_RESOURCES = \
  book/dialogs/aboutdialog/aboutdialog.gresource.xml \
  book/dialogs/aboutdialog/gtkmm_logo.gif

book/dialogs/aboutdialog/resources.c: $(DIALOGS_ABOUTDIALOG_RESOURCES)
	$(AM_V_GEN) $(GLIB_COMPILE_RESOURCES) --target=$@ --sourcedir=$(dir $<) --generate-source $<

DRAWINGAREA_IMAGE_RESOURCES = \
  book/drawingarea/image/image.gresource.xml \
  book/drawingarea/image/fractal_image.png

book/drawingarea/image/resources.c: $(DRAWINGAREA_IMAGE_RESOURCES)
	$(AM_V_GEN) $(GLIB_COMPILE_RESOURCES) --target=$@ --sourcedir=$(dir $<) --generate-source $<

MENUS_AND_TOOLBARS_RESOURCES = \
  book/menus_and_toolbars/toolbar.gresource.xml \
  book/menus_and_toolbars/rain.png \
  book/menus_and_toolbars/toolbar.ui

book/menus_and_toolbars/resources.c: $(MENUS_AND_TOOLBARS_RESOURCES)
	$(AM_V_GEN) $(GLIB_COMPILE_RESOURCES) --target=$@ --sourcedir=$(dir $<) --generate-source $<
