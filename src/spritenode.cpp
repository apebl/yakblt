#include "spritenode.hpp"

namespace yakblt {
	SpriteNode::SpriteNode () {
		_sprite = new Sprite();
	}

	SpriteNode::SpriteNode (Sprite &sprite) {
		_sprite = &sprite;
	}

	SpriteNode::SpriteNode (const Texture &texture) {
		_sprite = new Sprite(texture);
	}

	SpriteNode::SpriteNode (const Texture &texture, const IntRect &rect) {
		_sprite = new Sprite(texture, rect);
	}

	SpriteNode::~SpriteNode () {
		delete _sprite;
	}

	Sprite &SpriteNode::getSprite () const {
		return *_sprite;
	}

	Vector2f SpriteNode::getContentSize () const {
		FloatRect bounds = _sprite->getGlobalBounds();
		return Vector2f(bounds.width, bounds.height);
	}

	void SpriteNode::setContentSize (const Vector2f &size) {
		FloatRect bounds = _sprite->getLocalBounds();
		if (bounds.width == 0 || bounds.height == 0) return;
		float sx = size.x / bounds.width;
		float sy = size.y / bounds.height;
		_sprite->setScale(sx, sy);
	}

	void SpriteNode::onDraw (RenderTarget &target) {
		RenderStates states = RenderStates( getGlobalTransform() );
		target.draw(*_sprite, states);
	}
}
