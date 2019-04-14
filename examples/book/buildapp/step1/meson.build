project('gtkmm exampleapp', 'c', 'cpp',
  version: '0.0.0',
  default_options: [
    'cpp_std=c++11'
  ]
)

gtkmm_dep = dependency('gtkmm-3.0')

program_name = 'exampleapp'

cpp_sources = [
  'main.cc',
  'exampleappwindow.cc',
  'exampleapplication.cc',
]

executable(program_name,
  cpp_sources,
  dependencies: gtkmm_dep
)

install_cmd = './install-cmd.sh'

run_target('install-desktop-file',
  command: [install_cmd, 'desktop',
    program_name,
    'exampleapp.desktop',
    'exampleapp.png'
  ]
)
