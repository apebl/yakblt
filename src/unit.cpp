/* unit.cpp
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

#include "unit.hpp"
#include "globals.hpp"
#include "app.hpp"
#include "bullet.hpp"

namespace yakblt {
	Unit::Unit (Collidable &collidable) :
			GridEntity<Unit>(collidable),
			_isDead(false),
			_onDead()
	{
	}

	Unit::~Unit () {
	}

	void Unit::hit (Bullet &bullet) {
		kill();
	}

	bool Unit::isDead () {
		return _isDead;
	}

	void Unit::kill () {
		makeDead();
		removeFromWorld();
		app().addToDelete(*this);
	}

	void Unit::removeFromWorld () {
		app().world().removeUnit(*this);
	}

	Event<Unit&> &Unit::onDead () {
		return _onDead;
	}

	void Unit::onUpdate (float delta) {
		if ( isDead() ) return;
		detectCollisions();
		control();
		restrainActionArea();
	}

	void Unit::control () {
	}

	void Unit::detectCollisions () {
		if ( isDead() || !isOnGrid() ) return;
		vector<Bullet*> bullets = app().world().bulletGrid().getEntities<Unit>(*this);
		for (auto bullet : bullets) {
			if ( !bullet->isDead() && isHostileTo(*bullet) ) {
				const Collidable &c = getCollidable();
				const Collidable &c2 = bullet->getCollidable();
				if ( c.collideWith(c2) ) {
					hit(*bullet);
					bullet->hit(*this);
					if (isDead()) return;
				}
			}
		}
	}

	void Unit::restrainActionArea () {
	}

	void Unit::makeDead () {
		ASSERT(!_isDead)
		_isDead = true;
		dead();
		_onDead.fireEvent(*this);
	}

	void Unit::dead () {
	}
}
