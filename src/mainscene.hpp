#ifndef __BLT_MAINSCENE_H__
#define __BLT_MAINSCENE_H__

#include "ingamescene.hpp"
#include "scheduler.hpp"
#include "maingui.hpp"

namespace blt {
	class MainScene : public InGameScene {
	public:
		MainScene ();
		virtual ~MainScene () override;
		virtual void show (Scene *oldScene) override;
		virtual void hide (Scene *newScene) override;
		virtual void update (float delta) override;
	private:
		void registerEvents ();
		SpriteNode *_background;
		MainGUI *_gui;
		Scheduler _scheduler;
	};
}

#endif