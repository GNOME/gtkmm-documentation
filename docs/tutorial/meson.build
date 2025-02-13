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
allow_network_access = get_option('allow-network-access') ? 'true' : 'false'

# Check if xmllint can be used.
if xmllint.found()
  can_parse_and_validate = run_command(
    python3, tutorial_custom_cmd, 'xmllint',
    validate,
    allow_network_access,
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
can_build_pdf = xsltproc.found() and (dblatex.found() or \
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
  'custom_css_name.png',
  'dialogs_about.png',
  'dialogs_alertdialog.png',
  'dialogs_colordialog.png',
  'dialogs_filedialog.png',
  'dialogs_fontdialog.png',
  'dialogs_windowdialog.png',
  'drag_and_drop.png',
  'drawingarea_arcs.png',
  'drawingarea_curve.png',
  'drawingarea_image.png',
  'drawingarea_lines.png',
  'drawingarea_pango_text.png',
  'drawingarea_thin_lines.png',
  'dropdown_complex.png',
  'dropdown_search_font.png',
  'dropdown_search_string.png',
  'dropdown_string.png',
  'entry.png',
  'entry_completion.png',
  'entry_icon.png',
  'entry_progress.png',
  'events_mouse.png',
  'events_propagation.png',
  'events_simple.png',
  'frame.png',
  'grid.png',
  'helloworld.png',
  'helloworld2.png',
  'i18n.png',
  'infobar.png',
  'label.png',
  'listmodel_columnview.png',
  'listmodel_filter.png',
  'listmodel_gridview.png',
  'listmodel_listview.png',
  'listmodel_sort.png',
  'listmodel_tree.png',
  'main_menu.png',
  'menu_popup.png',
  'menus_and_toolbars.png',
  'multithread.png',
  'notebook.png',
  'paned.png',
  'printing_printdialog.png',
  'printing_simple.png',
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
  install_tag: 'doc',
)

# Install extra files in the C locale XML file directory.
install_data(tutorial_C_figures,
  install_dir: tutorial_C_xmldir / 'figures',
  install_tag: 'doc',
)

# Create an html version of the C locale's version of the DocBook.
html_target = custom_target('html_index.html',
  input: index_docbook,
  output: 'html',
  command: [
    python3, tutorial_custom_cmd, 'html',
    allow_network_access,
    meson.current_source_dir() / 'book.xsl',
    '@INPUT@',
    '@OUTPUT@',    
  ],
  build_by_default: true,
  install: true,
  install_dir: tutorialdir,
  install_tag: 'doc',
)

# highlight.js files were downloaded from
# https://highlightjs.org/download. Choose 'cpp' option (which
# contains only C++ related files) and click 'Download'. This should
# download a .zip containing .js and huge set of .css files (like
# 'intellij-light.min.css' etc). 'highlight.min.css' is actually
# 'intellij-light.min.css'.
style_files = [
  'style.css',
  'highlight.js' / 'highlight.min.css',
  'highlight.js' / 'highlight.min.js',
]

# Install extra files in the html directory.
install_data(style_files,
  install_dir: tutorial_htmldir,
  install_tag: 'doc',
)
install_data(tutorial_C_figures,
  install_dir: tutorial_figuresdir,
  install_tag: 'doc',
)
install_data(tutorial_icons,
  install_dir: tutorial_iconsdir,
  install_tag: 'doc',
)

# Copy extra files to the html directory in the build tree.
# The html files can then be viewed correctly formatted without installing.
current_build_dir_html = meson.current_build_dir() / 'html'
custom_target('copy-doc-files',
  input: html_target,
  output: 'copy_doc_files.stamp',
  command: [
    python3, tutorial_custom_cmd, 'copy_files',
    meson.current_source_dir(),
    '@OUTPUT@',
    current_build_dir_html,
    style_files,
    current_build_dir_html / 'figures',
    tutorial_C_figures,
    current_build_dir_html / 'icons',
    tutorial_icons,
  ],
  build_by_default: true,
  install: false,
)

if can_parse_and_validate
  # Parse and possibly validate the C locale's version of the DocBook.
  custom_target('C-xmllint',
    input: index_docbook,
    output: 'C_xmllint.stamp',
    command: [
      python3, tutorial_custom_cmd, 'xmllint',
      validate,
      allow_network_access,
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
      allow_network_access,
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
    install_tag: 'doc',
  )
  # Install extra symlinks in the translated XML file directory.
  # install_symlink() requires meson >= 0.61.0
  #foreach figure : tutorial_figurefiles
  #  install_symlink(figure,
  #    install_dir: tutorial_language_xmldir / 'figures',
  #    install_tag: 'doc',
  #    pointing_to: '..' / '..' / '..' / 'C' / gtkmm_tutorial / 'figures' / figure,
  #  )
  #endforeach
endforeach
