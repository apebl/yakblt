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
