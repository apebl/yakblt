/* factory.hpp
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

#ifndef __YAKBLT_FACTORY_H__
#define __YAKBLT_FACTORY_H__

#include <string>
#include "bullet.hpp"
#include "player.hpp"
#include "bullets/playerbullet.hpp"
#include "bullets/basicbullet.hpp"
#include "bullets/missile.hpp"
#include "bullets/mine.hpp"
#include "bullets/pinkbullet.hpp"

using namespace std;

namespace yakblt {
	template <typename T>
	class Factory {
	public:
		virtual ~Factory () {
		}

		/**
		 * Creates an object for the name.
		 *
		 * @note You have to delete the returned object yourself.
		 *
		 * @return An object for the name, or null if no object for the name.
		 */
		virtual T *get (const string &name) = 0;
	};

	class UnitFactory : public Factory<Unit> {
	public:
		virtual Unit *get (const string &name) override {
			if (name == "player") {
				return new DefaultPlayer();
			} else {
				return nullptr;
			}
		}
	};

	class BulletFactory : public Factory<Bullet> {
	public:
		virtual Bullet *get (const string &name) override {
			if (name == "player-bullet") {
				return new PlayerBullet();
			} else if (name == "basic-bullet") {
				return new BasicBullet();
			} else if (name == "missile") {
				return new Missile();
			} else if (name == "mine") {
				return new Mine();
			} else if (name == "pink-bullet") {
				return new PinkBullet();
			} else {
				return nullptr;
			}
		}
	};
}

#endif
