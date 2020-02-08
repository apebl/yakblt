/* animation.cpp
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

#include "animation.hpp"
#include "utils.hpp"

namespace {
	void split (const Texture &texture,
			const Vector2u &tileSize,
			vector<IntRect> &resultVector) {
		Vector2u texSize = texture.getSize();
		int cols = texSize.x / tileSize.x;
		int rows = texSize.y / tileSize.y;
		int y = 0;
		for (int r = 0; r < rows; r++) {
			int x = 0;
			for (int c = 0; c < cols; c++) {
				resultVector.emplace_back(x, y, tileSize.x, tileSize.y);
				x += tileSize.x;
			}
			y += tileSize.y;
		}
	}
}

namespace yakblt {
	Animation::Animation (const Texture &texture,
								const Vector2u &tileSize) :
			Sprite(texture),
			_currentFrame(0), _scheduler(), _regions(),
			_loop(false), _onFinished()
	{
		split(texture, tileSize, _regions);
		updateFrame(0);
		_scheduler.onRun().addHandler([this] {
			updateFrame(_currentFrame + 1);
		});
	}

	size_t Animation::numFrames () {
		return _regions.size();
	}

	size_t Animation::getCurrentFrame () {
		return _currentFrame;
	}

	void Animation::setCurrentFrame (size_t frame) {
		ASSERT(frame >= 0)
		ASSERT(frame < numFrames())
		updateFrame(frame);
	}

	int Animation::getInterval () {
		return _scheduler.frameInterval;
	}

	void Animation::setInterval (int interval) {
		_scheduler.frameInterval = interval;
	}

	bool Animation::isLoop () {
		return _loop;
	}

	void Animation::setLoop (bool loop) {
		_loop = loop;
	}

	void Animation::update () {
		_scheduler.update();
	}

	Event<Animation&> &Animation::onFinished () {
		return _onFinished;
	}

	void Animation::updateFrame (size_t frame) {
		if (frame >= _regions.size()) {
			if (_loop) {
				frame = 0;
			} else {
				_onFinished.fireEvent(*this);
				return;
			}
		}
		_currentFrame = frame;
		setTextureRect(_regions[frame]);
	}
}
