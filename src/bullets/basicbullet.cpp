/* basicbullet.cpp
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

#include "basicbullet.hpp"
#include "../globals.hpp"
#include "../app.hpp"
#include "../assets.hpp"

namespace {
	const float speed = 2.5f;
}

namespace yakblt {
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
