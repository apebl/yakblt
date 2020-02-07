#include "mineexplosion.hpp"
#include "../config.hpp"
#include "../globals.hpp"
#include "../app.hpp"
#include "../assets.hpp"

namespace {
	const int lifespan = FRAMERATE / 2;
}

namespace yakblt {
	MineExplosion::MineExplosion () :
		Effect(lifespan),
		_anim( app().assets().loadTexture(MINE_EXPLOSION), Vector2u(53, 53) )
	{
		_anim.setInterval( lifespan / _anim.numFrames() );
		FloatRect bounds = _anim.getGlobalBounds();
		Vector2f origin = Vector2f(bounds.width * 0.5f, bounds.height * 0.5f);
		_anim.setOrigin(origin);
		_anim.setScale(1.5f, 1.5f);
	}

	void MineExplosion::onUpdate (float delta) {
		if ( isDead() ) return;
		Effect::onUpdate(delta);
		_anim.update();
	}

	void MineExplosion::onDraw (RenderTarget &target) {
		RenderStates states = RenderStates( getGlobalTransform() );
		target.draw(_anim, states);
	}
}
