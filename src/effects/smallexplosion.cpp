#include "smallexplosion.hpp"
#include "../config.hpp"
#include "../globals.hpp"
#include "../app.hpp"
#include "../assets.hpp"

namespace {
	const int lifespan = 64;
}

namespace yakblt {
	SmallExplosion::SmallExplosion () :
		Effect(lifespan),
		_anim( app().assets().loadTexture(EXPLOSION), Vector2u(128, 128) )
	{
		FloatRect bounds = _anim.getGlobalBounds();
		Vector2f origin = Vector2f(bounds.width * 0.5f, bounds.height * 0.5f);
		_anim.setOrigin(origin);
	}

	void SmallExplosion::onUpdate (float delta) {
		if ( isDead() ) return;
		Effect::onUpdate(delta);
		_anim.update();
	}

	void SmallExplosion::onDraw (RenderTarget &target) {
		RenderStates states = RenderStates( getGlobalTransform() );
		target.draw(_anim, states);
	}
}
