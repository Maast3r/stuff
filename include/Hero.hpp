#include <SDL.h>

#include "GraphicsWrapper.hpp"
#include "SoundWrapper.hpp"
#include "KeyboardHandler.hpp"
#include "Platform.hpp"

#ifndef HERO_HPP
#define HERO_HPP

class Hero {
	private:
		SDL_Rect box;
		int x, y, w, h;
		static const int walkingAnimationFrames = 4;
		SDL_Rect spriteClips[walkingAnimationFrames];
		SDL_Texture* spriteSheetTexture;
		bool facingRight;
		bool isOnFloor;
		KeyboardHandler keyboardHandler;

		enum GravityDirection { UP, DOWN, LEFT,	RIGHT };
		Hero::GravityDirection gravity;

	public:
		Hero();
		~Hero();
		void handleEvents(SDL_Event* event, SoundWrapper* soundWrapper);
		void update(GraphicsWrapper* graphicsWrapper, Platform** platforms);
		void render(GraphicsWrapper* graphicsWrapper);
		void initTexture(GraphicsWrapper* graphicsWrapper);
		void handleCollisions(Platform* platform);
};

#endif
