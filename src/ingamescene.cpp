#include "ingamescene.hpp"
#include "globals.hpp"
#include "app.hpp"

namespace blt {
	InGameScene::InGameScene () : _world(nullptr) {
	}

	InGameScene::~InGameScene () {
	}

	void InGameScene::show (Scene *oldScene) {
		_world = new World();
		app().root().addChild(*_world);
	}

	void InGameScene::hide (Scene *newScene) {
		app().root().removeChild(*_world);
		app().addToDelete(*_world);
	}

	void InGameScene::update (float delta) {
		_world->updateComponents();
	}

	World &InGameScene::world () {
		return *_world;
	}
}