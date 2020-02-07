#ifndef __BLT_ENEMY_H__
#define __BLT_ENEMY_H__

#include "unit.hpp"

namespace yakblt {
	class Enemy : public Unit {
	public:
		Enemy (Collidable &collidable);
		virtual ~Enemy () override;
		virtual bool isHostileTo (Bullet &bullet) override;
	protected:
		virtual void restrainActionArea () override;
	};
}

#endif
