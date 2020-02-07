#include "unit.hpp"
#include "globals.hpp"
#include "app.hpp"
#include "bullet.hpp"

namespace yakblt {
	Unit::Unit (Collidable &collidable) :
			GridEntity<Unit>(collidable),
			_isDead(false),
			_onDead()
	{
	}

	Unit::~Unit () {
	}

	void Unit::hit (Bullet &bullet) {
		kill();
	}

	bool Unit::isDead () {
		return _isDead;
	}

	void Unit::kill () {
		makeDead();
		removeFromWorld();
		app().addToDelete(*this);
	}

	void Unit::removeFromWorld () {
		app().world().removeUnit(*this);
	}

	Event<Unit&> &Unit::onDead () {
		return _onDead;
	}

	void Unit::onUpdate (float delta) {
		if ( isDead() ) return;
		detectCollisions();
		control();
		restrainActionArea();
	}

	void Unit::control () {
	}

	void Unit::detectCollisions () {
		if ( isDead() || !isOnGrid() ) return;
		vector<Bullet*> bullets = app().world().bulletGrid().getEntities<Unit>(*this);
		for (auto bullet : bullets) {
			if ( !bullet->isDead() && isHostileTo(*bullet) ) {
				const Collidable &c = getCollidable();
				const Collidable &c2 = bullet->getCollidable();
				if ( c.collideWith(c2) ) {
					hit(*bullet);
					bullet->hit(*this);
					if (isDead()) return;
				}
			}
		}
	}

	void Unit::restrainActionArea () {
	}

	void Unit::makeDead () {
		ASSERT(!_isDead)
		_isDead = true;
		dead();
		_onDead.fireEvent(*this);
	}

	void Unit::dead () {
	}
}
