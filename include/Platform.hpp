#include <SDL.h>

#include "GraphicsWrapper.hpp"

#ifndef PLATFORM_HPP
#define PLATFORM_HPP

class Platform {
	private:
		SDL_Rect box;

	public:
		int x, y, w, h;

		Platform(int newX, int newY, int newW, int newH);
		~Platform();
		void render(GraphicsWrapper* graphicsWrapper);
};

#endif
