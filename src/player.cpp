#include "player.hpp"
#include "bullet.hpp"
#include "globals.hpp"
#include "app.hpp"
#include "config.hpp"
#include "assets.hpp"
#include "math.hpp"
#include "effects/playerexplosion.hpp"
#include <limits>

namespace {
	const float maxSpeed = 4;
	const float accel = 0.5f;
	const float friction = 0.9f;
	const float rotMul = 0.1f;
	const int shotInterval = 3;
	const float vibration = 30;

	float directionByArrowKeys (bool up, bool down, bool left, bool right) {
		if(!up && !down && !left && right) {
			return 0.0f;
		} else if(!up && down && !left && right) {
			return yakblt::deg2rad(45.0f);
		} else if(!up && down && !left && !right) {
			return yakblt::deg2rad(90.0f);
		} else if(!up && down && left && !right) {
			return yakblt::deg2rad(135.0f);
		} else if(!up && !down && left && !right) {
			return yakblt::deg2rad(180.0f);
		} else if(up && !down && left && !right) {
			return yakblt::deg2rad(225.0f);
		} else if(up && !down && !left && !right) {
			return yakblt::deg2rad(270.0f);
		} else if(up && !down && !left && right) {
			return yakblt::deg2rad(315.0f);
		} else {
			return numeric_limits<float>::quiet_NaN();
		}
	}
}

namespace yakblt {
	/* class Player */

	Player::Player (Collidable &collidable) :
			Unit(collidable)
	{
	}

	Player::~Player () {
	}

	bool Player::isHostileTo (Bullet &bullet) {
		return bullet.getOwnerType() == OwnerType::ENEMY;
	}

	void Player::restrainActionArea () {
		if( isDead() ) return;
		FloatRect worldBounds = getGrid()->getBounds();
		worldBounds = scaleRect(worldBounds, 0.975f);
		Vector2f pos = localTo(getGrid(), {});
		pos.x = max(pos.x, worldBounds.left);
		pos.x = min(pos.x, worldBounds.left + worldBounds.width);
		pos.y = max(pos.y, worldBounds.top);
		pos.y = min(pos.y, worldBounds.top + worldBounds.height);
		setPosition( getGrid()->localTo(getParent(), pos) );
		updateTransforms(); // to update immediately
	}

	/* class DefaultPlayer */

	DefaultPlayer::DefaultPlayer () :
			Player( *new CircleCollidable(Circle(0, 0, 5)) ),
			_sprite( app().assets().loadTexture(AIRPLANE) )
	{
		Vector2f origin = getContentSize();
		origin.x *= 0.58f;
		origin.y *= 0.5f;
		_sprite.setOrigin(origin);
		_sprite.setScale(0.5f, 0.5f);
	}

	Vector2f DefaultPlayer::getContentSize () const {
		FloatRect bounds = _sprite.getGlobalBounds();
		return Vector2f(bounds.width, bounds.height);
	}

	void DefaultPlayer::setContentSize (const Vector2f &size) {
		FloatRect bounds = _sprite.getLocalBounds();
		if (bounds.width == 0 || bounds.height == 0) return;
		float sx = size.x / bounds.width;
		float sy = size.y / bounds.height;
		_sprite.setScale(sx, sy);
	}

	void DefaultPlayer::shot () {
		_shotCount = shotInterval;
		Vector2f pos = getPosition();
		float rot = getRotation();

		Bullet *bullet = app().bulletFac().get("player-bullet");
		ASSERT(bullet != nullptr)
		bullet->setPosition( pos + yakblt::rotate(Vector2f(0, -7), rot*DEG_TO_RAD) );
		bullet->setRotation(rot);
		app().world().addBullet(*bullet);

		bullet = app().bulletFac().get("player-bullet");
		ASSERT(bullet != nullptr)
		bullet->setPosition( pos + yakblt::rotate(Vector2f(0, 7), rot*DEG_TO_RAD) );
		bullet->setRotation(rot);
		app().world().addBullet(*bullet);
	}

	void DefaultPlayer::onDraw (RenderTarget &target) {
		RenderStates states = RenderStates( getGlobalTransform() );
		target.draw(_sprite, states);
	}

	void DefaultPlayer::control () {
		if( isDead() ) return;

		/* movement */
		float moveDir = directionByArrowKeys(
				Keyboard::isKeyPressed(Keyboard::W),
				Keyboard::isKeyPressed(Keyboard::S),
				Keyboard::isKeyPressed(Keyboard::A),
				Keyboard::isKeyPressed(Keyboard::D) );
		if ( !isnan(moveDir) ) {
			_moveDelta += angleVector(moveDir) * accel;
			_moveDelta = limitLength(_moveDelta, maxSpeed);
		} else {
			_moveDelta *= friction;
		}
		move(_moveDelta);

		/* rotation */
		float curRot = getRotation() * DEG_TO_RAD;
		Vector2f mouse = Vector2f( Mouse::getPosition(window()) );
		float targetRot = angleTo(localToGlobal(Vector2f()), mouse);
		rotate(shortestArc(curRot, targetRot) * rotMul * RAD_TO_DEG);
		updateTransforms(); // for restrainActionArea()

		/* shot */
		if (_shotCount > 0) {
			_shotCount--;
		} else {
			if (Mouse::isButtonPressed(Mouse::Button::Left)) {
				shot();
			}
		}
	}

	void DefaultPlayer::dead () {
		Effect *effect = new PlayerExplosion();
		effect->setPosition( getPosition() );
		app().world().addEffect(*effect);
		app().world().vibrate(vibration);
		Sound *sound = new Sound( app().assets().loadSoundBuffer(DEATH_SOUND) );
		app().sounds().addSound(*sound);
	}
}
