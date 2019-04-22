# examples

# input: gnome, gtkmm_dep, giomm_dep, compile_schemas_sh, copy_to_subdir_sh,
#        config_include_dir

build_examples_by_default = get_option('build-examples')
examples_targets = []

subdir('book')
subdir('others')

run_target('examples',
  command: ['bash', '-c', 'cd ' + meson.build_root() + '; ' + meson.backend() + ' ' + ' '.join(examples_targets)]
)
