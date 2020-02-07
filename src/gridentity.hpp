#ifndef __BLT_GRIDENTITY_H__
#define __BLT_GRIDENTITY_H__

#include <SFML/System.hpp>
#include "collisions.hpp"
#include "node.hpp"

using namespace std;
using namespace sf;

namespace yakblt {
	template <typename T>
	class Grid;

	/*
	 * @note GridEntities hold the ownership of the collidable and the grid.
	 */
	template <typename T>
	class GridEntity : public Node {
		// static_assert(is_base_of<GridEntity<T>, T>::value, "T must inherit from GridEntity<T>");

	public:
		GridEntity (Collidable &collidable);
		virtual ~GridEntity () override;

		const Collidable &getCollidable () const;

		const Grid<T> *getGrid () const;
		// void setGrid (const Grid<T> *grid);

		/**
		 * Gets the x position of the top-left corner of the grid
		 * bounds.
		 *
		 * @return The x position of the grid bounds
		 */
		int getGridX () const;
		/**
		 * Gets the y position of the top-left corner of the grid
		 * bounds.
		 *
		 * @return The y position of the grid bounds
		 */
		int getGridY () const;
		Vector2i getGridPos () const;
		const IntRect &getGridBounds () const;

		/**
		 * Gets whether or not this entity overlaps the grid.
		 * If doesn't, the entity is outside of the grid and
		 * the grid doesn't update the grid bounds of the entity.
		 *
		 * @return Whether or not this entity overlaps the grid
		 */
		bool isOverlappingGrid () const;

		/**
		 * Gets whether or not this entity is on the grid.
		 *
		 * @return Whether or not this entity is on the grid
		 */
		bool isOnGrid () const;

		virtual void drawDebug (RenderTarget &target) override;

	private:
		const Collidable *_collidable;
		const Grid<T> *_grid;
		IntRect _gridBounds;
		bool _isOnGrid;

		friend class Grid<T>;
	};
}

#include "gridentity.tpp"

#endif
