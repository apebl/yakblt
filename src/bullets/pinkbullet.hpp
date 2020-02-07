#ifndef __BLT_PINKBULLET_H__
#define __BLT_PINKBULLET_H__

#include "../bullet.hpp"

namespace yakblt {
	class PinkBullet : public Bullet {
	public:
		PinkBullet ();
	protected:
		virtual void control () override;
		virtual void onDraw (RenderTarget &target) override;
	private:
		Sprite _sprite;
	};
}

#endif
