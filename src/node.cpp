#include "node.hpp"
#include <algorithm>
#include <memory>
#include "utils.hpp"

namespace blt {
	/* class Node */

	Node::Node () : Transformable(),
			_parent(nullptr),
			_children(),
			_globalTransform()
	{
	}

	Node::~Node () {
		for (auto child : _children) {
			delete child;
		}
	}

	void Node::updateTransforms () {
		updateSelfTransforms();
		for (auto child : _children) {
			child->updateTransforms();
		}
	}

	void Node::updateSelfTransforms() {
		if (_parent == nullptr) {
			_globalTransform = getTransform();
		} else {
			_globalTransform = _parent->getGlobalTransform() * getTransform();
		}
	}

	void Node::update (float delta) {
		vector<Node*> copy = _children;
		for (auto child : copy) {
			child->update(delta);
		}
		onUpdate(delta);
	}

	void Node::draw (RenderTarget &target) {
		for (auto child : _children) {
			child->draw(target);
		}
		onDraw(target);
	}

	void Node::drawDebug (RenderTarget &target) {
		for (auto child : _children) {
			child->drawDebug(target);
		}
		onDrawDebug(target);
	}

	Node *Node::getParent () const {
		return _parent;
	}

	Node *Node::getRoot () {
		Node *node = this;
		Node *prt = node->getParent();
		while (prt != nullptr) {
			node = prt;
			prt = node->getParent();
		}
		return node;
	}

	const vector<Node*> &Node::getChildren () const {
		return _children;
	}

	Node &Node::getChildAt (size_t idx) const {
		ASSERT(_children.size() > idx)
		return *_children.at(idx);
	}

	size_t Node::numChildren () const {
		return _children.size();
	}

	bool Node::hasChild (const Node &node) {
		vector<Node*>::iterator iter = find(_children.begin(), _children.end(), &node);
		return iter != _children.end();
	}

	void Node::addChild (Node &node) {
		ASSERT( node.getParent() == nullptr )
		ASSERT( find(_children.begin(), _children.end(), &node) == _children.end() )
		_children.push_back(&node);
		node._parent = this;
	}

	bool Node::removeChild (Node &node) {
		vector<Node*>::iterator iter = find(_children.begin(), _children.end(), &node);
		if (iter != _children.end()) {
			(*iter)->_parent = nullptr;
			_children.erase(iter);
			return true;
		}
		return false;
	}

	Node *Node::removeChildAt (size_t idx) {
		if (idx >= _children.size()) {
			vector<Node*>::iterator iter = _children.begin() + idx;
			(*iter)->_parent = nullptr;
			_children.erase(iter);
			return (*iter);
		}
		return nullptr;
	}

	void Node::removeAllChildren () {
		for (auto child : _children) {
			child->_parent = nullptr;
		}
		_children.clear();
	}

	void Node::removeFromParent () {
		_parent->removeChild(*this);
	}

	size_t Node::getChildIndex (const Node &node) const {
		ASSERT(node.getParent() == this)
		return distance(_children.begin(), find(_children.begin(), _children.end(), &node));
	}

	void Node::setChildIndex (Node &node, size_t index) {
		ASSERT(node.getParent() == this)
		ASSERT(0 <= index && index < numChildren())
		_children.erase( find(_children.begin(), _children.end(), &node) );
		_children.insert(_children.begin() + index, &node);
	}

	void Node::swapChildren (Node &a, Node &b) {
		int idx = getChildIndex(a);
		int idx2 = getChildIndex(b);
		_children[idx] = &b;
		_children[idx2] = &a;
	}

	const Transform &Node::getGlobalTransform () const {
		return _globalTransform;
	}

	Vector2f Node::getContentSize () const {
		return Vector2f();
	}

	void Node::setContentSize (const Vector2f &size) {
	}

	Vector2f Node::getSize () const {
		Vector2f content = getContentSize();
		content.x *= getScale().x;
		content.y *= getScale().y;
		return content;
	}

	Vector2f Node::localToGlobal (const Vector2f &vec) const {
		return _globalTransform.transformPoint(vec);
	}

	Vector2f Node::globalToLocal (const Vector2f &vec) const {
		return _globalTransform.getInverse().transformPoint(vec);
	}

	Vector2f Node::localTo (const Node *target, const Vector2f &vec) const {
		if (target == nullptr) {
			return localToGlobal(vec);
		} else if (this == target) {
			return vec;
		} else {
			// TODO optimize
			return target->globalToLocal( localToGlobal(vec) );
		}
	}

	Vector2f Node::globalToParent (const Vector2f &vec) const {
		if (getParent() == nullptr) {
			return vec;
		} else {
			return getParent()->globalToLocal(vec);
		}
	}

	void Node::onUpdate (float delta) {
	}

	void Node::onDraw (RenderTarget &target) {
	}

	void Node::onDrawDebug (RenderTarget &target) {
	}
}
