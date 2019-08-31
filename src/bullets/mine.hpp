#ifndef __BLT_MINE_H__
#define __BLT_MINE_H__

#include "destroyablebullet.hpp"
#include "../scheduler.hpp"
#include "../animation.hpp"

namespace blt {
	class Mine : public DestroyableBullet {
	public:
		Mine ();
		void setDest (const Vector2f &dest);
		void randomDest ();
	protected:
		virtual void control () override;
		virtual void dead () override;
		virtual void onDraw (RenderTarget &target) override;
	private:
		Sprite _sprite;
		Vector2f _dest;
	};
}

#endif