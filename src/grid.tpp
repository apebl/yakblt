/* grid.tpp
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

#include "grid.hpp"
#include <algorithm>
#include <cmath>
#include "utils.hpp"
#include "shaperenderer.hpp"

namespace yakblt {
	/* class Grid */

	template<typename T>
	Grid<T>::Grid (const FloatRect &bounds, const Vector2f &tileSize) :
			_transform(),
			_bounds(bounds),
			_tileSize(tileSize),
			_entities()
	{
		initGrid();
	}

	template <typename T>
	Grid<T>::~Grid () {
		clearEntities();
		delete [] _entitiesGrid;
	}

	template <typename T>
	const FloatRect &Grid<T>::getBounds () const {
		return _bounds;
	}

	template <typename T>
	const Vector2f &Grid<T>::getTileSize () const {
		return _tileSize;
	}

	template <typename T>
	const Vector2i &Grid<T>::getGridDim () const {
		return _gridDim;
	}

	template <typename T>
	size_t Grid<T>::numEntities () const {
		return _entities.size();
	}

	template <typename T>
	T* Grid<T>::getEntity (const Vector2i &pos) const {
		ASSERT(pos.x >= 0 && pos.y >= 0)
		ASSERT(pos.x < _gridDim.x && pos.y < _gridDim.y)
		int idx = pos.x + pos.y*_gridDim.x;
		if ( _entitiesGrid[idx].empty() ) {
			return nullptr;
		} else {
			return _entitiesGrid[idx].at(0);
		}
	}

	template <typename T>
	const vector<T*> &Grid<T>::getEntities () const {
		return _entities;
	}

	template <typename T>
	const vector<T*> &Grid<T>::getEntities (const Vector2i &pos) const {
		ASSERT(pos.x >= 0 && pos.y >= 0)
		ASSERT(pos.x < _gridDim.x && pos.y < _gridDim.y)
		int idx = pos.x + pos.y*_gridDim.x;
		return _entitiesGrid[idx];
	}

	template <typename T>
	vector<T*> Grid<T>::getEntities (const IntRect &bounds) const {
		ASSERT(bounds.width >= 0 && bounds.height >= 0)
		ASSERT(bounds.left >= 0 && bounds.top >= 0)
		ASSERT(bounds.left + bounds.width <= _gridDim.x
				&& bounds.top + bounds.height <= _gridDim.y)
		vector<T*> result = vector<T*>();
		for (int i = bounds.left; i < bounds.left + bounds.width; i++) {
			for (int j = bounds.top; j < bounds.top + bounds.height; j++) {
				const vector<T*> list = getEntities( Vector2i(i, j) );
				result.insert(result.end(), list.begin(), list.end());
			}
		}
		return result;
	}

	template <typename T>
	template <typename T2>
	vector<T*> Grid<T>::getEntities (const GridEntity<T2> &entity) const {
		const IntRect &bounds = entity.getGridBounds();
		return getEntities(bounds);
	}

	template <typename T>
	vector<T*> Grid<T>::getEntities (const GridEntity<T> &entity) const {
		return getEntities<T>(entity);
	}

	template <typename T>
	bool Grid<T>::hasEntity (const T &entity) const {
		typename vector<T*>::iterator iter = find(_entities.begin(), _entities.end(), &entity);
		return iter != _entities.end();
	}

	template <typename T>
	void Grid<T>::addEntity (T &entity) {
		typename vector<T*>::iterator iter = find(_entities.begin(), _entities.end(), &entity);
		if (iter == _entities.end()) {
			entity._grid = this;
			if ( entity.isOverlappingGrid() ) {
				IntRect bounds = calculateGridBound(entity);
				addEntityInto(entity, bounds);
				entity._gridBounds = bounds;
			}
			_entities.push_back(&entity);
		}
	}

	template <typename T>
	bool Grid<T>::removeEntity (T &entity) {
		typename vector<T*>::iterator iter = find(_entities.begin(), _entities.end(), &entity);
		if (iter != _entities.end()) {
			removeFromGrid(entity);
			_entities.erase(iter);
			entity._grid = nullptr;
			return true;
		} else {
			return false;
		}
	}

	template <typename T>
	void Grid<T>::clearEntities () {
		_entities.clear();
		for (int i = 0, n = _gridDim.x * _gridDim.y; i < n; i++) {
			_entitiesGrid[i].clear();
		}
	}

	template <typename T>
	void Grid<T>::updateGrid () {
		arrangeAllEntities();
	}

	/*
	template <typename T>
	void Grid<T>::onUpdate (float delta) {
		arrangeAllEntities();
	}
	*/

	template <typename T>
	void Grid<T>::onDrawDebug (RenderTarget &target) {
		ShapeRenderer renderer {};
		renderer.setRenderTarget(target);
		renderer.setTransform( getGlobalTransform() );

		for (int i = 0; i < _gridDim.x; i++) {
			for (int j = 0; j < _gridDim.y; j++) {
				GridEntity<T> *e = getEntity(Vector2i(i, j));
				if (e != nullptr) {
					renderer.setColor( Color(255, 255, 0, 50) );
					renderer.setShapeType(ShapeRenderer::ShapeType::FILLED);
				} else {
					renderer.setColor( Color(255, 255, 255, 50) );
					renderer.setShapeType(ShapeRenderer::ShapeType::LINE);
				}
				renderer.draw( FloatRect(i*_tileSize.x, j*_tileSize.y, _tileSize.x, _tileSize.y) );
			}
		}
	}

	template <typename T>
	void Grid<T>::initGrid () {
		_gridDim = Vector2i();
		_gridDim.x = (int) ceil(_bounds.width / _tileSize.x);
		_gridDim.y = (int) ceil(_bounds.height / _tileSize.y);
		_entitiesGrid = new vector<T*>[_gridDim.x * _gridDim.y];
	}

	template <typename T>
	void Grid<T>::removeFromGrid (T &entity) {
		if (entity._isOnGrid) {
			removeEntityFrom( entity, entity.getGridBounds() );
			entity._isOnGrid = false;
		}
	}

	template <typename T>
	void Grid<T>::addEntityInto (T &entity, const IntRect &bounds) {
		// assumes that the bounds has been normalized
		for (int i = bounds.left; i < bounds.left + bounds.width; i++) {
			for (int j = bounds.top; j < bounds.top + bounds.height; j++) {
				addEntityAt(entity, i, j);
			}
		}
	}

	template <typename T>
	void Grid<T>::addEntityAt (T &entity, int x, int y) {
		int idx = x + y*_gridDim.x;
		_entitiesGrid[idx].push_back(&entity);
		entity._isOnGrid = true;
	}

	static void normalizeEntityBoundsPos (IntRect &bounds, const Vector2i &gridDim) {
		bounds.left = max(bounds.left, 0);
		bounds.top = max(bounds.top, 0);
		bounds.left = min(bounds.left, gridDim.x - 1);
		bounds.top = min(bounds.top, gridDim.y - 1);
	}

	static void normalizeEntityBoundsSize (IntRect &bounds, const Vector2i &gridDim) {
		bounds.width = min(bounds.width, gridDim.x - bounds.left);
		bounds.height = min(bounds.height, gridDim.y - bounds.top);
	}

	template <typename T>
	void Grid<T>::removeEntityFrom (T &entity, const IntRect &bounds) {
		IntRect rect = bounds;
		normalizeEntityBoundsPos(rect, _gridDim);
		normalizeEntityBoundsSize(rect, _gridDim);
		for (int i = rect.left; i < rect.left + rect.width; i++) {
			for (int j = rect.top; j < rect.top + rect.height; j++) {
				removeEntityAt(entity, i, j);
			}
		}
	}

	template <typename T>
	void Grid<T>::removeEntityAt (T &entity, int x, int y) {
		int idx = x + y*_gridDim.x;
		vector<T*> &list = _entitiesGrid[idx];
		// You should prefix with 'typename'. std::vector<T>::iterator is a
		// type that is dependent on a template parameter
		typename vector<T*>::iterator iter = find(list.begin(), list.end(), &entity);
		if (iter != list.end()) {
			list.erase(iter);
		}
	}

	template <typename T>
	void Grid<T>::arrangeAllEntities () {
		for (auto entity : _entities) {
			arrangeEntity(*entity);
		}
	}

	template <typename T>
	void Grid<T>::arrangeEntity (T &entity) {
		removeFromGrid(entity);
		if ( entity.isOverlappingGrid() ) {
			IntRect rect = calculateGridBound(entity);
			addEntityInto(entity, rect);
			entity._gridBounds = rect;
		}
	}

	static constexpr int right (const FloatRect &rect) {
		return rect.left + rect.width;
	}

	static constexpr int bottom (const FloatRect &rect) {
		return rect.top + rect.height;
	}

	template <typename T>
	IntRect Grid<T>::calculateGridBound (const T &entity) {
		// assumes entity.isOverlappingMap()
		const FloatRect &entityBounds = entity.getCollidable().getBounds(this);
		IntRect result = IntRect();

		result.left = (int) ((entityBounds.left - _bounds.left) / _tileSize.x);
		result.top = (int) ((entityBounds.top - _bounds.top) / _tileSize.y);
		normalizeEntityBoundsPos(result, _gridDim);

		result.width = ( (int) ((right(entityBounds) - _bounds.left) / _tileSize.x - result.left) ) + 1;
		result.height = ( (int) ((bottom(entityBounds) - _bounds.top) / _tileSize.y - result.top) ) + 1;
		normalizeEntityBoundsSize(result, _gridDim);
		return result;
	}
}
