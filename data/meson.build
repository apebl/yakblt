install_data('icons' / 'hicolor' / 'scalable' /'@0@.svg'.format(app_id),
	install_dir: get_option('datadir') / 'icons' / 'hicolor' / 'scalable' / 'apps'
)

install_data('@0@.desktop'.format(app_id),
	install_dir: get_option('datadir') / 'applications'
)

configure_file(
	input: '@0@.in'.format(app_id),
	output: app_id,
	configuration: {
		'install_path': get_option('prefix') / install_dir
	},
	install: true,
	install_dir: get_option('bindir')
)

install_data ('@0@.appdata.xml'.format(app_id),
	install_dir: get_option('datadir') / 'metainfo'
)

desktop_file_validate = find_program('desktop-file-validate', required: false)
if desktop_file_validate.found()
	test('validate-desktop',
		desktop_file_validate,
		args: [
			files('org.kosmospredanie.Yakblt.desktop')
		]
	)
endif

appstream_util = find_program('appstream-util', required: false)
if appstream_util.found()
	test('validate-appdata',
		appstream_util,
		args: [
			'validate',
			'--nonet',
			files('@0@.appdata.xml'.format(app_id))
		]
	)
endif
