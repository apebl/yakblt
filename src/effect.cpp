#include "effect.hpp"
#include "globals.hpp"
#include "app.hpp"

namespace yakblt {
	Effect::Effect (int lifespan) :
		_lifespan(lifespan),
		_isDead(false)
	{
	}

	Effect::~Effect () {
	}

	int Effect::getLifespan () {
		return _lifespan;
	}

	bool Effect::isDead () {
		return _isDead;
	}

	void Effect::kill () {
		makeDead();
		removeFromWorld();
		app().addToDelete(*this);
	}

	void Effect::removeFromWorld () {
		app().world().removeEffect(*this);
	}

	void Effect::makeDead () {
		ASSERT(!_isDead)
		_isDead = true;
		dead();
	}

	void Effect::dead () {
	}

	void Effect::onUpdate (float delta) {
		if (_lifespan > 0) {
			_lifespan--;
		} else if (_lifespan == 0) {
			kill();
		}
	}
}
