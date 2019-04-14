project('gtkmm exampleapp', 'c', 'cpp',
  version: '0.0.0',
  default_options: [
    'cpp_std=c++11'
  ]
)

gnome = import('gnome')
gtkmm_dep = dependency('gtkmm-3.0')

program_name = 'exampleapp'

cpp_sources = [
  'main.cc',
  'exampleappwindow.cc',
  'exampleapplication.cc',
]

resources = gnome.compile_resources('resources',
                                    'exampleapp.gresource.xml',
                                    source_dir: '.')
executable(program_name,
  cpp_sources, resources,
  dependencies: gtkmm_dep
)

install_cmd = '../step1/install-cmd.sh'

run_target('install-desktop-file',
  command: [install_cmd, 'desktop',
    program_name,
    '../step1/exampleapp.desktop',
    '../step1/exampleapp.png'
  ]
)
