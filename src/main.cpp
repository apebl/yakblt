#include "config.hpp"
#include "assets.hpp"
#include "globals.hpp"
#include "app.hpp"
#include <TGUI/TGUI.hpp>
#include "startscene.hpp"

using namespace std;
using namespace sf;

namespace {
	tgui::Theme _theme;

	constexpr float getScaleToFit (const Vector2f &windowSize, const Vector2f &worldSize) {
		float windowRatio = windowSize.y / windowSize.x;
		float worldRatio = worldSize.y / worldSize.x;
		return windowRatio > worldRatio ? windowSize.x / worldSize.x : windowSize.y / worldSize.y;
	}

	void resize (RenderWindow &window, unsigned int width, unsigned int height) {
		window.setView( View(FloatRect(0, 0, width, height)) );

		blt::App &app = blt::app();
		Vector2f size = Vector2f(width, height);
		app.background().setContentSize(size);

		Vector2f worldSize = Vector2f(WORLD_WIDTH, WORLD_HEIGHT);
		float scale = getScaleToFit(size, worldSize);
		worldSize *= scale;
		Vector2f pos = Vector2f((width - worldSize.x) / 2, (height - worldSize.y) / 2);
		app.root().setPosition(pos);
		app.root().setScale(scale, scale);
	}

	void initWindow () {
		VideoMode mode(WINDOW_WIDTH, WINDOW_HEIGHT);
		RenderWindow *window = new RenderWindow(mode, TITLE);
		window->setVerticalSyncEnabled(VSYNC);
		window->setFramerateLimit(FRAMERATE);
		blt::setWindow(*window);
	}

	void initApp () {
		blt::App *app = new blt::App( blt::window() );
		blt::setApp(*app);
		const Vector2f &view = app->window().getView().getSize();
		resize(app->window(), view.x, view.y);
	}

	void initGuiTheme () {
		_theme = tgui::Theme(GUI_THEME);
		tgui::Theme::setDefault(&_theme);
	}

	void initScene () {
		initGuiTheme();
		blt::StartScene *scene = new blt::StartScene();
		blt::app().replaceScene(scene);
	}

	void handleEvent (RenderWindow &window, Event &event) {
		switch (event.type) {
		case Event::Closed:
			window.close();
			break;
		case Event::Resized:
			resize(window, event.size.width, event.size.height);
			break;
		default:
			break;
		}
		blt::app().onSfmlEvent().fireEvent(event);
	}

	void render (RenderWindow &window) {
		window.clear();
		blt::app().render(window);
		window.display();
	}

	void loop () {
		RenderWindow &window = blt::window();
		while ( window.isOpen() ) {
			Event event;
			while ( window.pollEvent(event) ) {
				handleEvent(window, event);
			}
			render(window);
		}
	}

	void dispose () {
		blt::App *app = &blt::app();
		delete app;
		RenderWindow *window = &blt::window();
		delete window;
	}
}

int main () {
	initWindow();
	initApp();
	initScene();
	loop();
	dispose();
	return 0;
}