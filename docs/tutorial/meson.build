# docs/tutorial

# input: gtkmm_datadir, gtkmm_pcname, tutorial_custom_cmd_sh
# output: tutorial_languages

xsltproc = find_program('xsltproc', required: true)
perl = find_program('perl', required: true)
xmllint = find_program('xmllint', required: false)

can_build_translations = find_program('msgfmt', required: false).found() and \
                         find_program('itstool', required: false).found()
build_translations_by_default = get_option('build-translations')

tutorial_languages = ['cs', 'de', 'el', 'es', 'fr', 'pt_BR', 'sl', 'zh_CN']

# Installation directories
tutorialdir = join_paths(gtkmm_datadir, 'doc', gtkmm_pcname, 'tutorial')
tutorial_htmldir = join_paths(tutorialdir, 'html')
tutorial_figuresdir = join_paths(tutorial_htmldir, 'figures')
tutorial_iconsdir = join_paths(tutorial_htmldir, 'icons')

tutorial_figurefiles = [
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
  'recentfiles.png',
  'scrolledwindow.png',
  'spinbutton.png',
  'textview.png',
  'toolbar.png',
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
foreach f : tutorial_figurefiles
  tutorial_figures += join_paths('C', 'figures', f)
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
  tutorial_icons += join_paths('icons', i)
endforeach

# Set the use.id.as.filename param so that we don't use the chapter / section
# number as the filename, otherwise the url will change every time anything is
# re-ordered or inserted in the documentation
xslt_params = [
  '--param', 'toc.section.depth', '1',
  '--stringparam', 'html.stylesheet', 'style.css',
  '--stringparam', 'admon.graphics', '1',
  '--stringparam', 'admon.graphics.path', 'icons/',
  '--stringparam', 'admon.graphics.extension', '.png',
  '--stringparam', 'chunker.output.indent', 'yes',
  '--stringparam', 'chunker.output.encoding', 'UTF-8',
  '--stringparam', 'navig.graphics', 'yes',
  '--stringparam', 'navig.graphics.extension', '.png',
  '--stringparam', 'navig.graphics.path', 'icons/',
  '--stringparam', 'toc.list.type', 'ul',
  '--stringparam', 'use.id.as.filename', '1',
]

index_docbook = custom_target('index.docbook',
  input: join_paths('C', 'index-in.docbook'),
  output: 'index.docbook',
  command: [
    perl, '--',
    join_paths(meson.current_source_dir(), 'insert_example_code.pl'),
    join_paths(meson.source_root(), 'examples', 'book'),
    '@INPUT@',
  ],
  capture: true,
  build_by_default: true
)

custom_target('html_index.html',
  input: index_docbook,
  output: 'html',
  command: [
    xsltproc,
    xslt_params,
    '-o', '@OUTPUT@/',
    '--xinclude',
    '--catalogs',
    'http://docbook.sourceforge.net/release/xsl/current/html/chunk.xsl',
    '@INPUT@',
  ],
  build_by_default: true,
  install: true,
  install_dir: tutorialdir
)

if xmllint.found()
  custom_target('C-xmllint',
    input: index_docbook,
    output: 'C_xmllint.stamp',
    command: [
      tutorial_custom_cmd_sh,
      'xmllint',
      '@INPUT@',
      '@OUTPUT@'
    ],
    build_by_default: true,
  )
endif

if can_build_translations
  foreach lang : tutorial_languages
    po2mo = custom_target(lang + '-po2mo',
      input: join_paths(lang, lang + '.po'),
      output: lang + '_mo.stamp',
      command: [
        tutorial_custom_cmd_sh,
        'po2mo',
        lang,
        meson.current_build_dir(),
        '@INPUT@',
        join_paths(meson.current_build_dir(), lang, lang + '.mo'),
        '@OUTPUT@'      
      ],
      build_by_default: build_translations_by_default,
    )

    lang_index_docbook = custom_target(lang + '-index.docbook',
      input: [po2mo, index_docbook],
      output: lang + '_docbook.stamp',
      command: [
        tutorial_custom_cmd_sh,
        'docbook',
        join_paths(meson.current_build_dir(), lang, lang + '.mo'),
        '@INPUT1@',
        join_paths(meson.current_build_dir(), lang),
        '@OUTPUT@'      
      ],
      build_by_default: build_translations_by_default,
    )

    if xmllint.found()
      custom_target(lang + '-xmllint',
        input: lang_index_docbook,
        output: lang + '_xmllint.stamp',
        command: [
          tutorial_custom_cmd_sh,
          'xmllint',
          join_paths(meson.current_build_dir(), lang, 'index.docbook'),
          '@OUTPUT@'
        ],
        build_by_default: build_translations_by_default,
      )
    endif
  endforeach # lang
endif # can_build_translations

install_data('style.css', install_dir: tutorial_htmldir)
install_data(tutorial_figures, install_dir: tutorial_figuresdir)
install_data(tutorial_icons, install_dir: tutorial_iconsdir)

