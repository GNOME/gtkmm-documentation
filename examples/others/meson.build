# examples/others

# input: gnome, gtkmm_dep, build_examples_by_default, copy_to_subdir_sh
# input and output: examples_targets

examples_others = [
# [[dir-name], exe-name, [sources]]
  [['arrow'], 'arrow', ['arrow.cc']],
  [['calendar'], 'calendar', ['calendar.cc']],
  [['cellrenderercustom'], 'cellrenderertoggle', ['cellrenderertoggle.cc']],
  [['cellrenderercustom'], 'testpopup',
    ['cellrendererlist.cc', 'cellrendererpopup.cc', 'popupentry.cc', 'testpopup.cc']],
  [['dnd'], 'testdnd', ['dndwindow.cc', 'main.cc']],
  [['exception'], 'exceptiontest', ['exceptiontest.cc']],
  [['idle'], 'idle', ['idle.cc']],
  [['statusbar'], 'statusbar', ['statusbar.cc']],
  [['tictactoe'], 'ttt_test', ['tictactoe.cc', 'ttt_test.cc']],
  [['treemodelcustom'], 'example', ['exampletreemodel.cc', 'examplewindow.cc', 'main.cc']],
  # Waiting for a gdk_cairo_region_from_surface():
  # [['window'], 'wheelbarrow', ['wheelbarrow.cc']],
]

foreach ex : examples_others
  dir = ''
  foreach dir_part : ex[0]
    dir = join_paths(dir, dir_part)
  endforeach
  ex_name = join_paths(dir, ex[1]).underscorify()
  ex_sources = []
  resources = []
  foreach src : ex[2]
    if src.endswith('.gresource.xml')
      resources = gnome.compile_resources(dir.underscorify() + '_resources',
        join_paths(dir, src),
        source_dir: dir
      )
    else
      ex_sources += join_paths(dir, src)
    endif
  endforeach

  exe_file = executable(ex_name, ex_sources, resources,
    dependencies: gtkmm_dep,
    gui_app: true,
    build_by_default: build_examples_by_default
  )

  stamp_file_name = ex_name + '_copy.stamp'
  custom_target(stamp_file_name,
    input: exe_file,
    output: stamp_file_name,
    command: [
      copy_to_subdir_sh,
      '@INPUT@',
      dir,
      ex[1],
      '@OUTPUT@',
    ],
    build_by_default: build_examples_by_default
  )

  examples_targets += join_paths('examples', 'others', stamp_file_name)
endforeach
