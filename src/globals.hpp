#ifndef __BLT_GLOBALS_H__
#define __BLT_GLOBALS_H__

#include <SFML/Graphics.hpp>

using namespace sf;

namespace blt {
	class App;

	RenderWindow &window ();
	void setWindow (RenderWindow &window);
	App &app ();
	void setApp (App &app);
}

#endif