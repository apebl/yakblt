#include "enemy.hpp"
#include "bullet.hpp"
#include "grid.hpp"

namespace {
	const float restraintAreaScale = 1.8f;
}

namespace blt {
	Enemy::Enemy (Collidable &collidable) :
			Unit(collidable)
	{
	}

	Enemy::~Enemy () {
	}

	bool Enemy::isHostileTo (Bullet &bullet) {
		return bullet.getOwnerType() == OwnerType::PLAYER;
	}

	void Enemy::restrainActionArea () {
		if( isDead() ) return;
		FloatRect bounds = getCollidable().getBounds( getGrid() );
		FloatRect area = getGrid()->getBounds();
		area = scaleRect(area, restraintAreaScale);
		if ( !area.intersects(bounds) ) {
			kill();
		}
	}
}