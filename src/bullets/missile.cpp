#include "missile.hpp"
#include "../globals.hpp"
#include "../app.hpp"
#include "../assets.hpp"
#include "../config.hpp"
#include "../scores.hpp"
#include "../effects/smallexplosion.hpp"

namespace {
	const float maxSpeed = 3;
	const float accel = 0.2f;
	const float rotMul = 0.02f;
	const float health = 1.5f;
	const long score = 5;
	const float vibration = 5;
}

namespace yakblt {
	Missile::Missile () :
			DestroyableBullet(*new CircleCollidable(Circle(0, 0, 4.5f)), ENEMY),
			_anim( app().assets().loadTexture(MISSILE), Vector2u(64, 25) ),
			_moveDelta()
	{
		setHealth(health);
		_anim.setInterval(FRAMERATE / 4);
		_anim.setLoop(true);
		FloatRect bounds = _anim.getGlobalBounds();
		Vector2f origin = Vector2f(bounds.width * 0.7f, bounds.height * 0.5f);
		_anim.setOrigin(origin);
		_anim.setScale(0.7f, 0.7f);
	}

	void Missile::onUpdate (float delta) {
		if ( isDead() ) return;
		Bullet::onUpdate(delta);
		_anim.update();
	}

	void Missile::control () {
		if( isDead() ) return;
		float curRot = getRotation() * DEG_TO_RAD;
		_moveDelta += angleVector(curRot) * accel;
		_moveDelta = limitLength(_moveDelta, maxSpeed);
		move(_moveDelta);

		Unit *player = app().world().getPlayer();
		if (player == nullptr) return;
		float targetRot = angleTo( getPosition(), player->getPosition() );
		rotate(shortestArc(curRot, targetRot) * rotMul * RAD_TO_DEG);
	}

	void Missile::restrainActionArea () {
		if( isDead() ) return;
		FloatRect bounds = getCollidable().getBounds( getGrid() );
		FloatRect area = getGrid()->getBounds();
		if ( !area.intersects(bounds) ) {
			kill();
		}
	}

	void Missile::dead () {
		Scores::add(score);
		Effect *effect = new SmallExplosion();
		effect->setPosition( getPosition() );
		app().world().addEffect(*effect);
		app().world().vibrate(vibration);
	}

	void Missile::onDraw (RenderTarget &target) {
		RenderStates states = RenderStates( getGlobalTransform() );
		target.draw(_anim, states);
	}
}
