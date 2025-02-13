# examples/book/treeview

# input: gnome, gtkmm_dep, build_examples_by_default, compile_schemas, python3,
#        copy_to_subdir, meson_backend, test_timeout, project_build_root
# input and output: examples_targets

exwindow_main = ['examplewindow.cc', 'main.cc']

examples_book_treeview = [
# [[dir-name], exe-name, [sources]]
  [['combo_renderer'], 'example', exwindow_main],
  [['custom_treemodel'], 'example', exwindow_main + ['exampletreemodel.cc']],
  [['drag_and_drop'], 'example', exwindow_main + ['treemodel_dnd.cc']],
  [['editable_cells'], 'example', exwindow_main],
  [['filter'], 'example', exwindow_main],
  [['filter_modify'], 'example', exwindow_main],
  [['list'], 'example', exwindow_main],
  [['listviewtext'], 'example', exwindow_main],
  [['modelsort'], 'example', exwindow_main],
  [['popup'], 'example', exwindow_main + ['treeview_withpopup.cc']],
  [['tree'], 'example', exwindow_main],
]

foreach ex : examples_book_treeview
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

  exe_file = executable(ex_name, ex_sources, resources,
    dependencies: gtkmm_dep,
    win_subsystem: 'windows',
    build_by_default: build_examples_by_default,
    install: false,
  )

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

  target_name = 'examples' / 'book' / 'treeview' / stamp_file_name
  test('book_treeview_' + ex_name, meson_backend,
    args: target_name,
    workdir: project_build_root,
    timeout: test_timeout
  )
endforeach
