#ifndef __BLT_MATH_H__
#define __BLT_MATH_H__

#include <cmath>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

#define M_E 2.7182818284590452354
#define PI 3.14159265358979323846
#define TWO_PI (PI * 2.0)
#define RAD_TO_DEG (180.0 / PI)
#define DEG_TO_RAD (PI / 180.0)

namespace yakblt {
	class Circle {
	public:
		Circle (float x = 0, float y = 0, float radius = 0);
		bool collideWith (const Circle &other) const;
		float x;
		float y;
		float radius;
	};

	FloatRect scaleRect (const FloatRect &rect, float scale);

	float deg2rad (float deg);
	float rad2deg (float rad);
	float shortestArc (float from, float to);

	/**
	 * Transforms the rect -- position only.
	 *
	 * @param[in] transform A transform
	 * @param[in] rect A rect
	 * @return The transformed rect
	 */
	FloatRect transformRectPos (const Transform &transform, const FloatRect &rect);
	/**
	 * Gets the position of the given transform
	 *
	 * @param[in] transform The transform
	 * @return The position of the transform
	 */
	Vector2f getPosition (const Transform &transform);
	/**
	 * Gets the rotation of the transform
	 *
	 * @param[in] transform The transform
	 * @return The rotation of the transform
	 */
	float getRotation (const Transform &transform);

	FloatRect mergeRects (const FloatRect &rect, const FloatRect &rect2);

	float distSq (const Vector2f &a, const Vector2f &b);
	float dist (const Vector2f &a, const Vector2f &b);
	float lengthSq (const Vector2f &v);
	float length (const Vector2f &v);
	Vector2f setLengthSq (const Vector2f &v, float val);
	Vector2f setLength (const Vector2f &v, float val);
	Vector2f limitLength (const Vector2f &v, float val);
	Vector2f norm (const Vector2f &v);
	float angle (const Vector2f &v);
	Vector2f rotate (const Vector2f &v, float rad);
	Vector2f setAngle (const Vector2f &v, float rad);
	Vector2f angleVector (float rad);
	float angleTo (const Vector2f &from, const Vector2f &to);
	Vector2f lerp (const Vector2f &v, const Vector2f &target, float t);
	Vector2f invert (const Vector2f &v);

	Vector2f rect (float width, float height, float t);
	Vector2f rect (FloatRect rect, float t);
	Vector2f ellipse (float width, float height, float t);
	Vector2f circle (float radius, float t);
	Vector2f fifthHeartCurve (float t);
	Vector2f astroid (float a, float t);
	Vector2f logarithmicSpiral (float a, float b, float t);
	Vector2f astroidPedalCurve (float a, float t);
}

#endif
