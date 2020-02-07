#include "collisions.hpp"
#include "utils.hpp"

namespace yakblt {
	/* class Collidable */

	Collidable::Collidable () :
			_node(nullptr)
	{
	}

	Collidable::~Collidable () {
	}

	const Node *Collidable::getNode () const {
		return _node;
	}

	void Collidable::setNode (const Node &node) {
		_node = &node;
	}

	static bool collisionCircleCircle (const Circle &circle, const Circle &circle2) {
		return circle.collideWith(circle2);
	}

	static bool collisionCircleRect (const Circle &circle, const FloatRect &rect) {
		float distX = abs(circle.x - rect.left);
		float distY = abs(circle.y - rect.top);
		if(distX > (rect.width/2 + circle.radius)) {
			return false;
		} else if(distY > (rect.height/2 + circle.radius)) {
			return false;
		} else if(distX <= rect.width/2) {
			return true;
		} else if(distY <= rect.height/2) {
			return true;
		} else {
			float cornerDist = pow(distX - rect.width/2, 2) + pow(distY - rect.height/2, 2);
			return cornerDist <= pow(circle.radius, 2);
		}
	}

	static bool collisionRectRect (const FloatRect &rect, const FloatRect &rect2) {
		return rect.intersects(rect2);
	}

	/* class CircleCollidable */

	CircleCollidable::CircleCollidable (const Circle &circle) :
			_circle(circle)
	{
	}

	CircleCollidable::~CircleCollidable () {
	}

	CollidableType CircleCollidable::getType () const {
		return CollidableType::CIRCLE;
	}

	bool CircleCollidable::collideWith (const Collidable &other) const {
		switch (other.getType()) {
		case CollidableType::CIRCLE:
			return collisionCircleCircle( getCoordinatedCircle(nullptr), static_cast<const CircleCollidable&>(other).getCoordinatedCircle(nullptr) );
		case CollidableType::RECT:
			return collisionCircleRect( getCoordinatedCircle(nullptr), static_cast<const RectCollidable&>(other).getBounds(nullptr) );
		default:
			ASSERT_NOT_REACHED
		}
	}

	/*
	FloatRect CircleCollidable::getLocalBounds () const {
		FloatRect rect;
		rect.left = _circle.x - _circle.radius;
		rect.top = _circle.y - _circle.radius;
		rect.width = _circle.radius * 2;
		rect.height = rect.width;
		return rect;
	}
	*/

	FloatRect CircleCollidable::getBounds (const Node *coordinates) const {
		ASSERT(getNode() != nullptr)
		Vector2f vec = getNode()->localTo(coordinates, Vector2f(_circle.x, _circle.y));
		float r2 = _circle.radius * 2;
		return FloatRect(vec.x - _circle.radius, vec.y - _circle.radius, r2, r2);
	}

	const Circle &CircleCollidable::getCircle () const {
		return _circle;
	}

	Circle CircleCollidable::getCoordinatedCircle (const Node *coordinates) const {
		ASSERT(getNode() != nullptr)
		Vector2f vec = getNode()->localTo(coordinates, Vector2f(_circle.x, _circle.y));
		return Circle(vec.x, vec.y, _circle.radius);
	}

	/* class RectCollidable */

	RectCollidable::RectCollidable (const FloatRect &rect) :
			_rect(rect)
	{
	}

	RectCollidable::~RectCollidable () {
	}

	CollidableType RectCollidable::getType () const {
		return CollidableType::RECT;
	}

	bool RectCollidable::collideWith (const Collidable &other) const {
		switch (other.getType()) {
		case CollidableType::CIRCLE:
			return collisionCircleRect( static_cast<const CircleCollidable&>(other).getCoordinatedCircle(nullptr), getBounds(nullptr) );
		case CollidableType::RECT:
			return collisionRectRect( getBounds(nullptr), static_cast<const RectCollidable&>(other).getBounds(nullptr) );
		default:
			ASSERT_NOT_REACHED
		}
	}

	/*
	FloatRect RectCollidable::getLocalBounds () const {
		return _rect;
	}
	*/

	FloatRect RectCollidable::getBounds (const Node *coordinates) const {
		ASSERT(getNode() != nullptr)
		float halfw = _rect.width / 2;
		float halfh = _rect.height / 2;
		float cx = _rect.left + halfw;
		float cy = _rect.top + halfh;
		Vector2f vec = getNode()->localTo(coordinates, Vector2f(cx, cy));
		return FloatRect(vec.x-halfw, vec.y-halfh, _rect.width, _rect.height);
	}

	const FloatRect &RectCollidable::getRect () const {
		return _rect;
	}
}
