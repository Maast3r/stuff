#include <iostream>
#include <string>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "Tile.hpp"
#include "GraphicsWrapper.hpp"
#include "SoundWrapper.hpp"

Tile::Tile(int x, int y, int w, int h) {
	box.x = x;
	box.y = y;
	box.w = w;
	box.h = h;
	value = 0;
	showValue = false;
	visited = false;
	texture = NULL;  
}

Tile::~Tile() {
	SDL_DestroyTexture(texture);
	texture = NULL;
}

void Tile::handleEvents(SDL_Event* event, SoundWrapper* soundWrapper) {
	int mouseX = 0, mouseY = 0;
	
	if (event->type == SDL_MOUSEBUTTONDOWN) {
		if (event->button.button == SDL_BUTTON_LEFT) {
			mouseX = event->button.x;
			mouseY = event->button.y;
		
			if ((box.x < mouseX) && (mouseX < box.x + box.w) && (box.y < mouseY) && (mouseY < box.y + box.h)) {
				showValue = true;
				
				if (value == -1) {
					Mix_PlayChannel(-1, soundWrapper->bombSoundEffect, 0);
				}
			}
		}
	}
}

void Tile::update(GraphicsWrapper* graphicsWrapper) {
	SDL_Surface* surface = NULL;
	SDL_Color color;
	std::string str;

	if (value > -1 && showValue) {
		if (value == 0) {
			color.r = 50;
			color.g = 50;
			color.b = 50;
		} else if (value == 1) {
			color.r = 0;
			color.g = 0;
			color.b = 255;
		} else if (value == 2) {
			color.r = 0;
			color.g = 255;
			color.b = 0;
		} else if (value == 3) {
			color.r = 255;
			color.g = 0;
			color.b = 0;
		} else if (value == 4) {
			color.r = 255;
			color.g = 0;
			color.b = 255;
		} else if (value == 5) {
			color.r = 128;
			color.g = 0;
			color.b = 0;
		} else if (value == 6) {
			color.r = 175;
			color.g = 238;
			color.b = 238;
		} else if (value == 7) {
			color.r = 0;
			color.g = 0;
			color.b = 0;
		} else if (value == 8) {
			color.r = 105;
			color.g = 105;
			color.b = 105;
		}

		str = std::to_string(value);
		surface = TTF_RenderText_Solid(graphicsWrapper->font, str.c_str(), color);
		texture = SDL_CreateTextureFromSurface(graphicsWrapper->renderer, surface);
	} else if (value == -1 && showValue) {
		str = "BOMB";
		color.r = 0;
		color.g = 0;
		color.b = 0;
		surface = TTF_RenderText_Solid(graphicsWrapper->font, str.c_str(), color);
		texture = SDL_CreateTextureFromSurface(graphicsWrapper->renderer, surface);
	}

	SDL_FreeSurface(surface);
	surface = NULL;
}

void Tile::render(GraphicsWrapper* graphicsWrapper) {
	if (value == -1 && showValue) {
		SDL_SetRenderDrawColor(graphicsWrapper->renderer, 0xFF, 0x00, 0x00, 0xFF);

	} else {
		SDL_SetRenderDrawColor(graphicsWrapper->renderer, 0xAA, 0xAA, 0xAA, 0xFF);
	}

	SDL_RenderFillRect(graphicsWrapper->renderer, &box);
	SDL_RenderCopy(graphicsWrapper->renderer, texture, NULL, &box);
}

void Tile::placeBomb() {
	value = -1;
}

void Tile::incrementBombProximityCount() {
	if (value > -1) {
		value++;
	}
}

bool Tile::isBomb() {
	return value == -1;
}
