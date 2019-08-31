#ifndef __BLT_INGAMESCENE_H__
#define __BLT_INGAMESCENE_H__

#include "scene.hpp"
#include "world.hpp"

namespace blt {
	class InGameScene : public Scene {
	public:
		InGameScene ();
		virtual ~InGameScene () override;
		virtual void show (Scene *oldScene) override;
		virtual void hide (Scene *newScene) override;
		virtual void update (float delta) override;
		World &world ();

	private:
		World *_world;
	};
}

#endif