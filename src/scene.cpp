#include "scene.hpp"

namespace blt {
	Scene::Scene () : _onSfmlEvent() {
	}

	Scene::~Scene () {
	}

	void Scene::show (Scene *oldScene) {
	}

	void Scene::hide (Scene *newScene) {
	}

	void Scene::update (float delta) {
	}

	void Scene::draw (RenderTarget &target) {
	}

	Event<sf::Event> &Scene::onSfmlEvent () {
		return _onSfmlEvent;
	}
}