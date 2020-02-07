#include "mainscene.hpp"
#include "config.hpp"
#include "globals.hpp"
#include "app.hpp"
#include "assets.hpp"
#include "scores.hpp"
#include "player.hpp"
#include "scripts/mainscripter.hpp"

namespace yakblt {
	MainScene::MainScene () : _scheduler(FRAMERATE / 10) {
		_scheduler.onRun().addHandler([] {
			Scores::add(1);
		});
	}

	MainScene::~MainScene () {
	}

	void MainScene::show (Scene *oldScene) {
		InGameScene::show(oldScene);
		Scores::reset();
		_scheduler.reset();

		// Set the background
		const Texture &tex = app().assets().loadTexture(BACKGROUND);
		_background = new SpriteNode(tex);
		_background->setContentSize( Vector2f(WORLD_WIDTH, WORLD_HEIGHT) );
		world().back().addChild(*_background);

		// Add a player
		Player *player = new DefaultPlayer();
		player->setPosition(WORLD_CENTER);
		world().addPlayer(*player);

		// Add scripts
		_gui = new MainGUI(world());
		world().gui().addChild(*_gui);
		world().addScripter( *new MainScripter() );
		registerEvents();

		// Set the background music
		Music *music = new Music();
		music->openFromFile(GAME_MUSIC);
		music->setLoop(true);
		app().sounds().clear();
		app().sounds().addMusic(*music);
	}

	void MainScene::hide (Scene *newScene) {
		InGameScene::hide(newScene);
	}

	void MainScene::update (float delta) {
		InGameScene::update(delta);
		_scheduler.update();
	}

	void MainScene::registerEvents () {
		Player *player = world().getPlayer();
		ASSERT(player != nullptr)
		player->onDead().addHandler([this](Unit &unit) {
			Scores::capture();
			_gui->startSceneChange();
		});
	}
}
