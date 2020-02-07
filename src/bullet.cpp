#include "bullet.hpp"
#include "utils.hpp"
#include "globals.hpp"
#include "app.hpp"

namespace {
	const float restraintAreaScale = 1.8f;
}

namespace yakblt {
	Bullet::Bullet (Collidable &collidable, OwnerType owner) :
			GridEntity<Bullet>(collidable),
			_ownerType(owner),
			_isDead(false)
	{
	}

	Bullet::~Bullet () {
	}

	OwnerType Bullet::getOwnerType () {
		return _ownerType;
	}

	void Bullet::hit (Unit &unit) {
		kill();
	}

	bool Bullet::isDead () {
		return _isDead;
	}

	void Bullet::kill () {
		makeDead();
		removeFromWorld();
		app().addToDelete(*this);
	}

	void Bullet::removeFromWorld () {
		app().world().removeBullet(*this);
	}

	void Bullet::onUpdate (float delta) {
		if ( isDead() ) return;
		control();
		restrainActionArea();
	}

	void Bullet::control () {
	}

	void Bullet::restrainActionArea () {
		if( isDead() ) return;
		FloatRect bounds = getCollidable().getBounds( getGrid() );
		FloatRect area = getGrid()->getBounds();
		area = scaleRect(area, restraintAreaScale);
		if ( !area.intersects(bounds) ) {
			kill();
		}
	}

	void Bullet::makeDead () {
		ASSERT(!_isDead)
		_isDead = true;
		dead();
	}

	void Bullet::dead () {
	}
}
