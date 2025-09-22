# This file is part of gtkmm-documentation.

project('gtkmm-documentation', 'c', 'cpp',
  version: '4.12.0',
  license: 'GFDL-1.2-no-invariants-or-later',
  default_options: [
    'cpp_std=c++17',
    'warning_level=1',
  ],
  meson_version: '>= 0.60.0', # required for install_tag keyword argument.
)

# Use the Python installation that Meson uses. Its version is >= 3.7.
python3 = import('python').find_installation()

gtkmm_pcname = 'gtkmm-4.0'
gtkmm_req = '>= 4.10.0'
giomm_pcname = 'giomm-2.68'
giomm_req = '>= 2.68.0'
gnome = import('gnome')

# Installation directories are relative to {prefix}.
install_prefix = get_option('prefix')
install_datadir = get_option('datadir')

# Source and build root directories of the current (sub)project.
project_source_root = meson.project_source_root()
project_build_root = meson.project_build_root()

script_dir = project_source_root / 'tools' / 'meson_aux'
compile_schemas = script_dir / 'compile-schemas.py'
copy_to_subdir = script_dir / 'copy-to-subdir.py'
tutorial_custom_cmd = script_dir / 'tutorial-custom-cmd.py'
extra_dist_cmd = script_dir / 'extra-dist-cmd.py'

c_compiler = meson.get_compiler('c')
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
  cpp_warnings = get_option('dist-warnings')
else
  cpp_warnings = get_option('warnings')
endif
if get_option('warning_level') in ['0','1','2','3','4','5']
  warning_level = get_option('warning_level').to_int()
else
  # For instance get_option('warning_level') == 'everything'
  warning_level = 99
endif
werror = get_option('werror')

must_be_able_to_build_examples = build_examples_by_default or is_dist_check

gtkmm_dep = dependency(gtkmm_pcname, version: gtkmm_req, required: must_be_able_to_build_examples)
giomm_dep = dependency(giomm_pcname, version: giomm_req, required: must_be_able_to_build_examples)
can_build_examples = gtkmm_dep.found() and giomm_dep.found()

# Set compiler warnings.
# Meson warns if any of the /W1, /W2, /W3, /W4, /Wall, -Wall, -Wextra, -Werror
# compiler options are added with add_project_arguments().
# Avoid such warnings, when possible.
# See _warn_about_builtin_args() in meson/mesonbuild/interpreter/interpreter.py.
warning_flags = []
if cpp_warnings == 'min'
  if warning_level == 0
    warning_flags = ['-Wall']
  endif
elif cpp_warnings == 'max' or cpp_warnings == 'fatal'
  if warning_level < 3
    warning_flags = ['-pedantic', '-Wall', '-Wextra']
  endif
  warning_flags += '-Wformat-security -Wsuggest-override -Wshadow -Wno-long-long'.split()
  if cpp_warnings == 'fatal'
    if not werror
      warning_flags += ['-Werror']
    endif
    deprecations = 'G PANGO GDK GDK_PIXBUF GTK GLIBMM GIOMM GDKMM PANGOMM GTKMM SIGCXX'.split()
    foreach d : deprecations
      warning_flags += '-D@0@_DISABLE_DEPRECATED'.format(d)
    endforeach
  endif
endif

warning_flags = cpp_compiler.get_supported_arguments(warning_flags)
add_project_arguments(warning_flags, language: 'cpp')

# Don't warn about a long string in a C file.
# gnome.compile_resources() generates such a file.
c_warning_flags = ['-Wno-overlength-strings']
add_project_arguments(c_compiler.get_supported_arguments(c_warning_flags), language: 'c')

subdir('docs/tutorial')
subdir('examples')

# Don't distribute these files and directories.
dont_distribute = [
  'docs' / 'tutorial' / 'kindle_cover.jpg',
  'docs' / 'tutorial' / 'kindle_cover.svg',
  'tools' / 'make_screenshots',
  'gtkmm-documentation.doap',
  '.gitlab-ci.yml',
]
# Modify the contents of the distribution directory.
meson.add_dist_script(
  python3, extra_dist_cmd,
  project_source_root,
  project_build_root,
  dont_distribute,
)

# Print a summary.
explain_ex = ''
if not can_build_examples
  explain_ex = ' (requires @0@ @1@ and @2@ @3@)'
  explain_ex = explain_ex.format(gtkmm_pcname, gtkmm_req, giomm_pcname, giomm_req)
endif

validate = get_option('validation') and can_parse_and_validate
explain_val = ''
if get_option('validation') and not validate
  explain_val = ' (requires xmllint with Relax NG and DocBook V5.0 support)'
endif

build_translations = build_translations_by_default and can_build_translations
explain_trans = ''
if build_translations_by_default and not build_translations
  explain_trans = ' (requires msgfmt and itstool)'
endif

build_pdf = build_pdf_by_default and can_build_pdf
explain_pdf = ''
if build_pdf_by_default and not build_pdf
  explain_pdf = ' (requires xsltproc and (dblatex or fop))'
endif

summary = [
  '',
  '------',
  meson.project_name() + ' ' + meson.project_version(),
  '',
  '      Build examples: @0@@1@'.format(build_examples_by_default, explain_ex),
  '   Compiler warnings: @0@ (warning_level: @1@, werror: @2@)'. \
                         format(cpp_warnings, warning_level, werror),
  '      XML validation: @0@@1@'.format(validate, explain_val),
  'Allow network access: @0@'.format(get_option('allow-network-access')),
  '  Build translations: @0@@1@'.format(build_translations, explain_trans),
  '           Build PDF: @0@@1@'.format(build_pdf, explain_pdf),
  'Directories:',
  '              prefix: @0@'.format(install_prefix),
  '             datadir: @0@'.format(install_prefix / install_datadir),
  '         tutorialdir: @0@'.format(install_prefix / tutorialdir),
  '------'
]

message('\n'.join(summary))
