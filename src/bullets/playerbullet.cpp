/* playerbullet.cpp
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
