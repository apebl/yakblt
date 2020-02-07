#ifndef __BLT_SCENE_H__
#define __BLT_SCENE_H__

#include "node.hpp"
#include "event.hpp"

namespace yakblt {
	class Scene {
	public:
		Scene ();
		virtual ~Scene ();
		/**
		 * Called just after this scene becomes the current scene.
		 *
		 * @param[in] oldScene The old scene
		 */
		virtual void show (Scene *oldScene);
		/**
		 * Called just before this scene is replaced by another scene.
		 *
		 * @param[in] newScene The new scene
		 */
		virtual void hide (Scene *newScene);
		virtual void update (float delta);
		virtual void draw (RenderTarget &target);
		Event<sf::Event> &onSfmlEvent ();

	private:
		Event<sf::Event> _onSfmlEvent;
	};
}

#endif
