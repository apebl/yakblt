#ifndef __BLT_STARTSCENE_H__
#define __BLT_STARTSCENE_H__

#include "scene.hpp"
#include <TGUI/TGUI.hpp>

namespace blt {
	class StartScene : public Scene {
	public:
		StartScene ();
		virtual ~StartScene () override;
		tgui::Gui &gui ();
		virtual void show (Scene *oldScene) override;
		virtual void hide (Scene *newScene) override;
		virtual void update (float delta) override;
		virtual void draw (RenderTarget &target) override;
	private:
		tgui::Gui _gui;
	};
}

#endif