/* node.hpp
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

#ifndef __YAKBLT_NODE_H__
#define __YAKBLT_NODE_H__

#include <vector>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

namespace yakblt {
	/**
	 * @note Nodes hold the ownership of the children.
	 */
	class Node : public Transformable {
	public:
		Node ();
		virtual ~Node () override;

		void updateTransforms ();
		virtual void updateSelfTransforms ();
		/**
		 * Updates this node.
		 *
		 * This method will be called every frame.
		 *
		 * @param delta The elapsed time, in seconds.
		 */
		virtual void update (float delta);
		virtual void draw (RenderTarget &target);
		virtual void drawDebug (RenderTarget &target);

		Node *getParent () const;
		Node *getRoot ();
		const vector<Node*> &getChildren () const;
		Node &getChildAt (size_t idx) const;
		size_t numChildren () const;
		bool hasChild (const Node &node);
		void addChild (Node &node);
		/**
		 * @return true if removed, false otherwise.
		 */
		bool removeChild (Node &node);
		/**
		 * @return The removed child, or null if no one removed.
		 */
		Node *removeChildAt (size_t idx);
		void removeAllChildren ();
		void removeFromParent ();

		size_t getChildIndex (const Node &node) const;
		void setChildIndex (Node &node, size_t index);
		void swapChildren (Node &a, Node &b);

		/**
		 * @note You should call Node::update(float) before this method.
		 */
		const Transform &getGlobalTransform () const;
		/**
		 * Gets the untransformed size of the node, excluding
		 * its children.
		 *
		 * @return The size
		 */
		virtual Vector2f getContentSize () const;
		virtual void setContentSize (const Vector2f &size);
		Vector2f getSize () const;

		/**
		 * @note You should call Node::update(float) before this method.
		 */
		Vector2f localToGlobal (const Vector2f &vec) const;
		/**
		 * @note You should call Node::update(float) before this method.
		 */
		Vector2f globalToLocal (const Vector2f &vec) const;
		/**
		 * @note You should call Node::update(float) before this method.
		 *
		 * @param[in] target The target coordinates, or null if global
		 * coordinates.
		 * @param vec A vector to be converted
		 */
		Vector2f localTo (const Node *target, const Vector2f &vec) const;
		Vector2f globalToParent (const Vector2f &vec) const;

	protected:
		virtual void onUpdate (float delta);
		virtual void onDraw (RenderTarget &target);
		virtual void onDrawDebug (RenderTarget &target);

	private:
		Node *_parent;
		vector<Node*> _children;
		Transform _globalTransform;
	};
}

#endif
