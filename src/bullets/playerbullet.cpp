#include "playerbullet.hpp"
#include "destroyablebullet.hpp"
#include "../globals.hpp"
#include "../app.hpp"
#include "../assets.hpp"

namespace {
	const float speed = 20;
	const float damage = 0.5f;
}

namespace yakblt {
	PlayerBullet::PlayerBullet () :
			Bullet(*new CircleCollidable(Circle(0, 0, 8)), PLAYER),
			_sprite( app().assets().loadTexture(FIGHTER_BULLET) )
	{
		FloatRect bounds = _sprite.getGlobalBounds();
		Vector2f origin = Vector2f(bounds.width * 0.75f, bounds.height * 0.5f);
		_sprite.setOrigin(origin);
		_sprite.setScale(0.5f, 0.5f);
		_sprite.setColor( Color(255, 255, 255, 200) );
	}

	void PlayerBullet::onUpdate (float delta) {
		if ( isDead() ) return;
		detectCollisions();
		Bullet::onUpdate(delta);
	}

	void PlayerBullet::control () {
		if( isDead() ) return;
		move(angleVector(getRotation() * DEG_TO_RAD) * speed);
	}

	void PlayerBullet::detectCollisions () {
		if ( isDead() || !isOnGrid() ) return;
		vector<Bullet*> bullets = app().world().bulletGrid().getEntities(*this);
		for (auto el : bullets) {
			DestroyableBullet *bullet = dynamic_cast<DestroyableBullet*>(el);
			if ( bullet != nullptr && !bullet->isDead() && isHostileTo(*bullet) ) {
				const Collidable &c = getCollidable();
				const Collidable &c2 = bullet->getCollidable();
				if ( c.collideWith(c2) ) {
					bullet->damaged(damage);
					kill();
					return;
				}
			}
		}
	}

	bool PlayerBullet::isHostileTo (Bullet &bullet) {
		return bullet.getOwnerType() == OwnerType::ENEMY;
	}

	void PlayerBullet::onDraw (RenderTarget &target) {
		RenderStates states = RenderStates( getGlobalTransform() );
		target.draw(_sprite, states);
	}
}
