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
