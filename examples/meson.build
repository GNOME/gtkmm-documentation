# examples

# input: gnome, gtkmm_dep, giomm_dep, compile_schemas, copy_to_subdir,
#        project_build_root, python3
# output: build_examples_by_default

# examples/book/input/main.cc must know if mkfifo() exists.
has_mkfifo = cpp_compiler.has_function('mkfifo')

meson_backend = find_program(meson.backend(), required: true)
build_examples_by_default = get_option('build-examples')
test_timeout = 80 # max seconds per test
examples_targets = []

subdir('book')
subdir('others')

# 'ninja examples' builds all example programs.
# alias_target(), added in Meson 0.52.0, is an alternative to run_target().
run_target('examples',
  depends: examples_targets,
  command: [ python3, '-c', '# Dummy program' ]
)
