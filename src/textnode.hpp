#ifndef __BLT_TEXTNODE_H__
#define __BLT_TEXTNODE_H__

#include "node.hpp"

namespace yakblt {
	/**
	 * @note TextNodes hold the ownership of the text.
	 * @note TextNodes don't hold the ownership of the font.
	 */
	class TextNode : public Node {
	public:
		TextNode (Text &text);
		TextNode (const String &string, const Font &font, unsigned int characterSize);
		virtual ~TextNode () override;
		Text &getText () const;
		virtual Vector2f getContentSize () const override;
		virtual void setContentSize (const Vector2f &size) override;
	protected:
		virtual void onDraw (RenderTarget &target) override;
	private:
		Text *_text;
	};
}

#endif
