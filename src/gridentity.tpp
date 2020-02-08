/* gridentity.tpp
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

#include "gridentity.hpp"
#include "utils.hpp"
#include "shaperenderer.hpp"

namespace yakblt {
	/* class GridEntity */

	template <typename T>
	GridEntity<T>::GridEntity (Collidable &collidable) :
			Node(),
			_grid(nullptr),
			_gridBounds(),
			_isOnGrid(false)
	{
		ASSERT(collidable.getNode() == nullptr)
		collidable.setNode(*this);
		_collidable = &collidable;
	}

	template <typename T>
	GridEntity<T>::~GridEntity () {
		delete _collidable;
	}

	template <typename T>
	const Collidable &GridEntity<T>::getCollidable () const {
		return *_collidable;
	}

	template <typename T>
	const Grid<T> *GridEntity<T>::getGrid () const {
		return _grid;
	}

	/*
	template <typename T>
	void GridEntity<T>::setGrid (const Grid<T> *grid) {
		_grid = grid;
	}
	*/

	template <typename T>
	int GridEntity<T>::getGridX () const {
		return _gridBounds.left;
	}

	template <typename T>
	int GridEntity<T>::getGridY () const {
		return _gridBounds.top;
	}

	template <typename T>
	Vector2i GridEntity<T>::getGridPos () const {
		return Vector2i(_gridBounds.left, _gridBounds.top);
	}

	template <typename T>
	const IntRect &GridEntity<T>::getGridBounds () const {
		return _gridBounds;
	}

	template <typename T>
	bool GridEntity<T>::isOverlappingGrid () const {
		ASSERT(_grid != nullptr)
		return _grid->getBounds().intersects( getCollidable().getBounds(_grid) );
	}

	template <typename T>
	bool GridEntity<T>::isOnGrid () const {
		return _isOnGrid;
	}

	template <typename T>
	void GridEntity<T>::drawDebug (RenderTarget &target) {
		ASSERT( getParent() != nullptr )
		ShapeRenderer renderer {};
		renderer.setRenderTarget(target);
		renderer.setTransform( getRoot()->getGlobalTransform() );
		renderer.setColor( Color(255, 0, 0, 150) );
		const Collidable &c = getCollidable();
		switch ( c.getType() ) {
		case CollidableType::CIRCLE: {
			const CircleCollidable &cc = static_cast<const CircleCollidable&>(c);
			renderer.draw( cc.getCoordinatedCircle(getRoot()) );
			break;
		}
		case CollidableType::RECT: {
			const RectCollidable &rc = static_cast<const RectCollidable&>(c);
			renderer.draw( rc.getBounds(getRoot()) );
			break;
		}
		default:
			ASSERT_NOT_REACHED
		}
	}
}
