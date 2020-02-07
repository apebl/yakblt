#ifndef __BLT_SOUNDMANAGER_H__
#define __BLT_SOUNDMANAGER_H__

#include <vector>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

namespace yakblt {
	/*
	 * @note SoundManagers hold the ownership of the sounds.
	 */
	class SoundManager {
	public:
		SoundManager ();
		virtual ~SoundManager ();
		const vector<Sound*> &getSounds () const;
		const vector<Music*> &getMusics () const;
		void addSound (Sound &sound);
		void addMusic (Music &music);
		bool isPaused () const;
		void play ();
		void pause ();
		void clear ();
		void setVolume (float volume);
		void mulVolume (float mul);
		void fadeOut (float attenuation);
		void update ();
	private:
		vector<Sound*> _sounds;
		vector<Music*> _musics;
		bool _paused;
		float _fade; // 1 => no fading
	};
}

#endif
