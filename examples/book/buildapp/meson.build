# examples/book/buildapp

# input: gnome, gtkmm_dep, build_examples_by_default, compile_schemas, python3,
#        copy_to_subdir, meson_backend, test_timeout, project_build_root
# input and output: examples_targets

exapp_main = ['exampleapplication.cc', 'exampleappwindow.cc', 'main.cc']
exapp_prefs = exapp_main + \
  ['exampleappprefs.cc', 'exampleapp.gresource.xml', 'org.gtkmm.exampleapp.gschema.xml']

examples_book_buildapp = [
# [[dir-name], exe-name, [sources]]
  [['step1'], 'exampleapp', exapp_main],
  [['step2'], 'exampleapp', exapp_main + ['exampleapp.gresource.xml']],
  [['step3'], 'exampleapp', exapp_main + ['exampleapp.gresource.xml']],
  [['step4'], 'exampleapp', exapp_main + ['exampleapp.gresource.xml']],
  [['step5'], 'exampleapp', exapp_prefs],
  [['step6'], 'exampleapp', exapp_prefs],
  [['step7'], 'exampleapp', exapp_prefs],
  [['step8'], 'exampleapp', exapp_prefs],
  [['step9'], 'exampleapp', exapp_prefs],
]

glib_compile_schemas = find_program('glib-compile-schemas', required: false)

foreach ex : examples_book_buildapp
  dir = ''
  foreach dir_part : ex[0]
    dir = dir / dir_part
  endforeach
  ex_name = (dir / ex[1]).underscorify()
  ex_sources = []
  resources = []
  schemas = []
  foreach src : ex[2]
    if src.endswith('.gresource.xml')
      resources = gnome.compile_resources(dir.underscorify() + '_resources',
        dir / src,
        source_dir: dir,
        install: false,
      )
    elif src.endswith('.gschema.xml')
      if glib_compile_schemas.found()
        schemas = custom_target(dir.underscorify() + '_schemas',
          input: dir / src,
          output: dir.underscorify() + '_gschemas.compiled',
          command: [
            python3, compile_schemas,
            meson.current_source_dir() / dir,
            meson.current_build_dir() / dir,
            '@OUTPUT@'
          ],
          build_by_default: build_examples_by_default,
          install: false,
        )
      endif
    else
      ex_sources += dir / src
    endif
  endforeach

  exe_file = executable(ex_name, ex_sources, resources, schemas,
    dependencies: gtkmm_dep,
    win_subsystem: 'windows',
    build_by_default: build_examples_by_default,
    install: false,
  )

  stamp_file_name = ex_name + '_copy.stamp'
  examples_targets += custom_target(stamp_file_name,
    input: exe_file,
    output: stamp_file_name,
    command: [
      python3, copy_to_subdir,
      '@INPUT@',
      dir,
      ex[1],
      '@OUTPUT@',
    ],
    build_by_default: build_examples_by_default,
    install: false,
  )

  target_name = 'examples' / 'book' / 'buildapp' / stamp_file_name
  test('book_buildapp_' + ex_name, meson_backend,
    args: target_name,
    workdir: project_build_root,
    timeout: test_timeout
  )
endforeach
