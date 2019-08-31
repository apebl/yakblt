#include "app.hpp"
#include "ingamescene.hpp"
#include "config.hpp"
#include "assets.hpp"
#include <SFML/OpenGL.hpp>

using namespace blt;

namespace {
	void scissorRoot (Node &root) {
		glEnable(GL_SCISSOR_TEST);
		glScissor(
			(int) root.getPosition().x,
			(int) root.getPosition().y,
			(int) (root.getScale().x * WORLD_WIDTH),
			(int) (root.getScale().y * WORLD_HEIGHT)
		);
	}

	void resetScissors (const Window &window) {
		glScissor(0, 0, window.getSize().x, window.getSize().y);
	}
}

namespace blt {
	App::App (RenderWindow &window) :
			_window(&window),
			_assets( *(new DefaultResolver()) ),
			_sounds(),
			_gameRandom(), _unitFac(), _bulletFac(),
			_background(), _root(),
			_scene(nullptr), _clock(), _onSfmlEvent(),
			_deletes(), _sceneDeletes()
	{
		const Texture &tex = _assets.loadTexture(WINDOW_BACKGROUND);
		_background.getSprite().setTexture(tex, true);

		onSfmlEvent().addHandler([this](sf::Event event) {
			if (_scene != nullptr) {
				_scene->onSfmlEvent().fireEvent(event);
			}
		});
	}

	App::~App () {
	}

	RenderWindow &App::window () {
		return *_window;
	}

	AssetManager &App::assets () {
		return _assets;
	}

	SoundManager &App::sounds () {
		return _sounds;
	}

	Random &App::rand () {
		return _gameRandom;
	}

	Factory<Unit> &App::unitFac () {
		return _unitFac;
	}

	Factory<Bullet> &App::bulletFac () {
		return _bulletFac;
	}

	Node &App::background () {
		return _background;
	}

	Node &App::root () {
		return _root;
	}

	Scene *App::scene () {
		return _scene;
	}

	World &App::world () {
		return static_cast<InGameScene*>(_scene)->world();
	}

	void App::replaceScene (Scene *scene) {
		Scene *oldScene = _scene;
		if (oldScene != nullptr) {
			oldScene->hide(scene);
			// _root.removeChild(*oldScene);
		}
		_scene = scene;
		if (scene != nullptr) {
			// _root.addChild(*scene);
			scene->show(oldScene);
		}
	}

	void App::render (RenderTarget &target) {
		update( _clock.restart().asSeconds() );
		draw(target);
		while (!_deletes.empty()) {
			delete _deletes.front();
			_deletes.pop_front();
		}
		while (!_sceneDeletes.empty()) {
			delete _sceneDeletes.front();
			_sceneDeletes.pop_front();
		}
	}

	Event<sf::Event> &App::onSfmlEvent () {
		return _onSfmlEvent;
	}

	void App::addToDelete (const Node &item) {
		ASSERT( find(_deletes.begin(), _deletes.end(), &item) == _deletes.end() )
		_deletes.push_back(&item);
	}

	void App::addToDelete (const Scene &item) {
		ASSERT( find(_sceneDeletes.begin(), _sceneDeletes.end(), &item) == _sceneDeletes.end() )
		_sceneDeletes.push_back(&item);
	}

	void App::update (float delta) {
		_background.updateTransforms();
		_root.updateTransforms();
		_background.update(delta);
		_root.update(delta);
		if (_scene != nullptr) _scene->update(delta);
		_sounds.update();
	}

	void App::draw (RenderTarget &target) {
		_background.draw(target);
		scissorRoot(_root);
		_root.draw(target);
#ifdef DEBUG
		_root.drawDebug(target);
#endif
		resetScissors(*_window);
		if (_scene != nullptr) _scene->draw(target);
	}
}
