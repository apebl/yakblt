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

namespace blt {
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