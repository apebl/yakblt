/* textnode.cpp
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

#include "textnode.hpp"

namespace yakblt {
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
