#ifndef __BLT_SMALLEXPLOSION_H__
#define __BLT_SMALLEXPLOSION_H__

#include "../effect.hpp"
#include "../animation.hpp"

namespace yakblt {
	class SmallExplosion : public Effect {
	public:
		SmallExplosion ();
	protected:
		virtual void onUpdate (float delta) override;
		virtual void onDraw (RenderTarget &target) override;
	private:
		Animation _anim;
	};
}

#endif
