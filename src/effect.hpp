#ifndef __BLT_EFFECT_H__
#define __BLT_EFFECT_H__

#include "node.hpp"

namespace yakblt {
	class Effect : public Node {
	public:
		Effect (int lifespan);
		virtual ~Effect () override;
		int getLifespan ();
		bool isDead ();
		virtual void kill ();
		void removeFromWorld ();
	protected:
		void makeDead ();
		virtual void dead ();
		virtual void onUpdate (float delta) override;
	private:
		int _lifespan; // in frames. negative => infinity
		bool _isDead;
	};
}

#endif
