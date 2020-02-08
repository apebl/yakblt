/* shaperenderer.cpp
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

#include "shaperenderer.hpp"

namespace {
	const float THICKNESS = 1.0f;
}

namespace yakblt {
	ShapeRenderer::ShapeRenderer () :
			_target(nullptr),
			_transform(),
			_color(),
			_shapeType(FILLED)
	{
	}

	void ShapeRenderer::setRenderTarget (RenderTarget &target) {
		_target = &target;
	}

	Transform &ShapeRenderer::getTransform () {
		return _transform;
	}

	void ShapeRenderer::setTransform (const Transform &transform) {
		_transform = transform;
	}

	void ShapeRenderer::setColor (const Color &color) {
		_color = color;
	}

	void ShapeRenderer::setShapeType (ShapeType type) {
		_shapeType = type;
	}

	void ShapeRenderer::drawLine (const Vector2f &a, const Vector2f &b) const {
		Vertex vertices[] = {
			Vertex(a, _color), Vertex(b, _color)
		};
		_target->draw(vertices, 2, PrimitiveType::Lines);
	}

	void ShapeRenderer::draw (const FloatRect &rect) const {
		RectangleShape shape = RectangleShape( Vector2f(rect.width, rect.height) );
		shape.setPosition(rect.left, rect.top);
		if (_shapeType == ShapeType::FILLED) {
			shape.setFillColor(_color);
		} else {
			shape.setFillColor( Color(0, 0, 0, 0) );
			shape.setOutlineColor(_color);
			shape.setOutlineThickness(THICKNESS);
		}
		_target->draw( shape, RenderStates(_transform) );
	}

	void ShapeRenderer::draw (const Circle &circle) const {
		CircleShape shape = CircleShape(circle.radius);
		shape.setPosition(circle.x, circle.y);
		shape.setOrigin(circle.radius, circle.radius);
		if (_shapeType == ShapeType::FILLED) {
			shape.setFillColor(_color);
		} else {
			shape.setFillColor( Color(0, 0, 0, 0) );
			shape.setOutlineColor(_color);
			shape.setOutlineThickness(THICKNESS);
		}
		_target->draw( shape, RenderStates(_transform) );
	}
}
