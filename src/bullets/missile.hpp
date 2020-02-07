#ifndef __BLT_MISSILE_H__
#define __BLT_MISSILE_H__

#include "destroyablebullet.hpp"
#include "../scheduler.hpp"
#include "../animation.hpp"

namespace yakblt {
	class Missile : public DestroyableBullet {
	public:
		Missile ();
	protected:
		virtual void onUpdate (float delta) override;
		virtual void control () override;
		virtual void restrainActionArea () override;
		virtual void dead () override;
		virtual void onDraw (RenderTarget &target) override;
	private:
		Animation _anim;
		Vector2f _moveDelta;
	};
}

#endif
