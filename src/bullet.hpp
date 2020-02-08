/* bullet.hpp
 *
 * Copyright (C) 2019-2020 Космическое П. <kosmospredanie@yandex.ru>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef __YAKBLT_BULLET_H__
#define __YAKBLT_BULLET_H__

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
