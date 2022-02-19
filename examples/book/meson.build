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
  [['buttons', 'volumebutton'], 'example', exwindow_main],
  [['clipboard', 'ideal'], 'example', exwindow_main],
  [['clipboard', 'simple'], 'example', exwindow_main],
  [['combobox', 'complex'], 'example', exwindow_main],
  [['combobox', 'text'], 'example', exwindow_main],
  [['combobox', 'entry_complex'], 'example', exwindow_main],
  [['combobox', 'entry_text'], 'example', exwindow_main],
  [['custom', 'custom_container'], 'example', exwindow_main + ['mycontainer.cc']],
  [['custom', 'custom_widget'], 'example', exwindow_main + ['myextrainit.cc', 'mywidget.cc']],
  [['dialogs', 'aboutdialog'], 'example',  exwindow_main + ['aboutdialog.gresource.xml']],
  [['dialogs', 'colorchooserdialog'], 'example', exwindow_main],
  [['dialogs', 'filechooserdialog'], 'example', exwindow_main],
  [['dialogs', 'filechoosernative'], 'example', exwindow_main],
  [['dialogs', 'fontchooserdialog'], 'example', exwindow_main],
  [['dialogs', 'messagedialog'], 'example', exwindow_main],
  [['dialogs', 'simple'], 'example', exwindow_main],
  [['drag_and_drop'], 'drag_and_drop', ['dndwindow.cc', 'main.cc']],
  [['drawingarea', 'arcs'], 'drawingareaarcs', ['main.cc', 'myarea.cc']],
  [['drawingarea', 'clock'], 'cairoclock', ['clock.cc', 'main.cc']],
  [['drawingarea', 'curve'], 'drawingareacurve', ['main.cc', 'myarea.cc']],
  [['drawingarea', 'image'], 'drawingareaimage', ['main.cc', 'myarea.cc', 'image.gresource.xml']],
  [['drawingarea', 'joins'], 'cairojoins', ['main.cc', 'myarea.cc']],
  [['drawingarea', 'pango_text'], 'example', ['main.cc', 'myarea.cc']],
  [['drawingarea', 'simple'], 'drawingarea', ['main.cc', 'myarea.cc']],
  [['drawingarea', 'thin_lines'], 'example', exwindow_main + ['myarea.cc']],
  [['entry', 'completion'], 'example', exwindow_main],
  [['entry', 'icon'], 'example', exwindow_main],
  [['entry', 'progress'], 'example', exwindow_main],
  [['entry', 'simple'], 'example', exwindow_main],
  [['expander'], 'example', exwindow_main],
  [['flowbox'], 'example', exwindow_main],
  [['frame'], 'example', exwindow_main],
  [['grid'], 'example', exwindow_main],
  [['headerbar'], 'example', exwindow_main],
  [['helloworld'], 'helloworld', ['helloworld.cc', 'main.cc']],
  [['helloworld2'], 'helloworld2', ['helloworld.cc', 'main.cc']],
  [['iconview'], 'example', exwindow_main],
  [['idle'], 'idle', ['idleexample.cc', 'main.cc']],
  [['infobar'], 'example', exwindow_main],
  [['input'], 'example', ['main.cc']],
  [['keyboard_events', 'simple'], 'example', exwindow_main],
  [['keyboard_events', 'propagation'], 'example', exwindow_main],
  [['label'], 'example', exwindow_main],
  [['listbox'], 'example', exwindow_main + ['examplerow.cc']],
  [['listmodel'], 'example', exwindow_main + ['myobject.cc']],
  [['menus', 'main_menu'], 'main_menu', ['exampleapplication.cc'] + exwindow_main],
  [['menus', 'popup'], 'example', exwindow_main],
  [['menus_and_toolbars'], 'example', exwindow_main + ['toolbar.gresource.xml']],
  [['multithread'], 'example', exwindow_main + ['exampleworker.cc']],
  [['notebook'], 'example', exwindow_main],
  [['paned'], 'example', exwindow_main + ['messageslist.cc', 'messagetext.cc']],
  [['popover'], 'example', exwindow_main],
  [['printing', 'advanced'], 'example', exwindow_main + ['previewdialog.cc', 'printformoperation.cc']],
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

foreach ex : examples_book
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
        source_dir: dir
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
      build_by_default: build_examples_by_default
    )
  else
    # multi-threaded programs need thread support
    deps = (ex[0][0] == 'multithread') ? [gtkmm_dep, thread_dep] : gtkmm_dep

    exe_file = executable(ex_name, ex_sources, resources,
      dependencies: deps,
      win_subsystem: 'windows',
      build_by_default: build_examples_by_default
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
    build_by_default: build_examples_by_default
  )

  target_name = 'examples' / 'book' / stamp_file_name
  test('book_' + ex_name, meson_backend,
    args: target_name,
    workdir: project_build_root,
    timeout: test_timeout
  )
endforeach
