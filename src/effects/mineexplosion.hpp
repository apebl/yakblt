#ifndef __BLT_MINEEXPLOSION_H__
#define __BLT_MINEEXPLOSION_H__

#include "../effect.hpp"
#include "../animation.hpp"

namespace blt {
	class MineExplosion : public Effect {
	public:
		MineExplosion ();
	protected:
		virtual void onUpdate (float delta) override;
		virtual void onDraw (RenderTarget &target) override;
	private:
		Animation _anim;
	};
}

#endif