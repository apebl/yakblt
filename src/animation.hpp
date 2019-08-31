#ifndef __BLT_ANIMATION_H__
#define __BLT_ANIMATION_H__

#include <vector>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "scheduler.hpp"
#include "event.hpp"

using namespace std;
using namespace sf;

namespace blt {
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