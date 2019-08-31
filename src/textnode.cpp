#include "textnode.hpp"

namespace blt {
	TextNode::TextNode (Text &text) {
		_text = &text;
	}

	TextNode::TextNode (const String &string, const Font &font, unsigned int characterSize) {
		_text = new Text(string, font, characterSize);
	}

	TextNode::~TextNode () {
		delete _text;
	}

	Text &TextNode::getText () const {
		return *_text;
	}

	Vector2f TextNode::getContentSize () const {
		FloatRect bounds = _text->getGlobalBounds();
		return Vector2f(bounds.width, bounds.height);
	}

	void TextNode::setContentSize (const Vector2f &size) {
		FloatRect bounds = _text->getLocalBounds();
		if (bounds.width == 0 || bounds.height == 0) return;
		float sx = size.x / bounds.width;
		float sy = size.y / bounds.height;
		_text->setScale(sx, sy);
	}

	void TextNode::onDraw (RenderTarget &target) {
		RenderStates states = RenderStates( getGlobalTransform() );
		target.draw(*_text, states);
	}
}