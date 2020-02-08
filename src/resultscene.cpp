/* resultscene.cpp
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

#include "resultscene.hpp"
#include "globals.hpp"
#include "app.hpp"
#include "scores.hpp"
#include "assets.hpp"
#include "mainscene.hpp"
#include "strutils.hpp"
#include <sstream>

using namespace yakblt;

namespace yakblt {
	ResultScene::ResultScene () : _gui( window() )
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

	ResultScene::~ResultScene () {
	}

	tgui::Gui &ResultScene::gui () {
		return _gui;
	}

	void ResultScene::show (Scene *oldScene) {
		string labelStr = string("Your score: ") + to_string(Scores::getCaptured());
		auto label = tgui::Label::create(labelStr);
		label->setSize({"90%", "20%"});
		label->setPosition({"5%", "10%"});
		label->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);
		label->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
		label->setTextSize(64);
		_gui.add(label);

		auto editBox = tgui::EditBox::create();
		editBox->setSize({"50%", "12.5%"});
		editBox->setPosition({"25%", "35%"});
		editBox->setDefaultText("Enter your name");
		editBox->setAlignment(tgui::EditBox::Alignment::Center);
		editBox->setTextSize(0);
		_gui.add(editBox);

		auto button = tgui::Button::create("OK");
		button->setSize({"25%", "15%"});
		button->setPosition({"37.5%", "55%"});
		button->setTextSize(0);
		_gui.add(button);
		button->connect("pressed", [this, editBox] {
			string text = editBox->getText().toAnsiString();
			trim(text);
			if ( !text.empty() ) {
				Scores::saveScore(text, Scores::getCaptured());
				showRanking();
			}
		});

		Sound *sound = new Sound( app().assets().loadSoundBuffer(RESULT_SOUND) );
		app().sounds().clear();
		app().sounds().addSound(*sound);
	}

	void ResultScene::hide (Scene *newScene) {
		_gui.removeAllWidgets();
	}

	void ResultScene::update (float delta) {
	}

	void ResultScene::draw (RenderTarget &target) {
		_gui.draw();
	}

	void ResultScene::showRanking () {
		_gui.removeAllWidgets();

		auto label = tgui::Label::create("Ranking");
		label->setSize({"90%", "15%"});
		label->setPosition({"5%", "5%"});
		label->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);
		label->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
		label->setTextSize(64);
		_gui.add(label);

		auto list = tgui::ListBox::create();
		list->setSize({"66.666%", "50%"});
		list->setPosition({"16.666%", "20%"});
		list->setItemHeight(48);
		list->setTextSize(0);
		_gui.add(list);

		vector<tuple<string, long>> scores = Scores::loadScores();
		for (auto &item : scores) {
			stringstream ss;
			ss << get<0>(item) << " - " << get<1>(item);
			list->addItem( ss.str() );
		}

		auto button = tgui::Button::create("Restart");
		button->setSize({"20%", "10%"});
		button->setPosition({"40%", "75%"});
		button->setTextSize(0);
		_gui.add(button);
		button->connect("pressed", [this] {
			app().replaceScene( new MainScene() );
			app().addToDelete(*this);
		});
	}
}
