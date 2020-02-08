/* mineexplosion.cpp
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

#include "mineexplosion.hpp"
#include "../config.hpp"
#include "../globals.hpp"
#include "../app.hpp"
#include "../assets.hpp"

namespace {
	const int lifespan = FRAMERATE / 2;
}

namespace yakblt {
	MineExplosion::MineExplosion () :
		Effect(lifespan),
		_anim( app().assets().loadTexture(MINE_EXPLOSION), Vector2u(53, 53) )
	{
		_anim.setInterval( lifespan / _anim.numFrames() );
		FloatRect bounds = _anim.getGlobalBounds();
		Vector2f origin = Vector2f(bounds.width * 0.5f, bounds.height * 0.5f);
		_anim.setOrigin(origin);
		_anim.setScale(1.5f, 1.5f);
	}

	void MineExplosion::onUpdate (float delta) {
		if ( isDead() ) return;
		Effect::onUpdate(delta);
		_anim.update();
	}

	void MineExplosion::onDraw (RenderTarget &target) {
		RenderStates states = RenderStates( getGlobalTransform() );
		target.draw(_anim, states);
	}
}
