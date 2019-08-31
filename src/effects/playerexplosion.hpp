#ifndef __BLT_PLAYEREXPLOSION_H__
#define __BLT_PLAYEREXPLOSION_H__

#include "../effect.hpp"
#include "../animation.hpp"

namespace blt {
	class PlayerExplosion : public Effect {
	public:
		PlayerExplosion ();
	protected:
		virtual void onUpdate (float delta) override;
		virtual void onDraw (RenderTarget &target) override;
	private:
		Animation _anim;
	};
}

#endif