/* app.hpp
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

#ifndef __BLT_APP_H__
#define __BLT_APP_H__

#include <deque>
#include "assetmanager.hpp"
#include "soundmanager.hpp"
#include "random.hpp"
#include "factory.hpp"
#include "scripter.hpp"
#include "event.hpp"
#include "scene.hpp"
#include "world.hpp"

namespace yakblt {
	class App {
	public:
		App (RenderWindow &window);
		virtual ~App ();

		RenderWindow &window ();

		/**
		 * Gets the asset manager.
		 *
		 * @return The asset manager of this app
		 */
		AssetManager &assets ();
		/**
		 * Gets the sound manager.
		 *
		 * @return The sound manager of this app
		 */
		SoundManager &sounds ();
		/**
		 * Gets the random used for the game.
		 *
		 * @return The random generator of this app
		 */
		Random &rand ();
		Factory<Unit> &unitFac ();
		Factory<Bullet> &bulletFac ();

		Node &background ();
		/**
		 * Gets the root node.
		 *
		 * @return The root node of this app
		 */
		Node &root ();

		/**
		 * Gets the current scene.
		 *
		 * @return The current scene, or null if no scene
		 */
		Scene *scene ();
		World &world ();
		/**
		 * Replaces the current scene with the new scene.
		 *
		 * @note This method doesn't delete the previous scene, so you have to delete
		 * the scene manually.
		 *
		 * @note This app hold the ownership of the new scene.
		 *
		 * @param scene The new scene, or null if no scene
		 */
		void replaceScene (Scene *scene);

		void render (RenderTarget &target);

		Event<sf::Event> &onSfmlEvent ();

		void addToDelete (const Node &item);
		void addToDelete (const Scene &item);

	private:
		void update (float delta);
		void draw (RenderTarget &target);

		RenderWindow *_window;
		AssetManager _assets;
		SoundManager _sounds;
		Random _gameRandom;
		UnitFactory _unitFac;
		BulletFactory _bulletFac;
		SpriteNode _background;
		Node _root;
		Scene *_scene;
		Clock _clock;
		Event<sf::Event> _onSfmlEvent;
		deque<const Node*> _deletes;
		deque<const Scene*> _sceneDeletes;
	};
}

#endif
