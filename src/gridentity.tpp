#include "gridentity.hpp"
#include "utils.hpp"
#include "shaperenderer.hpp"

namespace blt {
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
