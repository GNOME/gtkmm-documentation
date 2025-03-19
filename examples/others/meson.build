# examples/others

# input: gnome, gtkmm_dep, build_examples_by_default, copy_to_subdir,
#        meson_backend, test_timeout, project_build_root, python3
# input and output: examples_targets

examples_others = [
# [[dir-name], exe-name, [sources]]
  [['calendar'], 'calendar', ['calendar.cc']],
  [['dnd'], 'testdnd', ['dndwindow.cc', 'main.cc']],
  [['exception'], 'exceptiontest', ['exceptiontest.cc']],
  [['tictactoe'], 'ttt_test', ['tictactoe.cc', 'ttt_test.cc']],
  [['webkit'], 'example', ['examplewindow.cc', 'main.cc']],
  [['window'], 'wheelbarrow', ['wheelbarrow.cc']],
]

webkit_dep = dependency('webkitgtk-6.0', required: false)

foreach ex : examples_others
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

  # The WebKit example can be built only if webkitgtk is installed.
  if ex[0][0] != 'webkit' or webkit_dep.found()
    deps = (ex[0][0] == 'webkit') ? [gtkmm_dep, webkit_dep] : gtkmm_dep
    exe_file = executable(ex_name, ex_sources, resources,
      dependencies: deps,
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

    target_name = 'examples' / 'others' / stamp_file_name
    test('others_' + ex_name, meson_backend,
      args: target_name,
      workdir: project_build_root,
      timeout: test_timeout
    )
  endif
endforeach
