#ifndef __BLT_DESTROYABLEBULLET_H__
#define __BLT_DESTROYABLEBULLET_H__

#include "../bullet.hpp"

namespace yakblt {
	class DestroyableBullet : public Bullet {
	public:
		DestroyableBullet (Collidable &collidable, OwnerType owner);
		float getHealth ();
		virtual void damaged (float damage);
	protected:
		void setHealth (float health);
	private:
		float _health;
	};
}

#endif
