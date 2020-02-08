project('yakblt', 'cpp',
	version: '2019.08.31',
	license: 'MIT',
	meson_version: '>=0.49.0',
	default_options : ['cpp_std=c++14'])

sfml_reqs = '2.5.1'
sfmlsystem_dep = dependency('sfml-system', version: '>=' + sfml_reqs)
sfmlwindow_dep = dependency('sfml-window', version: '>=' + sfml_reqs)
sfmlgraphics_dep = dependency('sfml-graphics', version: '>=' + sfml_reqs)
sfmlaudio_dep = dependency('sfml-audio', version: '>=' + sfml_reqs)
gl_dep = dependency('gl')
tgui_reqs = '0.8'
tgui_dep = dependency('tgui', version: '>=' + tgui_reqs)

dependencies = [
	sfmlsystem_dep,
	sfmlwindow_dep,
	sfmlgraphics_dep,
	sfmlaudio_dep,
	gl_dep,
	tgui_dep
]

install_dir = get_option('gamedir') / 'yakblt'

subdir('src')

configure_file(
	input: 'org.kosmospredanie.Yakblt.desktop.in',
	output: 'org.kosmospredanie.Yakblt.desktop',
	configuration: {
		'install_path': get_option('prefix') / install_dir
	},
	install: true,
	install_dir: install_dir
)
meson.add_install_script('ln', '-fs',
	get_option('prefix') / install_dir / 'org.kosmospredanie.Yakblt.desktop',
	get_option('prefix') / get_option('datadir') / 'applications' / 'org.kosmospredanie.Yakblt.desktop')
install_subdir('assets', install_dir: install_dir)
install_data('icon.svg', install_dir: install_dir)
