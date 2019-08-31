#ifndef __BLT_FACTORY_H__
#define __BLT_FACTORY_H__

#include <string>
#include "bullet.hpp"
#include "player.hpp"
#include "bullets/playerbullet.hpp"
#include "bullets/basicbullet.hpp"
#include "bullets/missile.hpp"
#include "bullets/mine.hpp"
#include "bullets/pinkbullet.hpp"

using namespace std;

namespace blt {
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
