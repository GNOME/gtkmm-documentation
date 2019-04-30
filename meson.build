# This file is part of gtkmm-documentation.

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

# Is this configuration done during creation of a tarball (ninja dist)?
# The "real" source directory contains a .git subdirectory. The temporary
# source directory created by "ninja dist" does not.
is_dist = run_command('test', '-d', join_paths(meson.current_source_dir(), '.git')).returncode() != 0

warning_level = get_option(is_dist ? 'dist-warnings' : 'warnings')
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

subdir('docs/tutorial')
subdir('examples')

# Modify the contents of the distribution directory.
meson.add_dist_script(
  join_paths('tools', 'meson_aux', 'extra-dist-cmd.sh'),
  meson.current_source_dir(),
  meson.current_build_dir(),
  join_paths('meson-dist', meson.project_name() + '-' + meson.project_version()),
  ' '.join(tutorial_languages)
)

# Print a summary.
validate = get_option('validation') and can_parse_and_validate
explain_val = ''
if get_option('validation') and not validate
  explain_val = ' (requires xmllint)'
endif

build_translations = build_translations_by_default and can_build_translations
explain_trans = ''
if build_translations_by_default and not build_translations
  explain_trans = ' (requires msgfmt and itstool)'
endif

build_pdf = build_pdf_by_default and can_build_pdf
explain_pdf = ''
if build_pdf_by_default and not build_pdf
  explain_pdf = ' (requires xmllint and docbook2pdf)'
endif

summary = [
  '',
  '------',
  meson.project_name() + ' ' + meson.project_version(),
  '',
  '    Build examples: @0@'.format(build_examples_by_default),
  ' Compiler warnings: @0@'.format(warning_level),
  '    XML validation: @0@@1@'.format(validate, explain_val),
  'Build translations: @0@@1@'.format(build_translations, explain_trans),
  '         Build PDF: @0@@1@'.format(build_pdf, explain_pdf),
  'Directories:',
  '            prefix: @0@'.format(gtkmm_prefix),
  '           datadir: @0@'.format(gtkmm_datadir),
  '------'
]

message('\n'.join(summary))
