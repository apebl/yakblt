/* animation.hpp
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

#ifndef __BLT_ANIMATION_H__
#define __BLT_ANIMATION_H__

#include <vector>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "scheduler.hpp"
#include "event.hpp"

using namespace std;
using namespace sf;

namespace yakblt {
	class Animation : public Sprite {
	public:
		Animation (const Texture &texture, const Vector2u &tileSize);
		size_t numFrames ();
		size_t getCurrentFrame ();
		void setCurrentFrame (size_t frame);
		int getInterval ();
		void setInterval (int interval);
		bool isLoop ();
		void setLoop (bool loop);
		void update ();
		Event<Animation&> &onFinished ();
	private:
		void updateFrame (size_t frame);
		size_t _currentFrame;
		Scheduler _scheduler;
		vector<IntRect> _regions;
		bool _loop;
		Event<Animation&> _onFinished;
	};
}

#endif
