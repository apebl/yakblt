/* minepattern.cpp
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

#include "minepattern.hpp"
#include "../config.hpp"
#include "../globals.hpp"
#include "../app.hpp"
#include "../math.hpp"

namespace yakblt {
	void MinePattern::init () {
		loop([] { return true; }, [this] {
			for (int i = 0; i < 3; i++) {
				int num = app().rand().intRange(2, 5);
				for (int j = 0; j < num; j++) {
					float t = app().rand().randFloat();
					Vector2f pos = rect(WORLD_RECT, t);
					createBullet("mine", pos.x, pos.y, 0);
					wait(2);
				}
				wait(5);
			}
			wait(8);
		});
	}
}
