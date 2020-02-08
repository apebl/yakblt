/* collisions.hpp
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

#ifndef __YAKBLT_COLLISIONS_H__
#define __YAKBLT_COLLISIONS_H__

#include <cmath>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "math.hpp"
#include "node.hpp"

using namespace std;
using namespace sf;

namespace yakblt {
	enum CollidableType {
		CIRCLE,
		RECT
	};

	/**
	 * @note The transform of the node affects only the position of the
	 * Collidable and not the others -- scale, rotation, etc.
	 */
	class Collidable {
	public:
		Collidable ();
		virtual ~Collidable ();
		virtual CollidableType getType () const = 0;
		const Node *getNode () const;
		/**
		 * @note This Collidable doesn't hold the ownership of the given node.
		 */
		void setNode (const Node &node);
		virtual bool collideWith (const Collidable &other) const = 0;
		/**
		 * Gets the bounds in the given coordinates.
		 *
		 * @param[in] coordinates The coordinates
		 * @return The bounds in the given coordinates
		 */
		virtual FloatRect getBounds (const Node *coordinates) const = 0;
	private:
		const Node *_node;
	};

	class CircleCollidable : public Collidable {
	public:
		CircleCollidable (const Circle &circle);
		virtual ~CircleCollidable () override;
		virtual CollidableType getType () const override;
		virtual bool collideWith (const Collidable &other) const override;
		virtual FloatRect getBounds (const Node *coordinates) const override;
		const Circle &getCircle () const;
		/**
		 * Gets the circle in the given coordinates.
		 *
		 * @param[in] coordinates The coordinates
		 * @return The circle in the given coordinates
		 */
		Circle getCoordinatedCircle (const Node *coordinates) const;
	private:
		Circle _circle;
	};

	class RectCollidable : public Collidable {
	public:
		RectCollidable (const FloatRect &rect);
		virtual ~RectCollidable () override;
		virtual CollidableType getType () const override;
		virtual bool collideWith (const Collidable &other) const override;
		virtual FloatRect getBounds (const Node *coordinates) const override;
		const FloatRect &getRect () const;
	private:
		FloatRect _rect;
	};
}

#endif
