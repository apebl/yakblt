/* basicpattern.cpp
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

#include "basicpattern.hpp"
#include "../config.hpp"
#include "../globals.hpp"
#include "../app.hpp"
#include "../math.hpp"

namespace yakblt {
	void BasicPattern::init () {
		loop([] { return true; }, [this] {
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 15; j++) {
					float t = app().rand().randFloat();
					Vector2f pos = rect(WORLD_RECT, t);
					float angle = angleTo(pos, WORLD_CENTER) * RAD_TO_DEG;
					createBullet("basic-bullet", pos.x, pos.y, angle + app().rand().floatRange(-45, 45));
					wait(0.05f);
				}
				wait(0.5f);
			}
			wait(2);
		});
	}
}
