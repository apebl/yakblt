#ifndef __BLT_BULLET_H__
#define __BLT_BULLET_H__

#include "gridentity.hpp"

namespace yakblt {
	enum OwnerType {
		PLAYER,
		ENEMY
	};

	class Unit;

	class Bullet : public GridEntity<Bullet> {
	public:
		Bullet (Collidable &collidable, OwnerType owner);
		virtual ~Bullet () override;

		OwnerType getOwnerType ();
		// void setOwnerType (OwnerType owner);

		/**
		 * Will be called by a **hostile** unit, when the unit collides with
		 * this bullet.
		 *
		 * @param[in] unit The hostile unit
		 */
		virtual void hit (Unit &unit);
		bool isDead ();
		/**
		 * Kills this bullet.
		 *
		 * Default implementation: Makes this dead, remove it from the world,
		 * and add it to the delete list.
		 */
		virtual void kill ();
		/**
		 * Remove this bullet from the world.
		 *
		 * @note After this method, you have to delete this object manually
		 * if it has been allocated using 'new' operator.
		 */
		void removeFromWorld ();

	protected:
		virtual void onUpdate (float delta) override;
		virtual void control ();
		virtual void restrainActionArea ();
		void makeDead ();
		virtual void dead ();

	private:
		const OwnerType _ownerType;
		bool _isDead;
	};
}

#endif
