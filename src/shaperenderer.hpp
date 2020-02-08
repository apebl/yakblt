/* shaperenderer.hpp
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

#ifndef __BLT_SHAPERENDERER_H__
#define __BLT_SHAPERENDERER_H__

#include <SFML/Graphics.hpp>
#include "math.hpp"

using namespace std;
using namespace sf;

namespace yakblt {
	class ShapeRenderer {
	public:
		enum ShapeType {
			FILLED,
			LINE
		};

		ShapeRenderer ();

		void setRenderTarget (RenderTarget &target);
		Transform &getTransform ();
		void setTransform (const Transform &transform);
		void setColor (const Color &color);
		void setShapeType (ShapeType type);

		void drawLine (const Vector2f &a, const Vector2f &b) const;
		void draw (const FloatRect &rect) const;
		void draw (const Circle &circle) const;

	private:
		RenderTarget *_target;
		Transform _transform;
		Color _color;
		ShapeType _shapeType;
	};
}

#endif
