#include "Platform.hpp"
#include "GraphicsWrapper.hpp"

Platform::Platform(int newX, int newY, int newW, int newH) {
	x = newX;
	y = newY;
	w = newW;
	h = newH;

	box.x = x;
	box.y = y;
	box.w = w;
	box.h = h;
}

Platform::~Platform() {

}

void Platform::render(GraphicsWrapper* graphicsWrapper) {
	SDL_SetRenderDrawColor(graphicsWrapper->renderer, 0x00, 0xAA, 0x00, 0xFF);
	SDL_RenderFillRect(graphicsWrapper->renderer, &box);
}
