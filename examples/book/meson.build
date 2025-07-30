# examples/book

# input: gnome, gtkmm_dep, giomm_dep, build_examples_by_default,
#        compile_schemas, copy_to_subdir, has_mkfifo, python3,
#        meson_backend, test_timeout, project_build_root
# input and output: examples_targets

subdir('buildapp')
subdir('giomm')
subdir('treeview')

exwindow_main = ['examplewindow.cc', 'main.cc']

examples_book = [
# [[dir-name], exe-name, [sources]]
  [['actionbar'], 'example', exwindow_main],
  [['application', 'simple'], 'example', ['exampleapplication.cc'] + exwindow_main],
  [['application', 'command_line_handling'], 'example', ['exampleapplication.cc'] + exwindow_main],
  [['application', 'menubar'], 'example', ['exampleapplication.cc'] + exwindow_main],
  [['aspectframe'], 'example', exwindow_main],
  [['assistant'], 'example', ['exampleassistant.cc'] + exwindow_main],
  [['base'], 'base', ['base.cc']],
  [['box'], 'example', exwindow_main + ['packbox.cc']],
  [['builder', 'basic'], 'example', ['main.cc']],
  [['builder', 'derived'], 'example', ['deriveddialog.cc', 'derivedbutton.cc', 'main.cc']],
  [['buttons', 'button'], 'buttons', ['buttons.cc', 'main.cc']],
  [['buttons', 'checkbutton'], 'example', exwindow_main],
  [['buttons', 'radiobutton'], 'radiobuttons', ['main.cc', 'radiobuttons.cc']],
  [['buttons', 'scalebutton'], 'example', exwindow_main],
  [['buttons', 'togglebutton'], 'example', exwindow_main],
  [['clipboard', 'ideal'], 'example', exwindow_main],
  [['clipboard', 'simple'], 'example', exwindow_main],
  [['combobox', 'complex'], 'example', exwindow_main],
  [['combobox', 'text'], 'example', exwindow_main],
  [['combobox', 'entry_complex'], 'example', exwindow_main],
  [['combobox', 'entry_text'], 'example', exwindow_main],
  [['custom', 'custom_container'], 'example', exwindow_main + ['mycontainer.cc']],
  [['custom', 'custom_css_name'], 'example',  exwindow_main + ['myextrainit.cc', 'mybutton.cc']],
  [['custom', 'custom_widget'], 'example', exwindow_main + ['mywidget.cc']],
  [['dialogs', 'aboutdialog'], 'example',  exwindow_main + ['aboutdialog.gresource.xml']],
  [['dialogs', 'alertdialog'], 'example', exwindow_main],
  [['dialogs', 'colordialog'], 'example', exwindow_main],
  [['dialogs', 'filedialog'], 'example', exwindow_main],
  [['dialogs', 'fontdialog'], 'example', exwindow_main],
  [['dialogs', 'windowdialog'], 'example', exwindow_main + ['namedialog.cc']],
  [['drag_and_drop'], 'drag_and_drop', ['dndwindow.cc', 'main.cc']],
  [['drawingarea', 'arcs'], 'drawingareaarcs', ['main.cc', 'myarea.cc']],
  [['drawingarea', 'clock'], 'cairoclock', ['clock.cc', 'main.cc']],
  [['drawingarea', 'curve'], 'drawingareacurve', ['main.cc', 'myarea.cc']],
  [['drawingarea', 'image'], 'drawingareaimage', ['main.cc', 'myarea.cc', 'image.gresource.xml']],
  [['drawingarea', 'joins'], 'cairojoins', ['main.cc', 'myarea.cc']],
  [['drawingarea', 'pango_text'], 'example', ['main.cc', 'myarea.cc']],
  [['drawingarea', 'simple'], 'drawingarea', ['main.cc', 'myarea.cc']],
  [['drawingarea', 'thin_lines'], 'example', exwindow_main + ['myarea.cc']],
  [['dropdown', 'complex'], 'example', exwindow_main],
  [['dropdown', 'search_font'], 'example', exwindow_main],
  [['dropdown', 'search_string'], 'example', exwindow_main],
  [['dropdown', 'string'], 'example', exwindow_main],
  [['entry', 'completion'], 'example', exwindow_main],
  [['entry', 'icon'], 'example', exwindow_main],
  [['entry', 'progress'], 'example', exwindow_main],
  [['entry', 'simple'], 'example', exwindow_main],
  [['events', 'keyboard_propagation'], 'example', exwindow_main],
  [['events', 'keyboard_simple'], 'example', exwindow_main],
  [['events', 'mouse'], 'example', exwindow_main],
  [['expander'], 'example', exwindow_main],
  [['frame'], 'example', exwindow_main],
  [['glarea'], 'example', ['exampleglarea.cc'] + exwindow_main],
  [['grid'], 'example', exwindow_main],
  [['headerbar'], 'example', exwindow_main],
  [['helloworld'], 'helloworld', ['helloworld.cc', 'main.cc']],
  [['helloworld2'], 'helloworld2', ['helloworld.cc', 'main.cc']],
  [['i18n'], 'example', exwindow_main],
  [['idle'], 'idle', ['idleexample.cc', 'main.cc']],
  [['infobar'], 'example', exwindow_main],
  [['input'], 'example', ['main.cc']],
  [['label'], 'example', exwindow_main],
  [['listbox_flowbox', 'flowbox'], 'example', exwindow_main],
  [['listbox_flowbox', 'listbox'], 'example', exwindow_main + ['examplerow.cc']],
  [['listbox_flowbox', 'listmodel'], 'example', exwindow_main + ['myobject.cc']],
  [['listmodelviews', 'editable_cells'], 'example', exwindow_main],
  [['listmodelviews', 'filter'], 'example', exwindow_main],
  [['listmodelviews', 'gridview'], 'example', exwindow_main],
  [['listmodelviews', 'list_columnview'], 'example', exwindow_main],
  [['listmodelviews', 'list_listview'], 'example', exwindow_main],
  [['listmodelviews', 'sort'], 'example', exwindow_main],
  [['listmodelviews', 'tree_columnview'], 'example', exwindow_main],
  [['listmodelviews', 'tree_listview'], 'example', exwindow_main],
  [['menus', 'main_menu'], 'main_menu', ['exampleapplication.cc'] + exwindow_main],
  [['menus', 'popup'], 'example', exwindow_main],
  [['menus_and_toolbars'], 'example', exwindow_main + ['toolbar.gresource.xml']],
  [['multithread'], 'example', exwindow_main + ['exampleworker.cc']],
  [['notebook'], 'example', exwindow_main],
  [['paned'], 'example', exwindow_main + ['messageslist.cc', 'messagetext.cc']],
  [['popover'], 'example', exwindow_main],
  [['printing', 'advanced'], 'example', exwindow_main + ['previewdialog.cc', 'printformoperation.cc']],
  [['printing', 'print_dialog'], 'example', exwindow_main + ['printformdialog.cc']],
  [['printing', 'simple'], 'example', exwindow_main + ['printformoperation.cc']],
  [['progressbar'], 'example', exwindow_main],
  [['range_widgets'], 'example', exwindow_main],
  [['recent_files'], 'example', exwindow_main],
  [['revealer'], 'example', exwindow_main],
  [['scrolledwindow'], 'example', exwindow_main],
  [['searchbar'], 'example', exwindow_main],
  [['signals', 'custom'], 'example', ['client.cc', 'main.cc', 'server.cc']],
  [['spinbutton'], 'example', exwindow_main],
  [['textview'], 'example', exwindow_main],
  [['timeout'], 'timeout', ['main.cc', 'timerexample.cc']],
  [['toolbar'], 'example', exwindow_main],
  [['tooltips'], 'example', exwindow_main],
  [['update_ui'], 'example', exwindow_main],
]

