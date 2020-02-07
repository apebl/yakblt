#ifndef __BLT_RESULTSCENE_H__
#define __BLT_RESULTSCENE_H__

#include "scene.hpp"
#include <TGUI/TGUI.hpp>

namespace yakblt {
	class ResultScene : public Scene {
	public:
		ResultScene ();
		virtual ~ResultScene () override;
		tgui::Gui &gui ();
		virtual void show (Scene *oldScene) override;
		virtual void hide (Scene *newScene) override;
		virtual void update (float delta) override;
		virtual void draw (RenderTarget &target) override;
	private:
		void showRanking ();
		tgui::Gui _gui;
	};
}

#endif
