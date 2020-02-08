/* spritenode.cpp
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