thread_dep = dependency('threads')
epoxy_dep = dependency('epoxy', required: false)
glm_dep = dependency('glm', required: false)

foreach ex : examples_book
  # The GLArea example can be built only if epoxy and glm are installed.
  if ex[0][0] == 'glarea' and not (epoxy_dep.found() and glm_dep.found() and \
    gtkmm_dep.version().version_compare('>=4.12.0'))
    message('The GLArea example can\'t be built.\n' + \
            '  epoxy or glm is not installed or gtkmm version < 4.12.0.')
    continue
  endif
  dir = ''
  foreach dir_part : ex[0]
    dir = dir / dir_part
  endforeach
  ex_name = (dir / ex[1]).underscorify()
  ex_sources = []
  resources = []
  foreach src : ex[2]
    if src.endswith('.gresource.xml')
      resources = gnome.compile_resources(dir.underscorify() + '_resources',
        dir / src,
        source_dir: dir,
        install: false,
      )
    else
      ex_sources += dir / src
    endif
  endforeach

  if ex[0][0] == 'input'
    # input/main.cc must know if mkfifo() exists.
    # input/example is not a GUI app.
    exe_file = executable(ex_name, ex_sources, resources,
      dependencies: gtkmm_dep,
      win_subsystem: 'console',
      cpp_args: has_mkfifo ? [] : [ '-DDONT_HAVE_MKFIFO=1' ],
      build_by_default: build_examples_by_default,
      install: false,
    )
  else
    if ex[0][0] == 'glarea'
      deps = [gtkmm_dep, epoxy_dep, glm_dep]
    elif ex[0][0] == 'multithread'
      # Multi-threaded programs need thread support.
      deps = [gtkmm_dep, thread_dep]
    else
      deps = gtkmm_dep
    endif
    exe_file = executable(ex_name, ex_sources, resources,
      dependencies: deps,
      win_subsystem: 'windows',
      build_by_default: build_examples_by_default,
      install: false,
    )
  endif

  stamp_file_name = ex_name + '_copy.stamp'
  examples_targets += custom_target(stamp_file_name,
    input: exe_file,
    output: stamp_file_name,
    command: [
      python3, copy_to_subdir,
      '@INPUT@',
      dir,
      ex[1],
      '@OUTPUT@',
    ],
    build_by_default: build_examples_by_default,
    install: false,
  )

  target_name = 'examples' / 'book' / stamp_file_name
  test('book_' + ex_name, meson_backend,
    args: target_name,
    workdir: project_build_root,
    timeout: test_timeout
  )
endforeach
