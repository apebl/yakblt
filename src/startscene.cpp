/* startscene.cpp
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

#include "startscene.hpp"
#include "config.hpp"
#include "globals.hpp"
#include "app.hpp"
#include "assets.hpp"
#include "mainscene.hpp"

using namespace yakblt;

namespace yakblt {
	StartScene::StartScene () : _gui( window() )
	{
		const Font &font = app().assets().loadFont(FONT);
		tgui::Font guiFont = tgui::Font(font);
		_gui.setFont(guiFont);

		onSfmlEvent().addHandler([this](sf::Event event) {
			if (event.type == sf::Event::Resized) {
				_gui.setView( window().getView() );
			}
			_gui.handleEvent(event);
		});
	}

	StartScene::~StartScene () {
	}

	tgui::Gui &StartScene::gui () {
		return _gui;
	}

	void StartScene::show (Scene *oldScene) {
		auto label = tgui::Label::create(TITLE);
		label->setSize({"75%", "20%"});
		label->setPosition({"12.5%", "22.5%"});
		label->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);
		label->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
		label->setTextSize(64);
		// label->getRenderer()->setTextStyle(Text::Bold);
		_gui.add(label);

		auto button = tgui::Button::create("Start");
		button->setSize({"30%", "15%"});
		button->setPosition({"35%", "52.5%"});
		button->setTextSize(0);
		_gui.add(button);
		button->connect("pressed", [this] {
			app().replaceScene( new MainScene() );
			app().addToDelete(*this);
		});

		Sound *sound = new Sound( app().assets().loadSoundBuffer(INTRO_SOUND) );
		app().sounds().addSound(*sound);
	}

	void StartScene::hide (Scene *newScene) {
		_gui.removeAllWidgets();
	}

	void StartScene::update (float delta) {
	}

	void StartScene::draw (RenderTarget &target) {
		_gui.draw();
	}
}
