# examples

# input: gnome, gtkmm_dep, giomm_dep, compile_schemas_sh, copy_to_subdir_sh, is_dist
# output: build_examples_by_default

# examples/book/input/main.cc includes build/config.h.
has_mkfifo = cpp_compiler.has_function('mkfifo')
conf_data = configuration_data()
conf_data.set('HAVE_MKFIFO', has_mkfifo)
conf_file = configure_file(
  output: 'config.h',
  configuration: conf_data
)
custom_target('build_config',
  input: conf_file,
  output: 'config.stamp',
  command: [
    copy_to_subdir_sh,
    '@INPUT@',
    'build',
    'config.h',
    '@OUTPUT@',
  ],
  build_by_default: true
)
config_include_dir = include_directories('.')

build_examples_by_default = get_option(is_dist ? 'build-dist-examples' : 'build-examples')
examples_targets = []

subdir('book')
subdir('others')

run_target('examples',
  command: ['bash', '-c', 'cd ' + meson.build_root() + '; ' + meson.backend() + ' ' + ' '.join(examples_targets)]
)
