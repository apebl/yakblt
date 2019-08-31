#ifndef __BLT_WORLD_H__
#define __BLT_WORLD_H__

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "node.hpp"
#include "grid.hpp"
#include "scripter.hpp"
#include "event.hpp"
#include "unit.hpp"
#include "bullet.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "effect.hpp"

using namespace std;
using namespace sf;

namespace blt {
	class World : public Node, public ScripterContainer {
	public:
		World ();
		virtual ~World () override;

		/**
		 * @note It is the first child of the world.
		 */
		Node &back ();
		/**
		 * Gets the group node of enemies.
		 *
		 * @note It is a child of the world.
		 */
		Node &enemies ();
		/**
		 * Gets the group node of players.
		 *
		 * @note It is a child of the world.
		 */
		Node &players ();
		/**
		 * Gets the group node of effects.
		 *
		 * @note It is a child of the world.
		 */
		Node &effects ();
		/**
		 * Gets the group node of player bullets.
		 *
		 * @note It is a child of the world.
		 */
		Node &playerBullets ();
		/**
		 * Gets the group node of enemy bullets.
		 *
		 * @note It is a child of the world.
		 */
		Node &enemyBullets ();

		/**
		 * Gets the unit grid.
		 *
		 * @note It is a child of the world.
		 */
		Grid<Unit> &unitGrid ();
		/**
		 * Gets the bullet grid.
		 *
		 * @note It is a child of the world.
		 */
		Grid<Bullet> &bulletGrid ();
		/**
		 * Gets the group node for GUI.
		 *
		 * @note It is a child of the world.
		 */
		Node &gui ();

		void addUnit (Unit &unit);
		void removeUnit (Unit &unit);

		Player *getPlayer ();
		void addPlayer (Player &player);
		void removePlayer (Player &player);

		void addEnemy (Enemy &enemy);
		void removeEnemy (Enemy &enemy);

		void addBullet (Bullet &bullet);
		void removeBullet (Bullet &bullet);

		void addEffect (Effect &effect);
		void removeEffect (Effect &effect);

		void updateComponents ();

		void vibrate (float amount);

	protected:
		virtual void onUpdate (float delta) override;
	};
}

#endif
