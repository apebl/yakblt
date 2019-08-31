#ifndef __BLT_MAINGUI_H__
#define __BLT_MAINGUI_H__

#include "node.hpp"
#include "world.hpp"
#include "textnode.hpp"

namespace blt {
	class MainGUI : public Node {
	public:
		MainGUI (World &world);
		World &world ();
		void startSceneChange ();
	protected:
		virtual void onUpdate (float delta);
		virtual void onDraw (RenderTarget &target);
	private:
		World *_world;
		TextNode *_text;
		bool _sceneChanging;
		int _time;
	};
}

#endif