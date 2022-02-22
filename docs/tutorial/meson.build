# docs/tutorial

# input: install_datadir, gtkmm_pcname, tutorial_custom_cmd,
#        project_source_root, python3
# output: can_parse_and_validate, build_translations_by_default, can_build_translations,
#         build_pdf_by_default, can_build_pdf, tutorialdir

# xsltproc is required by tutorial_custom_cmd html.
xsltproc = find_program('xsltproc', required: true)

xmllint = find_program('xmllint', required: false)
can_parse_and_validate = xmllint.found()
validate = get_option('validation') ? 'true' : 'false'

# Check if xmllint can be used.
if xmllint.found()
  can_parse_and_validate = run_command(
    python3, tutorial_custom_cmd, 'xmllint',
    validate,
    meson.current_source_dir() / 'can_use_xmllint.xml',
    meson.current_build_dir() / 'can_use_xmllint.stamp',
    check: false,
  ).returncode() == 0
  if not can_parse_and_validate
    # The DocBook V5.0 package is called docbook5-xml in Ubuntu,
    # docbook5-schemas in Fedora. It may have other names in other distros.
    warning('Can\'t validate XML file.\n' +
      'xmllint does not support Relax NG schemas and DocBook V5.0.\n' +
      'DocBook V5.0 support may require docbook5-xml, docbook5-schemas or a similar package.'
    )
  endif
endif

can_build_translations = find_program('msgfmt', required: false).found() and \
                         find_program('itstool', required: false).found()
build_translations_by_default = get_option('build-translations')

dblatex = find_program('dblatex', required: false)
can_build_pdf = dblatex.found() or (xsltproc.found() and \
                find_program('fop', required: false).found())
build_pdf_by_default = get_option('build-pdf')

# Installation directories are relative to {prefix}.
gtkmm_tutorial = 'gtkmm-tutorial'
tutorialdir = install_datadir / 'doc' / gtkmm_pcname / 'tutorial'
tutorial_htmldir = tutorialdir / 'html'
tutorial_figuresdir = tutorial_htmldir / 'figures'
tutorial_iconsdir = tutorial_htmldir / 'icons'
tutorial_C_xmldir = install_datadir / 'help' / 'C' / gtkmm_tutorial

tutorial_figurefiles = [
  'alignment.png',
  'aspectframe.png',
  'assistant.png',
  'box_packing1.png',
  'box_packing2.png',
  'box_packing3.png',
  'buildapp_app_menu.png',
  'buildapp_header_bar.png',
  'buildapp_opening_files.png',
  'buildapp_populating_window.png',
  'buildapp_pref_dialog.png',
  'buildapp_properties.png',
  'buildapp_search_bar.png',
  'buildapp_side_bar.png',
  'buildapp_trivial_app.png',
  'buttonbox.png',
  'buttons.png',
  'cairo_clock.png',
  'cairo_joins.png',
  'checkbutton.png',
  'clipboard_ideal.png',
  'clipboard_simple.png',
  'combo.png',
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
  'dialogs_simple.png',
  'drag_and_drop.png',
  'drawingarea_arcs.png',
  'drawingarea_curve.png',
  'drawingarea_image.png',
  'drawingarea_lines.png',
  'drawingarea_pango_text.png',
  'drawingarea_text.png',
  'drawingarea_thin_lines.png',
  'entry.png',
  'entry_completion.png',
  'entry_icon.png',
  'entry_progress.png',
  'eventbox.png',
  'expander.png',
  'filechooserbutton.png',
  'frame.png',
  'grid.png',
  'helloworld.png',
  'helloworld2.png',
  'idle.png',
  'infobar.png',
  'keyboardevents_simple.png',
  'keyboardevents_propagation.png',
  'label.png',
  'main_menu.png',
  'menu_popup.png',
  'menus_and_toolbars.png',
  'menus_menu.png',
  'menus_menubar.png',
  'multithread.png',
  'notebook.png',
  'paned.png',
  'printing.png',
  'progressbar.png',
  'radiobuttons.png',
  'range_widgets.png',
  'recentchooserdialog.png',
  'scrolledwindow.png',
  'socket-fail.png',
  'socket.png',
  'spinbutton.png',
  'textview.png',
  'toolbar.png',
  'toolpalette.png',
  'tooltip.png',
  'treeview_combo_renderer.png',
  'treeview_draganddrop.png',
  'treeview_editablecells.png',
  'treeview_list.png',
  'treeview_popup.png',
  'treeview_tree.png',
  'update_ui.png',
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

if can_build_translations and build_translations_by_default
  # Get a list of translated languages.
  language_obj = run_command(
    python3, tutorial_custom_cmd, 'get_languages',
    meson.current_source_dir(),
    check: false,
  )
  if language_obj.stderr() != ''
    warning(language_obj.stderr())
  endif
  languages = language_obj.stdout().split()
else
  languages = []
endif

# Create a DocBook C locale XML file with the examples' source code included.
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
  build_by_default: true,
  install: true,
  install_dir: tutorial_C_xmldir,
)

# Install extra files in the C locale XML file directory.
install_data(tutorial_C_figures, install_dir: tutorial_C_xmldir / 'figures')

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

# Install extra files in the html directory.
install_data('style.css', install_dir: tutorial_htmldir)
install_data(tutorial_C_figures, install_dir: tutorial_figuresdir)
install_data(tutorial_icons, install_dir: tutorial_iconsdir)

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
  # Prefer dblatex, if both dblatex and fop are available.
  custom_target('C-pdf',
    input: index_docbook,
    output: 'programming-with-gtkmm.pdf',
    command: [
      python3, tutorial_custom_cmd,
      dblatex.found() ? 'dblatex' : 'fop',
      '@INPUT@',
      meson.current_source_dir() / 'C' / 'figures',
      '@OUTPUT@'
    ],
    build_by_default: build_pdf_by_default,
  )
endif

# gnome.yelp() is not used. After issue https://github.com/mesonbuild/meson/issues/2775
# was fixed in meson 0.61.0, gnome.yelp() can't be used on a generated XML file.
# See https://github.com/mesonbuild/meson/issues/10017

foreach language : languages
  # Create translated XML files.
  translated_xml_target = custom_target(language + '_xml_index.docbook',
    input: [language / language + '.po', index_docbook],
    output: language + '_xml.stamp',
    command: [
      python3, tutorial_custom_cmd, 'translate_xml',
      '@INPUT0@',
      '@INPUT1@',
      meson.current_build_dir() / language, # Absolute path
      '@OUTPUT@',
    ],
    build_by_default: true,
    install: false,
  )

  # Install the translated XML file.
  # Install extra symlinks in the translated XML file directory.
  tutorial_language_xmldir = install_datadir / 'help' / language / gtkmm_tutorial
  meson.add_install_script(
    python3, tutorial_custom_cmd, 'install',
    meson.current_build_dir() / language,
    tutorial_language_xmldir,
    'index.docbook',
    '..' / '..' / '..' / 'C' / gtkmm_tutorial / 'figures', # relative symlink dir
    tutorial_figurefiles,
  )
  # Install extra symlinks in the translated XML file directory.
  # install_symlink() requires meson >= 0.61.0
  #foreach figure : tutorial_figurefiles
  #  install_symlink(figure,
  #    install_dir: tutorial_language_xmldir / 'figures',
  #    pointing_to: '..' / '..' / '..' / 'C' / gtkmm_tutorial / 'figures' / figure,
  #  )
  #endforeach
endforeach
