#include "destroyablebullet.hpp"

namespace blt {
	DestroyableBullet::DestroyableBullet (
			Collidable &collidable, OwnerType owner) :
		Bullet(collidable, owner), _health(0)
	{
	}

	float DestroyableBullet::getHealth () {
		return _health;
	}

	void DestroyableBullet::damaged (float damage) {
		if ( isDead() ) return;
		_health -= damage;
		if (_health <= 0) {
			kill();
		}
	}

	void DestroyableBullet::setHealth (float health) {
		_health = health;
	}
}