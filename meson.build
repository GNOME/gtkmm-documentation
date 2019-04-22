# Building gtkmm-documentation with meson is experimental.
# Use autotools for production builds.

project('gtkmm-documentation', 'c', 'cpp',
  version: '3.89.0',
  default_options: [
    'cpp_std=c++17'
  ],
  meson_version: '>= 0.49.0',
  license: 'GPLv2'
)

gtkmm_pcname = 'gtkmm-4.0'
gtkmm_dep = dependency(gtkmm_pcname, version: '>=3.93.0')
giomm_dep = dependency('giomm-2.62', version: '>=2.61.1')
gnome = import('gnome')

gtkmm_prefix = get_option('prefix')
gtkmm_datadir = join_paths(gtkmm_prefix, get_option('datadir'))

compile_schemas_sh = files(join_paths('tools', 'meson_aux', 'compile-schemas.sh'))
copy_to_subdir_sh = files(join_paths('tools', 'meson_aux', 'copy-to-subdir.sh'))
tutorial_custom_cmd_sh = files(join_paths('tools', 'meson_aux', 'tutorial-custom-cmd.sh'))

cpp_compiler = meson.get_compiler('cpp')

warning_level = get_option('warnings')
warning_flags = []
if warning_level == 'min'
  warning_flags = [ '-Wall' ]
elif warning_level == 'max' or warning_level == 'fatal'
  warning_flags = '-pedantic -Wall -Wextra -Wformat-security -Wsuggest-override -Wshadow -Wno-long-long'.split()
  if warning_level == 'fatal'
    warning_flags += [ '-Werror' ]
    deprecations = 'G PANGO ATK GDK GDK_PIXBUF GTK GLIBMM GIOMM GDKMM ATKMM PANGOMM GTKMM SIGCXX'.split()
    foreach d : deprecations
      warning_flags += '-D@0@_DISABLED_DEPRECATED'.format(d)
    endforeach
  endif
endif

warning_flags = cpp_compiler.get_supported_arguments(warning_flags)
add_project_arguments(warning_flags, language: 'cpp')

# This fix is necessary to make examples/book/input/example compile.
# TODO: Improve it.
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
# end of examples/book/input/example fix

subdir('docs/tutorial')
subdir('examples')

meson.add_dist_script(
  join_paths('tools', 'meson_aux', 'extra-dist-cmd.sh'),
  meson.current_build_dir(),
  join_paths('meson-dist', meson.project_name() + '-' + meson.project_version()),
  ' '.join(tutorial_languages)
)
