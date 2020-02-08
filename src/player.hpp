/* player.hpp
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

#ifndef __YAKBLT_PLAYER_H__
#define __YAKBLT_PLAYER_H__

#include "unit.hpp"
#include "spritenode.hpp"

namespace yakblt {
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
