project('yakblt', 'cpp',
	version: '2020.02.10',
	license: 'MIT',
	meson_version: '>=0.50.0',
	default_options : ['cpp_std=c++14'])

app_id = 'org.kosmospredanie.Yakblt'

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

install_dir = get_option('datadir') / 'games' / 'yakblt'
install_subdir('assets', install_dir: install_dir)

subdir('data')
subdir('src')

