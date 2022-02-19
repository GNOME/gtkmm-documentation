project('gtkmm exampleapp', 'c', 'cpp',
  version: '0.0.0',
  default_options: [
    'cpp_std=c++17'
  ]
)

gnome = import('gnome')
gtkmm_dep = dependency('gtkmm-4.0')

program_name = 'exampleapp'

cpp_sources = [
  'main.cc',
  'exampleappwindow.cc',
  'exampleapplication.cc',
  'exampleappprefs.cc',
]

resources = gnome.compile_resources('resources',
                                    'exampleapp.gresource.xml',
                                    source_dir: '.')
schemas = gnome.compile_schemas(depend_files: 'org.gtkmm.exampleapp.gschema.xml')

executable(program_name,
  cpp_sources, resources, schemas,
  dependencies: gtkmm_dep,
  win_subsystem: 'windows',
)

python3 = import('python').find_installation()
source_step1_dir = meson.current_source_dir() / '..' / 'step1'
install_cmd = source_step1_dir / 'install-cmd.py'

conf_data = configuration_data()
conf_data.set('bindir', meson.current_build_dir())
desktop_file = configure_file(
  input: '..' / 'step1' / 'exampleapp.desktop.in',
  output: '@BASENAME@',
  configuration: conf_data,
)

run_target('install-desktop-file',
  command: [
    python3, install_cmd, 'desktop',
    program_name,
    desktop_file,
    source_step1_dir / 'exampleapp.png',
  ]
)

run_target('install-gschema-file',
  command: [
    python3, install_cmd, 'gschema',
    meson.current_source_dir() / 'org.gtkmm.exampleapp.gschema.xml',
  ]
)
