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
