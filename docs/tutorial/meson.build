# docs/tutorial

# input: gnome, install_datadir, gtkmm_pcname, tutorial_custom_cmd,
#        project_source_root, python3
# output: can_parse_and_validate, build_translations_by_default, can_build_translations,
#         build_pdf_by_default, can_build_pdf, tutorialdir

# xsltproc is required by tutorial_custom_cmd html.
xsltproc = find_program('xsltproc', required: true)
xmllint = find_program('xmllint', required: false)

can_parse_and_validate = xmllint.found()

can_build_translations = find_program('msgfmt', required: false).found() and \
                         find_program('itstool', required: false).found()
build_translations_by_default = get_option('build-translations')
validate = get_option('validation') ? 'true' : 'false'

dblatex = find_program('dblatex', required: false)
can_build_pdf = dblatex.found() or (xmllint.found() and \
                find_program('docbook2pdf', required: false).found())
build_pdf_by_default = get_option('build-pdf')

# Installation directories are relative to {prefix}.
tutorialdir = install_datadir / 'doc' / gtkmm_pcname / 'tutorial'
tutorial_htmldir = tutorialdir / 'html'
tutorial_figuresdir = tutorial_htmldir / 'figures'
tutorial_iconsdir = tutorial_htmldir / 'icons'

tutorial_figurefiles = [
  'aspectframe.png',
  'assistant.png',
  'box_packing1.png',
  'box_packing2.png',
  'buildapp_menu.png',
  'buildapp_header_bar.png',
  'buildapp_opening_files.png',
  'buildapp_populating_window.png',
  'buildapp_pref_dialog.png',
  'buildapp_properties.png',
  'buildapp_search_bar.png',
  'buildapp_side_bar.png',
  'buildapp_trivial_app.png',
  'buttons.png',
  'cairo_clock.png',
  'cairo_joins.png',
  'checkbutton.png',
  'clipboard_ideal.png',
  'clipboard_simple.png',
  'combobox_complex.png',
  'combobox_text.png',
  'comboboxentry_complex.png',
  'comboboxentry_text.png',
  'custom_container.png',
  'custom_widget.png',
  'dialogs_about.png',
  'dialogs_colorchooserdialog.png',
  'dialogs_filechooser.png',
  'dialogs_fontchooserdialog.png',
  'dialogs_messagedialog.png',
  'drag_and_drop.png',
  'drawingarea_arcs.png',
  'drawingarea_curve.png',
  'drawingarea_image.png',
  'drawingarea_lines.png',
  'drawingarea_pango_text.png',
  'drawingarea_thin_lines.png',
  'entry.png',
  'entry_completion.png',
  'entry_icon.png',
  'entry_progress.png',
  'frame.png',
  'grid.png',
  'helloworld.png',
  'helloworld2.png',
  'infobar.png',
  'keyboardevents_simple.png',
  'keyboardevents_propagation.png',
  'label.png',
  'main_menu.png',
  'menu_popup.png',
  'menus_and_toolbars.png',
  'multithread.png',
  'notebook.png',
  'paned.png',
  'printing.png',
  'progressbar.png',
  'radiobuttons.png',
  'range_widgets.png',
  'recentfiles.png',
  'scrolledwindow.png',
  'spinbutton.png',
  'textview.png',
  'tooltip.png',
  'treeview_draganddrop.png',
  'treeview_editablecells.png',
  'treeview_list.png',
  'treeview_popup.png',
  'treeview_tree.png',
]
tutorial_figures = []
tutorial_C_figures = []
foreach f : tutorial_figurefiles
  tutorial_figures += 'figures' / f
  tutorial_C_figures += 'C' / 'figures' / f
endforeach

tutorial_iconfiles = [
  'caution.png',
  'home.png',
  'important.png',
  'next.png',
  'note.png',
  'prev.png',
  'tip.png',
  'up.png',
  'warning.png',
]
tutorial_icons = []
foreach i : tutorial_iconfiles
  tutorial_icons += 'icons' / i
endforeach

# Create a DocBook C locale XML file with the examples' source code included.
# Copy it to the source directory, where gnome.yelp() expects to find it.
index_docbook = custom_target('index.docbook',
  input: 'C' / 'index-in.docbook',
  output: 'index.docbook',
  command: [
    python3, tutorial_custom_cmd, 'insert_example_code',
    meson.current_source_dir(),
    project_source_root / 'examples' / 'book',
    '@INPUT@',
    '@OUTPUT@',
  ],
  build_by_default: true
)

# Create an html version of the C locale's version of the DocBook.
custom_target('html_index.html',
  input: index_docbook,
  output: 'html',
  command: [
    python3, tutorial_custom_cmd, 'html',
    '@INPUT@',
    '@OUTPUT@',    
  ],
  build_by_default: true,
  install: true,
  install_dir: tutorialdir
)

if can_parse_and_validate
  # Parse and possibly validate the C locale's version of the DocBook.
  custom_target('C-xmllint',
    input: index_docbook,
    output: 'C_xmllint.stamp',
    command: [
      python3, tutorial_custom_cmd, 'xmllint',
      validate,
      '@INPUT@',
      '@OUTPUT@'
    ],
    build_by_default: true,
  )
endif

if can_build_pdf
  # Create a PDF file of the C locale's version of the DocBook.
  # Prefer dblatex, if both dblatex and docbook2pdf are available.
  custom_target('C-pdf',
    input: index_docbook,
    output: 'programming-with-gtkmm.pdf',
    command: [
      python3, tutorial_custom_cmd,
      dblatex.found() ? 'dblatex' : 'docbook2pdf',
      '@INPUT@',
      meson.current_source_dir() / 'C' / 'figures',
      '@OUTPUT@'
    ],
    build_by_default: build_pdf_by_default,
  )
endif

if can_build_translations and build_translations_by_default
  # Build translations. Install help documentation using Yelp.
  # C/index.docbook is copied from the source directory.
  # <lang>/index.docbook are written to the build directory, and copied from there.
  # It's bad that gnome.yelp() builds only at install time.
  # See https://github.com/mesonbuild/meson/issues/2775
  gnome.yelp('gtkmm-tutorial',
    sources: 'index.docbook',
    media: tutorial_figures,
    symlink_media: true
)
endif

# Install extra files in the html directory.
install_data('style.css', install_dir: tutorial_htmldir)
install_data(tutorial_C_figures, install_dir: tutorial_figuresdir)
install_data(tutorial_icons, install_dir: tutorial_iconsdir)

