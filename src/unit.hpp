#ifndef __BLT_UNIT_H__
#define __BLT_UNIT_H__

#include "gridentity.hpp"
#include "scripter.hpp"
#include "event.hpp"

namespace yakblt {
	class Bullet;

	class Unit : public GridEntity<Unit> {
	public:
		Unit (Collidable &collidable);
		virtual ~Unit () override;

		virtual bool isHostileTo (Bullet &bullet) = 0;
		/**
		 * Will be called when the unit collides with a **hostile** bullet.
		 *
		 * @param[in] bullet The bullet
		 */
		virtual void hit (Bullet &bullet);
		bool isDead ();
		/**
		 * Kills this unit.
		 *
		 * Default implementation: Makes this dead, remove it
		 * from the world, and delete it.
		 */
		virtual void kill ();
		/**
		 * After this method, you have to delete this object manually if it
		 * has been allocated using operator new.
		 */
		void removeFromWorld ();

		Event<Unit&> &onDead ();

	protected:
		/**
		 * All methods overriding this method must call their base method.
		 */
		virtual void onUpdate (float delta) override;
		virtual void control ();
		virtual void detectCollisions ();
		virtual void restrainActionArea ();
		void makeDead ();
		virtual void dead ();

	private:
		bool _isDead;
		Event<Unit&> _onDead;
	};
}

#endif
