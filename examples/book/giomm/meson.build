# examples/book/giomm

# input: gnome, giomm_dep, build_examples_by_default, copy_to_subdir,
#        meson_backend, project_build_root, python3
# input and output: examples_targets

examples_book_giomm = [
# [[dir-name], exe-name, [sources]]
  [['directory_list'], 'example', ['main.cc']],
  [['getline'], 'example', ['getline.cc']],
  [['monitor_directory'], 'monitor_directory', ['monitor_directory.cc']],
  [['read_file'], 'example', ['main.cc']],
  [['read_file_async'], 'example', ['main.cc']],
  [['usage'], 'usage', ['usage.cc']],
  [['volumes'], 'example', ['main.cc']],
  [['write_file'], 'example', ['main.cc']],
]

foreach ex : examples_book_giomm
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
    dependencies: giomm_dep,
    win_subsystem: 'console',
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

  # These example programs build quite fast. No need for extra timeout time.
  target_name = 'examples' / 'book' / 'giomm' / stamp_file_name
  test('book_giomm_' + ex_name, meson_backend,
    args: target_name,
    workdir: project_build_root
  )
endforeach
