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
  'exampleappprefs.cc',
]

resources = gnome.compile_resources('resources',
                                    'exampleapp.gresource.xml',
                                    source_dir: '.')
schemas = gnome.compile_schemas(depend_files: 'org.gtkmm.exampleapp.gschema.xml')

executable(program_name,
  cpp_sources, resources, schemas,
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

run_target('install-gschema-file',
  command: [install_cmd, 'gschema',
    'org.gtkmm.exampleapp.gschema.xml'
  ]
)
