/* app.cpp
 *
 * Copyright (C) 2019-2020 Космическое П. <kosmospredanie@yandex.ru>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "app.hpp"
#include "ingamescene.hpp"
#include "config.hpp"
#include "assets.hpp"
#include <SFML/OpenGL.hpp>

using namespace yakblt;

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

namespace yakblt {
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
