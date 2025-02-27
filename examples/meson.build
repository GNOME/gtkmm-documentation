# examples

# input: gnome, gtkmm_dep, giomm_dep, compile_schemas, copy_to_subdir, python3,
#        project_build_root, build_examples_by_default, can_build_examples
# output: -

if can_build_examples
  # examples/book/input/main.cc must know if mkfifo() exists.
  has_mkfifo = cpp_compiler.has_function('mkfifo')

  meson_backend = find_program(meson.backend(), required: true)
  test_timeout = 80 # max seconds per test
  examples_targets = []
  subdir('book')
  subdir('others')

  # 'ninja examples' and 'meson compile examples' build all example programs.
  alias_target('examples', examples_targets)
else
  run_target('examples',
    command: [ python3, '-c', 'print("Can\'t build the examples")' ]
  )
endif
