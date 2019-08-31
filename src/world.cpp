#include "world.hpp"
#include "config.hpp"
#include "globals.hpp"
#include "app.hpp"
#include <cmath>

namespace blt {
	World::World () {
		for (int i = 0; i < 6; i++) {
			addChild( *new Node() );
		}
		FloatRect bounds(0, 0, WORLD_WIDTH, WORLD_HEIGHT);
		Vector2f tileSize(GRID_TILE_WIDTH, GRID_TILE_HEIGHT);
		addChild( *new Grid<Unit>(bounds, tileSize) );
		addChild( *new Grid<Bullet>(bounds, tileSize) );
		addChild( *new Node() );
	}

	World::~World () {
	}

	Node &World::back () {
		return getChildAt(0);
	}

	Node &World::enemies () {
		return getChildAt(1);
	}

	Node &World::players () {
		return getChildAt(2);
	}

	Node &World::effects () {
		return getChildAt(3);
	}

	Node &World::playerBullets () {
		return getChildAt(4);
	}

	Node &World::enemyBullets () {
		return getChildAt(5);
	}

	Grid<Unit> &World::unitGrid () {
		return static_cast<Grid<Unit>&>(getChildAt(6));
	}

	Grid<Bullet> &World::bulletGrid () {
		return static_cast<Grid<Bullet>&>(getChildAt(7));
	}

	Node &World::gui () {
		return getChildAt(8);
	}

	void World::addUnit (Unit &unit) {
		if (dynamic_cast<Player*>(&unit) != nullptr) {
			addPlayer(static_cast<Player&>(unit));
		} else if (dynamic_cast<Enemy*>(&unit) != nullptr) {
			addEnemy(static_cast<Enemy&>(unit));
		} else {
			ERROR("The unit must be either a player or a enemy")
		}
	}

	void World::removeUnit (Unit &unit) {
		if (dynamic_cast<Player*>(&unit) != nullptr) {
			removePlayer(static_cast<Player&>(unit));
		} else if (dynamic_cast<Enemy*>(&unit) != nullptr) {
			removeEnemy(static_cast<Enemy&>(unit));
		} else {
			ERROR("The unit must be either a player or a enemy")
		}
	}

	Player *World::getPlayer () {
		if (players().numChildren() > 0) {
			return static_cast<Player*>(&players().getChildAt(0));
		} else {
			return nullptr;
		}
	}

	void World::addPlayer (Player &player) {
		if ( players().hasChild(player) ) return;
		players().addChild(player);
		unitGrid().addEntity(player);
	}

	void World::removePlayer (Player &player) {
		if ( !players().hasChild(player) ) return;
		players().removeChild(player);
		unitGrid().removeEntity(player);
	}

	void World::addEnemy (Enemy &enemy) {
		if ( enemies().hasChild(enemy) ) return;
		enemies().addChild(enemy);
		unitGrid().addEntity(enemy);
	}

	void World::removeEnemy (Enemy &enemy) {
		if ( !enemies().hasChild(enemy) ) return;
		enemies().removeChild(enemy);
		unitGrid().removeEntity(enemy);
	}

	void World::addBullet (Bullet &bullet) {
		switch (bullet.getOwnerType()) {
		case OwnerType::PLAYER:
			if ( playerBullets().hasChild(bullet) ) return;
			playerBullets().addChild(bullet);
			bulletGrid().addEntity(bullet);
			break;
		case OwnerType::ENEMY:
			if ( enemyBullets().hasChild(bullet) ) return;
			enemyBullets().addChild(bullet);
			bulletGrid().addEntity(bullet);
			break;
		default:
			ASSERT_NOT_REACHED
		}
	}

	void World::removeBullet (Bullet &bullet) {
		switch (bullet.getOwnerType()) {
		case OwnerType::PLAYER:
			if ( !playerBullets().hasChild(bullet) ) return;
			playerBullets().removeChild(bullet);
			bulletGrid().removeEntity(bullet);
			break;
		case OwnerType::ENEMY:
			if ( !enemyBullets().hasChild(bullet) ) return;
			enemyBullets().removeChild(bullet);
			bulletGrid().removeEntity(bullet);
			break;
		default:
			ASSERT_NOT_REACHED
		}
	}

	void World::addEffect (Effect &effect) {
		effects().addChild(effect);
	}

	void World::removeEffect (Effect &effect) {
		effects().removeChild(effect);
	}

	void World::updateComponents () {
		unitGrid().updateGrid();
		bulletGrid().updateGrid();
		updateScripters();
	}

	void World::vibrate (float amount) {
		float half = amount * 0.5f;
		float x = app().rand().floatRange(-half, half);
		float y = app().rand().floatRange(-half, half);
		if (x < 0) { x -= half; } else { x += half; }
		if (y < 0) { y -= half; } else { y += half; }
		setPosition(x, y);
	}

	void World::onUpdate (float delta) {
		// I've heard of tweening. but I don't have enough time.
		setPosition( getPosition() * 0.95f );
		if (length(getPosition()) < 0.01f) {
			setPosition(0, 0);
		}
	}
}