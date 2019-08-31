#include "math.hpp"

namespace blt {
	/* class Circle */

	Circle::Circle (float x, float y, float radius) :
			x(x), y(y), radius(radius)
	{
	}

	FloatRect scaleRect (const FloatRect &rect, float scale) {
		FloatRect result {};
		result.left = rect.left - rect.width * ((scale - 1.0f) * 0.5f);
		result.top = rect.top - rect.height * ((scale - 1.0f) * 0.5f);
		result.width = rect.width * scale;
		result.height = rect.height * scale;
		return result;
	}

	bool Circle::collideWith (const Circle &other) const {
		float dx = x - other.x;
		float dy = y - other.y;
		float dist = dx*dx + dy*dy;
		float radiusSum = radius + other.radius;
		return dist <= radiusSum*radiusSum;
	}

	FloatRect transformRectPos (const Transform &transform, const FloatRect &rect) {
		float halfw = rect.width / 2;
		float halfh = rect.height / 2;
		float cx = rect.left + halfw;
		float cy = rect.top + halfh;
		Vector2f vec = transform.transformPoint(cx, cy);
		return FloatRect(vec.x-halfw, vec.y-halfh, rect.width, rect.height);
	}

	float deg2rad (float deg) {
		return deg * DEG_TO_RAD;
	}

	float rad2deg (float rad) {
		return rad * RAD_TO_DEG;
	}

	float shortestArc (float from, float to) {
		if (fabs(to - from) < PI) {
			return to - from;
		} else if (to > from) {
			return to - from - (float)TWO_PI;
		} else {
			return to - from + (float)TWO_PI;
		}
	}

	Vector2f getPosition (const Transform &transform) {
		const float *data = transform.getMatrix();
		return Vector2f(data[6], data[7]); // (0, 2) and (1, 2)
	}

	float getRotation (const Transform &transform) {
		const float *data = transform.getMatrix();
		return atan2(data[1], data[0]); // (1, 0) and (0, 0)
	}

	FloatRect mergeRects (const FloatRect &rect, const FloatRect &rect2) {
		float minX = min(rect.left, rect2.left);
		float maxX = min(rect.left + rect.width, rect2.left + rect2.width);
		float minY = min(rect.top, rect2.top);
		float maxY = min(rect.top + rect.height, rect2.top + rect2.height);
		return FloatRect(minX, minY, maxX - minX, maxY - minY);
	}

	float distSq (const Vector2f &a, const Vector2f &b) {
		float dx = a.x - b.x;
		float dy = a.y - b.y;
		return dx*dx + dy*dy;
	}

	float dist (const Vector2f &a, const Vector2f &b) {
		return sqrt( distSq(a, b) );
	}

	float lengthSq (const Vector2f &v) {
		return v.x*v.x + v.y*v.y;
	}

	float length (const Vector2f &v) {
		return sqrt( lengthSq(v) );
	}

	Vector2f setLengthSq (const Vector2f &v, float val) {
		float prevLen = lengthSq(v);
		if (prevLen != 0 && prevLen != val) {
			float d = sqrt(val / prevLen);
			return Vector2f(v.x*d, v.y*d);
		}
		return v;
	}

	Vector2f setLength (const Vector2f &v, float val) {
		return setLengthSq(v, val*val);
	}

	Vector2f limitLength (const Vector2f &v, float val) {
		float valsq = val*val;
		float prevLen = lengthSq(v);
		if (prevLen != 0 && prevLen > valsq) {
			float d = sqrt(valsq / prevLen);
			return Vector2f(v.x*d, v.y*d);
		}
		return v;
	}

	Vector2f norm (const Vector2f &v) {
		float lsq = lengthSq(v);
		if (lsq != 0 && lsq != 1) {
			return v * ( 1.0f / sqrt(lsq) );
		}
		return v;
	}

	float angle (const Vector2f &v) {
		return atan2(v.y, v.x);
	}

	Vector2f rotate (const Vector2f &v, float rad) {
		float c = cos(rad);
		float s = sin(rad);
		float nx = v.x*c - v.y*s;
		float ny = v.x*s + v.y*c;
		return Vector2f(nx, ny);
	}

	Vector2f setAngle (const Vector2f &v, float rad) {
		Vector2f vec = v;
		vec.x = length(v);
		vec.y = 0;
		return rotate(vec, rad);
	}

	Vector2f angleVector (float rad) {
		return Vector2f(cos(rad), sin(rad));
	}

	float angleTo (const Vector2f &from, const Vector2f &to) {
		return atan2(to.y - from.y, to.x - from.x);
	}

	Vector2f lerp (const Vector2f &v, const Vector2f &target, float t) {
		float nx = v.x + t * (target.x - v.x);
		float ny = v.y + t * (target.y - v.y);
		return Vector2f(nx, ny);
	}

	Vector2f invert (const Vector2f &v) {
		return Vector2f(-v.x, -v.y);
	}

	Vector2f rect (float width, float height, float t) {
		float len = (width*2 + height*2) * fmod(t, 1.0f);
		float two = width;
		float three = width+height;
		float four = width+width+height;
		if (len > four) {
			return Vector2f(0, len - four);
		} else if (len > three) {
			return Vector2f(len - three, height);
		} else if (len > two) {
			return Vector2f(width, len - two);
		} else {
			return Vector2f(len, 0);
		}
	}

	Vector2f rect (FloatRect rect, float t) {
		return Vector2f(rect.left, rect.top) + blt::rect(rect.width, rect.height, t);
	}

	Vector2f ellipse (float width, float height, float t) {
		float x = cos(t*(float)TWO_PI) * width;
		float y = sin(t*(float)TWO_PI) * height;
		return Vector2f(x, y);
	}

	Vector2f circle (float radius, float t) {
		float diameter = radius + radius;
		return ellipse(diameter, diameter, t);
	}

	Vector2f fifthHeartCurve (float t) {
		float x = pow(sin(t), 3) * 16;
		float y = 13*cos(t) - 5*cos(2*t) - 2*cos(3*t) - cos(4*t);
		return Vector2f(x, y);
	}

	Vector2f astroid (float a, float t) {
		float x = a * pow(cos(t), 3);
		float y = a * pow(sin(t), 3);
		return Vector2f(x, y);
	}

	Vector2f logarithmicSpiral (float a, float b, float t) {
		float x = a * pow(M_E, b*t) * cos(t);
		float y = a * pow(M_E, b*t) * sin(t);
		return Vector2f(x, y);
	}

	Vector2f astroidPedalCurve (float a, float t) {
		float x = a * cos(t) * pow(sin(t), 2);
		float y = a * pow(cos(t), 2) * sin(t);
		return Vector2f(x, y);
	}
}