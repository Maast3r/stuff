#include <SDL_mixer.h>

#ifndef SOUNDWRAPPER_HPP
#define SOUNDWRAPPER_HPP

class SoundWrapper {
	public:
		Mix_Music *music;
		Mix_Chunk *bombSoundEffect;

		SoundWrapper();
		~SoundWrapper();
};

#endif
