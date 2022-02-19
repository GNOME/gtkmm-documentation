project('gtkmm exampleapp', 'c', 'cpp',
  version: '0.0.0',
  default_options: [
    'cpp_std=c++17'
  ]
)

gtkmm_dep = dependency('gtkmm-4.0')

program_name = 'exampleapp'

cpp_sources = [
  'main.cc',
  'exampleappwindow.cc',
  'exampleapplication.cc',
]

executable(program_name,
  cpp_sources,
  dependencies: gtkmm_dep,
  win_subsystem: 'windows',
)

python3 = import('python').find_installation()
install_cmd = meson.current_source_dir() / 'install-cmd.py'

conf_data = configuration_data()
conf_data.set('bindir', meson.current_build_dir())
desktop_file = configure_file(
  input: 'exampleapp.desktop.in',
  output: '@BASENAME@',
  configuration: conf_data,
)

run_target('install-desktop-file',
  command: [
    python3, install_cmd, 'desktop',
    program_name,
    desktop_file,
    meson.current_source_dir() / 'exampleapp.png',
  ]
)
