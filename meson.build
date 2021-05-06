# This file is part of gtkmm-documentation.

project('gtkmm-documentation', 'c', 'cpp',
  version: '4.0.1',
  default_options: [
    'cpp_std=c++17'
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

gtkmm_pcname = 'gtkmm-4.0'
gtkmm_req = '>= 4.0.0'
giomm_pcname = 'giomm-2.68'
giomm_req = '>= 2.68.0'
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

# Options
build_examples_by_default = get_option('build-examples')
if is_dist_check
  message('Looks like a tarball is being tested. ' + \
          'Option "dist-warnings" is used instead of "warnings".')
  warning_level = get_option('dist-warnings')
else
  warning_level = get_option('warnings')
endif

must_be_able_to_build_examples = build_examples_by_default or is_dist_check

gtkmm_dep = dependency(gtkmm_pcname, version: gtkmm_req, required: must_be_able_to_build_examples)
giomm_dep = dependency(giomm_pcname, version: giomm_req, required: must_be_able_to_build_examples)
can_build_examples = gtkmm_dep.found() and giomm_dep.found()

warning_flags = []
if warning_level == 'min'
  warning_flags = ['-Wall']
elif warning_level == 'max' or warning_level == 'fatal'
  warning_flags = '-pedantic -Wall -Wextra -Wformat-security -Wsuggest-override -Wshadow -Wno-long-long'.split()
  if warning_level == 'fatal'
    warning_flags += ['-Werror']
    deprecations = 'G PANGO GDK GDK_PIXBUF GTK GLIBMM GIOMM GDKMM PANGOMM GTKMM SIGCXX'.split()
    foreach d : deprecations
      warning_flags += '-D@0@_DISABLE_DEPRECATED'.format(d)
    endforeach
  endif
endif

warning_flags = cpp_compiler.get_supported_arguments(warning_flags)
add_project_arguments(warning_flags, language: 'cpp')

# add_dist_script() is not allowed in a subproject if meson.version() < 0.58.0.
can_add_dist_script = not meson.is_subproject() or meson.version().version_compare('>= 0.58.0')

subdir('docs/tutorial')
subdir('examples')

if can_add_dist_script
  # Don't distribute these files and directories.
  dont_distribute = [
    'docs' / 'tutorial' / 'kindle_cover.jpg',
    'docs' / 'tutorial' / 'kindle_cover.svg',
    'tools' / 'make_screenshots',
  ]
  # Modify the contents of the distribution directory.
  meson.add_dist_script(
    python3.path(), extra_dist_cmd,
    project_source_root,
    project_build_root,
    dont_distribute,
  )
endif

# Print a summary.
explain_ex = ''
if not can_build_examples
  explain_ex = ' (requires @0@ @1@ and @2@ @3@)'
  explain_ex = explain_ex.format(gtkmm_pcname, gtkmm_req, giomm_pcname, giomm_req)
endif

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
  '    Build examples: @0@@1@'.format(build_examples_by_default, explain_ex),
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
