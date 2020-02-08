/* mine.cpp
 *
 * Copyright (C) 2019-2020 Космическое П. <kosmospredanie@yandex.ru>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "mine.hpp"
#include "../globals.hpp"
#include "../app.hpp"
#include "../assets.hpp"
#include "../config.hpp"
#include "../scores.hpp"
#include "../effects/mineexplosion.hpp"

using namespace yakblt;

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

namespace yakblt {
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
		float dist = yakblt::dist(getPosition(), _dest);
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
