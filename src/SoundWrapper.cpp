#include <SDL_mixer.h>

#include "SoundWrapper.hpp"

SoundWrapper::SoundWrapper() {
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
	}

	music = Mix_LoadMUS("./assets/sounds/beat.wav");
	bombSoundEffect = Mix_LoadWAV("./assets/sounds/scratch.wav");

	if (music == NULL) {
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
	}
	if(bombSoundEffect == NULL) {
		printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}
}

SoundWrapper::~SoundWrapper() {
	Mix_FreeMusic(music);
	Mix_FreeChunk(bombSoundEffect); 
	
	music = NULL;
	bombSoundEffect = NULL;
}
