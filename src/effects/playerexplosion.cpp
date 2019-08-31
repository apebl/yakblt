#include "playerexplosion.hpp"
#include "../config.hpp"
#include "../globals.hpp"
#include "../app.hpp"
#include "../assets.hpp"

namespace {
	const int lifespan = 64;
}

namespace blt {
	PlayerExplosion::PlayerExplosion () :
		Effect(lifespan),
		_anim( app().assets().loadTexture(PLAYER_EXPLOSION), Vector2u(128, 128) )
	{
		FloatRect bounds = _anim.getGlobalBounds();
		Vector2f origin = Vector2f(bounds.width * 0.5f, bounds.height * 0.5f);
		_anim.setOrigin(origin);
	}

	void PlayerExplosion::onUpdate (float delta) {
		if ( isDead() ) return;
		Effect::onUpdate(delta);
		_anim.update();
	}

	void PlayerExplosion::onDraw (RenderTarget &target) {
		RenderStates states = RenderStates( getGlobalTransform() );
		target.draw(_anim, states);
	}
}
