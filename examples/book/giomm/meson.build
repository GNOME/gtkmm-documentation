# examples/book/giomm

# input: gnome, giomm_dep, build_examples_by_default, copy_to_subdir_sh
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
    dependencies: giomm_dep,
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

  examples_targets += join_paths('examples', 'book', 'giomm', stamp_file_name)
endforeach
