/* maingui.cpp
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

#include "maingui.hpp"
#include "globals.hpp"
#include "app.hpp"
#include "assets.hpp"
#include "scores.hpp"
#include "config.hpp"
#include "resultscene.hpp"
#include <sstream>

using namespace yakblt;

namespace {
	const int duration = FRAMERATE * 2;

	string genText () {
		stringstream ss;
		ss << "Score: " << Scores::get();
		return ss.str();
	}
}

namespace yakblt {
	MainGUI::MainGUI (World &world) :
			_world(&world), _sceneChanging(false), _time(0)
	{
		const Font &font = app().assets().loadFont(FONT);
		_text = new TextNode(genText(), font, 24);
		_text->setPosition(15, 10);
		addChild(*_text);
	}

	World &MainGUI::world () {
		return *_world;
	}

	void MainGUI::startSceneChange () {
		_sceneChanging = true;
		_time = duration;
		app().sounds().fadeOut(0.97f);
	}

	void MainGUI::onUpdate (float delta) {
		_text->getText().setString( genText() );
		if (_sceneChanging) {
			_time--;
			if (_time < 0) {
				Scene *old = app().scene();
				app().replaceScene( new ResultScene() );
				app().addToDelete(*old);
			}
		}
	}

	void MainGUI::onDraw (RenderTarget &target) {
		if (_sceneChanging) {
			ShapeRenderer renderer {};
			renderer.setRenderTarget(target);
			renderer.setTransform( getGlobalTransform() );
			float t = 1.0f - (float)_time / duration;
			renderer.setColor( Color(0, 0, 0, (int)(255*t)) );
			renderer.draw(WORLD_RECT);
		}
	}
}
