#include "globals.hpp"

namespace {
	sf::RenderWindow *_window;
	blt::App *_app;
}

namespace blt {
	RenderWindow &window () {
		return *_window;
	}

	void setWindow (RenderWindow &window) {
		_window = &window;
	}

	App &app () {
		return *_app;
	}

	void setApp (App &app) {
		_app = &app;
	}
}