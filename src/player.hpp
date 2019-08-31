#ifndef __BLT_PLAYER_H__
#define __BLT_PLAYER_H__

#include "unit.hpp"
#include "spritenode.hpp"

namespace blt {
	class Player : public Unit {
	public:
		Player (Collidable &collidable);
		virtual ~Player () override;
		virtual bool isHostileTo (Bullet &bullet) override;
	protected:
		virtual void restrainActionArea () override;
	};

	class DefaultPlayer : public Player {
	public:
		DefaultPlayer ();
		virtual Vector2f getContentSize () const override;
		virtual void setContentSize (const Vector2f &size) override;
		void shot ();
	protected:
		virtual void onDraw (RenderTarget &target) override;
		virtual void control () override;
		virtual void dead () override;
	private:
		Sprite _sprite;
		Vector2f _moveDelta;
		int _shotCount;
	};
}

#endif