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
