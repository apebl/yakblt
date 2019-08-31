#include "soundmanager.hpp"
#include "utils.hpp"

namespace blt {
	SoundManager::SoundManager () :
		_sounds(), _musics(), _paused(false), _fade(1.0f)
	{
	}

	SoundManager::~SoundManager () {
		for (const auto item : _sounds) {
			item->stop();
			delete item;
		}
		for (const auto item : _musics) {
			item->stop();
			delete item;
		}
	}

	const vector<Sound*> &SoundManager::getSounds () const {
		return _sounds;
	}

	const vector<Music*> &SoundManager::getMusics () const {
		return _musics;
	}

	void SoundManager::addSound (Sound &sound) {
		_sounds.push_back(&sound);
		if (!_paused) sound.play();
		_fade = 1.0f;
	}

	void SoundManager::addMusic (Music &music) {
		_musics.push_back(&music);
		if (!_paused) music.play();
		_fade = 1.0f;
	}

	bool SoundManager::isPaused () const {
		return _paused;
	}

	void SoundManager::play () {
		_paused = false;
		for (const auto item : _sounds) {
			item->play();
		}
		for (const auto item : _musics) {
			item->play();
		}
		_fade = 1.0f;
	}

	void SoundManager::pause () {
		_paused = true;
		for (const auto item : _sounds) {
			item->pause();
		}
		for (const auto item : _musics) {
			item->pause();
		}
		_fade = 1.0f;
	}

	void SoundManager::clear () {
		for (const auto item : _sounds) {
			item->stop();
			delete item;
		}
		for (const auto item : _musics) {
			item->stop();
			delete item;
		}
		_sounds.clear();
		_musics.clear();
		_fade = 1.0f;
	}

	void SoundManager::setVolume (float volume) {
		for (const auto item : _sounds) {
			item->setVolume(volume);
		}
		for (const auto item : _musics) {
			item->setVolume(volume);
		}
	}

	void SoundManager::mulVolume (float mul) {
		for (const auto item : _sounds) {
			item->setVolume(item->getVolume() * mul);
		}
		for (const auto item : _musics) {
			item->setVolume(item->getVolume() * mul);
		}
	}

	void SoundManager::fadeOut (float attenuation) {
		ASSERT(0 <= attenuation && attenuation < 1.0f)
		_fade = attenuation;
	}

	void SoundManager::update () {
		auto iter = _sounds.begin();
		while ( iter != _sounds.end() ) {
			if ((*iter)->getStatus() == Sound::Status::Stopped) {
				delete *iter;
				iter = _sounds.erase(iter);
			} else {
				if (_fade != 1.0f) {
					float vol = (*iter)->getVolume() * _fade;
					if (vol <= 0.1f) (*iter)->stop();
					(*iter)->setVolume(vol);
				}
				iter++;
			}
		}
		auto iter2 = _musics.begin();
		while ( iter2 != _musics.end() ) {
			if ((*iter2)->getStatus() == Music::Status::Stopped) {
				delete *iter2;
				iter2 = _musics.erase(iter2);
			} else {
				if (_fade != 1.0f) {
					float vol = (*iter2)->getVolume() * _fade;
					if (vol <= 0.1f) (*iter2)->stop();
					(*iter2)->setVolume(vol);
				}
				iter2++;
			}
		}
		if (_sounds.empty() && _musics.empty()) {
			_fade = 1.0f;
		}
	}
}