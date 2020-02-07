#ifndef __BLT_BASICBULLET_H__
#define __BLT_BASICBULLET_H__

#include "../bullet.hpp"

namespace yakblt {
	class BasicBullet : public Bullet {
	public:
		BasicBullet ();
	protected:
		virtual void control () override;
		virtual void onDraw (RenderTarget &target) override;
	private:
		Sprite _sprite;
	};
}

#endif
