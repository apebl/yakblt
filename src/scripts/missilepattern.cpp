#include "missilepattern.hpp"
#include "../config.hpp"
#include "../globals.hpp"
#include "../app.hpp"
#include "../math.hpp"

namespace yakblt {
	void MissilePattern::init () {
		loop([] { return true; }, [this] {
			for (int i = 0; i < 5; i++) {
				int num = app().rand().intRange(3, 5);
				for (int j = 0; j < num; j++) {
					float t = app().rand().randFloat();
					Vector2f pos = rect(WORLD_RECT, t);
					float angle = angleTo(pos, WORLD_CENTER) * RAD_TO_DEG;
					createBullet("missile", pos.x, pos.y, angle);
					wait(0.5f);
				}
				wait(2);
			}
			wait(5);
		});
	}
}
