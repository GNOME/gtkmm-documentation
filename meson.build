# This file is part of gtkmm-documentation.

project('gtkmm-documentation', 'c', 'cpp',
  version: '3.24.1',
  default_options: [
    'cpp_std=c++14'
  ],
  meson_version: '>= 0.50.0', # required for python3.path()
  license: 'GPLv2'
)

python3 = import('python').find_installation()
python_version = python3.language_version()
python_version_req = '>= 3.5'
if not python_version.version_compare(python_version_req)
  error('Requires Python @0@, found @1@.'.format(python_version_req, python_version))
endif

gtkmm_pcname = 'gtkmm-3.0'
gtkmm_dep = dependency(gtkmm_pcname, version: '>=3.24.0')
giomm_dep = dependency('giomm-2.4', version: '>=2.54.0')
gnome = import('gnome')

# Installation directories are relative to {prefix}.
install_prefix = get_option('prefix')
install_datadir = get_option('datadir')

# Use these instead of meson.source_root() and meson.build_root() in subdirectories.
# source_root() and build_root() are not useful, if this is a subproject.
project_source_root = meson.current_source_dir()
project_build_root = meson.current_build_dir()

script_dir = project_source_root / 'tools' / 'meson_aux'
compile_schemas = script_dir / 'compile-schemas.py'
copy_to_subdir = script_dir / 'copy-to-subdir.py'
tutorial_custom_cmd = script_dir / 'tutorial-custom-cmd.py'
extra_dist_cmd = script_dir / 'extra-dist-cmd.py'

cpp_compiler = meson.get_compiler('cpp')

# Are we testing a dist tarball while it's being built?
# There ought to be a better way. https://github.com/mesonbuild/meson/issues/6866
is_dist_check = project_source_root.contains('dist-unpack') and \
                project_build_root.contains('dist-build')

if is_dist_check
  message('Looks like a tarball is being tested. ' + \
          'Option "dist-warnings" is used instead of "warnings".')
  warning_level = get_option('dist-warnings')
else
  warning_level = get_option('warnings')
endif

warning_flags = []
if warning_level == 'min'
  warning_flags = ['-Wall']
elif warning_level == 'max' or warning_level == 'fatal'
  warning_flags = '-pedantic -Wall -Wextra -Wformat-security -Wsuggest-override -Wshadow -Wno-long-long'.split()
  if warning_level == 'fatal'
    warning_flags += ['-Werror']
    deprecations = 'G PANGO ATK GDK GDK_PIXBUF GTK GLIBMM GIOMM GDKMM ATKMM PANGOMM GTKMM SIGCXX'.split()
    foreach d : deprecations
      warning_flags += '-D@0@_DISABLE_DEPRECATED'.format(d)
    endforeach
  endif
endif

warning_flags = cpp_compiler.get_supported_arguments(warning_flags)
add_project_arguments(warning_flags, language: 'cpp')

subdir('docs/tutorial')
subdir('examples')

if not meson.is_subproject()
  # Don't distribute these files and directories.
  dont_distribute = [
    'docs' / 'tutorial' / 'kindle_cover.jpg',
    'docs' / 'tutorial' / 'kindle_cover.svg',
    'tools' / 'make_screenshots',
  ]
  # Modify the contents of the distribution directory. (not allowed in a subproject)
  meson.add_dist_script(
    python3.path(), extra_dist_cmd,
    project_source_root,
    project_build_root,
    dont_distribute,
  )
endif

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
  explain_pdf = ' (requires dblatex or (xmllint and docbook2pdf))'
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
  '            prefix: @0@'.format(install_prefix),
  '           datadir: @0@'.format(install_prefix / install_datadir),
  '       tutorialdir: @0@'.format(install_prefix / tutorialdir),
  '------'
]

message('\n'.join(summary))
