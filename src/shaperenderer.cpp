#include "shaperenderer.hpp"

namespace {
	const float THICKNESS = 1.0f;
}

namespace blt {
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