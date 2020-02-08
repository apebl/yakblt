/* grid.hpp
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

#ifndef __BLT_GRID_H__
#define __BLT_GRID_H__

#include <vector>
#include <type_traits>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "collisions.hpp"
#include "node.hpp"

using namespace std;
using namespace sf;

namespace yakblt {
	template <typename T>
	class GridEntity;

	/**
	 * A grid of entities.
	 *
	 * Grids don't hold the ownership of the entities.
	 *
	 * @note In collision check, the transform of a grid affects only the
	 * position of the grid and not the others -- scale, rotation, etc.
	 */
	template <typename T>
	class Grid : public Node {
		static_assert(is_base_of<GridEntity<T>, T>::value, "T must inherit from GridEntity<T>");

	public:
		Grid (const FloatRect &bounds, const Vector2f &tileSize);
		virtual ~Grid ();

		/**
		 * Gets the bounds of this grid.
		 *
		 * @return The bounds
		 */
		const FloatRect &getBounds () const;

		/**
		 * Gets the size of each tile.
		 *
		 * @return The size
		 */
		const Vector2f &getTileSize () const;
		/**
		 * @return A vector containing the number of rows(y) and columns(x).
		 */
		const Vector2i &getGridDim () const;

		size_t numEntities () const;
		/**
		 * Gets an entity at the position.
		 *
		 * @return An entity, or null if not found
		 */
		T* getEntity (const Vector2i &pos) const;
		/**
		 * Gets all the entities.
		 *
		 * @return The entities
		 */
		const vector<T*> &getEntities () const;
		/**
		 * Gets the entities at the position.
		 *
		 * @param[in] pos The position
		 * @return The entities
		 */
		const vector<T*> &getEntities (const Vector2i &pos) const;
		/**
		 * Gets the entities within the rectangular area.
		 *
		 * @param[in] bounds The area
		 * @return The entities
		 */
		vector<T*> getEntities (const IntRect &bounds) const;
		/**
		 * Gets the entities of which the grid-bounds colliding
		 * with the grid-bound of the given entity.
		 *
		 * @param[in] entity The entity
		 * @return The entities
		 */
		template <typename T2>
		vector<T*> getEntities (const GridEntity<T2> &entity) const;
		/**
		 * Gets the entities of which the grid-bounds colliding
		 * with the grid-bound of the given entity.
		 *
		 * @param[in] entity The entity
		 * @return The entities
		 */
		vector<T*> getEntities (const GridEntity<T> &entity) const;

		bool hasEntity (const T &entity) const;
		/**
		 * Adds the entity into this grid.
		 *
		 * @param[in] entity The entity to be added
		 */
		void addEntity (T &entity);
		/**
		 * Removes the entity from this grid.
		 *
		 * @param[in] entity The entity to be removed
		 * @return true if removed, false otherwise.
		 */
		bool removeEntity (T &entity);
		/**
		 * Removes all entities from this grid.
		 */
		void clearEntities ();

		void updateGrid ();

	protected:
		// virtual void onUpdate (float delta) override;
		virtual void onDrawDebug (RenderTarget &target) override;

	private:
		void initGrid ();
		void updateGlobalBounds ();
		void removeFromGrid (T &entity);
		void addEntityInto (T &entity, const IntRect &bounds);
		void addEntityAt (T &entity, int x, int y);
		void removeEntityFrom (T &entity, const IntRect &bounds);
		void removeEntityAt (T &entity, int x, int y);
		void arrangeAllEntities ();
		void arrangeEntity (T &entity);
		IntRect calculateGridBound (const T &entity);

		Transform _transform;
		const FloatRect _bounds;
		const Vector2f _tileSize;
		Vector2i _gridDim;

		vector<T*> _entities;
		vector<T*> *_entitiesGrid;
	};
}

#include "grid.tpp"

#endif
