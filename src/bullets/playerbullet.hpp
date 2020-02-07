#ifndef __BLT_PLAYERBULLET_H__
#define __BLT_PLAYERBULLET_H__

#include "../bullet.hpp"

namespace yakblt {
	class PlayerBullet : public Bullet {
	public:
		PlayerBullet ();
	protected:
		virtual void onUpdate (float delta) override;
		virtual void control () override;
		void detectCollisions ();
		bool isHostileTo (Bullet &bullet);
		virtual void onDraw (RenderTarget &target) override;
	private:
		Sprite _sprite;
	};
}

#endif
