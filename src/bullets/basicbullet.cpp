#include "basicbullet.hpp"
#include "../globals.hpp"
#include "../app.hpp"
#include "../assets.hpp"

namespace {
	const float speed = 2.5f;
}

namespace blt {
	BasicBullet::BasicBullet () :
			Bullet(*new CircleCollidable(Circle(0, 0, 4)), ENEMY),
			_sprite( app().assets().loadTexture(BASIC_BULLET) )
	{
		FloatRect bounds = _sprite.getGlobalBounds();
		Vector2f origin = Vector2f(bounds.width * 0.5f, bounds.height * 0.5f);
		_sprite.setOrigin(origin);
		_sprite.setScale(0.75f, 0.75f);
	}

	void BasicBullet::control () {
		if( isDead() ) return;
		move(angleVector(getRotation() * DEG_TO_RAD) * speed);
	}

	void BasicBullet::onDraw (RenderTarget &target) {
		RenderStates states = RenderStates( getGlobalTransform() );
		target.draw(_sprite, states);
	}
}