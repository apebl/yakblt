#ifndef __BLT_SPRITENODE_H__
#define __BLT_SPRITENODE_H__

#include "node.hpp"

namespace yakblt {
	/**
	 * @note SpriteNodes hold the ownership of the sprite.
	 * @note SpriteNodes don't hold the ownership of the texture.
	 */
	class SpriteNode : public Node {
	public:
		SpriteNode ();
		SpriteNode (Sprite &sprite);
		SpriteNode (const Texture &texture);
		SpriteNode (const Texture &texture, const IntRect &rect);
		virtual ~SpriteNode () override;
		Sprite &getSprite () const;
		virtual Vector2f getContentSize () const override;
		virtual void setContentSize (const Vector2f &size) override;
	protected:
		virtual void onDraw (RenderTarget &target) override;
	private:
		Sprite *_sprite;
	};
}

#endif
