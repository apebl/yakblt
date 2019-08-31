#include "mine.hpp"
#include "../globals.hpp"
#include "../app.hpp"
#include "../assets.hpp"
#include "../config.hpp"
#include "../scores.hpp"
#include "../effects/mineexplosion.hpp"

using namespace blt;

namespace {
	const float speed = 1;
	const float health = 10;
	const long score = 100;
	const float vibration = 15;

	void createBullet (const Vector2f &pos, float rot) {
		Bullet *bullet = app().bulletFac().get("pink-bullet");
		ASSERT(bullet != nullptr)
		bullet->setPosition(pos);
		bullet->setRotation(rot);
		app().world().addBullet(*bullet);
	}
}

namespace blt {
	Mine::Mine () :
			DestroyableBullet(*new CircleCollidable(Circle(0, 0, 12)), ENEMY),
			_sprite( app().assets().loadTexture(MINE) ),
			_dest()
	{
		setHealth(health);
		FloatRect bounds = _sprite.getGlobalBounds();
		Vector2f origin = Vector2f(bounds.width * 0.5f, bounds.height * 0.5f);
		_sprite.setOrigin(origin);
		randomDest();
	}

	void Mine::setDest (const Vector2f &dest) {
		_dest = dest;
	}

	void Mine::randomDest () {
		_dest.x = app().rand().randFloat() * WORLD_WIDTH;
		_dest.y = app().rand().randFloat() * WORLD_HEIGHT;
	}

	void Mine::control () {
		if( isDead() ) return;
		float dist = blt::dist(getPosition(), _dest);
		if (dist < 2.0f) return;
		float rot = angleTo(getPosition(), _dest);
		move(angleVector(rot) * speed);
	}

	void Mine::dead () {
		Scores::add(score);

		Effect *effect = new MineExplosion();
		effect->setPosition( getPosition() );
		app().world().addEffect(*effect);
		app().world().vibrate(vibration);

		int num = app().rand().intRange(10, 31);
		for (int i = 0; i < num; i++) {
			createBullet(getPosition(), app().rand().randFloat() * 360.0f);
		}
	}

	void Mine::onDraw (RenderTarget &target) {
		RenderStates states = RenderStates( getGlobalTransform() );
		target.draw(_sprite, states);
	}
}