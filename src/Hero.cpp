#include <SDL.h>
#include <SDL_image.h>

#include "GraphicsWrapper.hpp"
#include "SoundWrapper.hpp"
#include "Platform.hpp"
#include "Hero.hpp"

Hero::Hero() {
	x = 100;
	y = 300;
	w = 20;
	h = 30;
	box.x = x;
	box.y = y;
	box.w = w;
	box.h = h;

	facingRight = false;
	isOnFloor = false;

	spriteClips[0].x =   0;
	spriteClips[0].y =   0;
	spriteClips[0].w =  64;
	spriteClips[0].h = 205;

	spriteClips[1].x =  64;
	spriteClips[1].y =   0;
	spriteClips[1].w =  64;
	spriteClips[1].h = 205;
	
	spriteClips[2].x = 128;
	spriteClips[2].y =   0;
	spriteClips[2].w =  64;
	spriteClips[2].h = 205;

	spriteClips[3].x = 196;
	spriteClips[3].y =   0;
	spriteClips[3].w =  64;
	spriteClips[3].h = 205;

	spriteSheetTexture = NULL;

	gravity = DOWN;
}

Hero::~Hero() {
	SDL_DestroyTexture(spriteSheetTexture);
	spriteSheetTexture = NULL;
}

void Hero::handleEvents(SDL_Event* event, SoundWrapper* soundWrapper) {
	(void) soundWrapper;
	if (event->type == SDL_KEYDOWN || event->type == SDL_KEYUP) {
		keyboardHandler.handleKeyboardEvent(event->key.keysym.sym, event->type);
	}
}

void Hero::update(GraphicsWrapper* graphicsWrapper, Platform** platforms) {
	if (!spriteSheetTexture) {
		initTexture(graphicsWrapper);
	}

	if ((keyboardHandler.isPressed(SDLK_SPACE) || keyboardHandler.isPressed(SDLK_UP)) && isOnFloor) {
		if (gravity == DOWN) {
			y -= 30;
		} else if (gravity == UP) {
			y += 30;
		} else if (gravity == LEFT) {
			x += 30;
		} else if (gravity == RIGHT) {
			x -= 30;
		}
		isOnFloor = false;
	}
	if (keyboardHandler.isPressed(SDLK_LEFT)) {
		facingRight = false;
		if (gravity == DOWN) {
			x -= 5;
		} else if (gravity == UP) {
			x += 5;
		} else if (gravity == LEFT) {
			y -= 5;
		} else if (gravity == RIGHT) {
			y += 5;
		}
	}
	if (keyboardHandler.isPressed(SDLK_RIGHT)) {
		facingRight = true;
		if (gravity == DOWN) {
			x += 5;
		} else if (gravity == UP) {
			x -= 5;
		} else if (gravity == LEFT) {
			y += 5;
		} else if (gravity == RIGHT) {
			y -= 5;
		}
	}
	// if (keyboardHandler.isPressed(SDLK_DOWN)) {
	// 	if (gravity == DOWN) {
	// 		x+-= 5;
	// 	} else if (gravity == UP) {
	// 		x -= 5;
	// 	} else if (gravity == LEFT) {
	// 		y += 5;
	// 		facingRight = false;
	// 	} else if (gravity == RIGHT) {
	// 		y -= 5;
	// 		facingRight = true;
	// 	}
	// 	y += 5;
	// }

	box.x = x;
	box.y = y;
	box.w = w;
	box.h = h;

	if (gravity == DOWN) {
		++y;
	} else if (gravity == UP) {
		y -= 1;
	} else if (gravity == LEFT) {
		x -= 1;
	} else if (gravity == RIGHT) {
		++x;
	}

	for (int i = 0; i < 5; i++) {
		handleCollisions(platforms[i]);
	}
}

void Hero::handleCollisions(Platform* platform) {
	// _
	if (y + h > platform->y && y < platform->y && platform->x <= x && x + w <= platform->x + platform->w) {
		y -= y + h - platform->y;
		gravity = DOWN;
		isOnFloor = true;
	}
	// ^
	if (y + h > platform->y + h && y < platform->y + platform->h && platform->x <= x && x + w <= platform->x + platform->w) {
		y += platform->y + platform->h - y;
		gravity = UP;
		isOnFloor = true;
	}
	// >
	if (x + w > platform->x && x < platform->x && platform->y <= y && y + h <= platform->y + platform->h) {
		x -= x + w - platform->x;
		gravity = RIGHT;
		isOnFloor = true;
	}
	// <
	if (x < platform->x + platform->w && x + w > platform->x + platform->w && platform->y <= y && y + h <= platform->y + platform->h) {
		x += platform->x + platform->w - x;
		gravity = LEFT;
		isOnFloor = true;
	}
}

void Hero::initTexture(GraphicsWrapper* graphicsWrapper) {
	SDL_Surface* spriteSurface = IMG_Load("./assets/images/foo.png");
	if (!spriteSurface) {
		printf("Unable to load image %s! SDL_image Error: %s\n", "./images/foo.png", IMG_GetError());
	} else {
		SDL_SetColorKey(spriteSurface, SDL_TRUE, SDL_MapRGB(spriteSurface->format, 0, 0xFF, 0xFF));
		spriteSheetTexture = SDL_CreateTextureFromSurface(graphicsWrapper->renderer, spriteSurface);
	}

	SDL_FreeSurface(spriteSurface);
	spriteSurface = NULL;
}

void Hero::render(GraphicsWrapper* graphicsWrapper) {
	SDL_Rect* currentClip = &spriteClips[graphicsWrapper->frame/4];

	SDL_RendererFlip flip = SDL_FLIP_NONE;
	if (facingRight) {
		flip = SDL_FLIP_HORIZONTAL;
	}

	double angle = 0;
	if (gravity == LEFT) {
		angle = 90.0;
	} else if (gravity == RIGHT) {
		angle = 270.0;
	} else if (gravity == UP) {
		angle = 180.0;
	}

	SDL_RenderFillRect(graphicsWrapper->renderer, &box);

	SDL_RenderCopyEx(graphicsWrapper->renderer, spriteSheetTexture, currentClip, &box, angle, NULL, flip);

	++graphicsWrapper->frame;
	if (graphicsWrapper->frame / 4 >= walkingAnimationFrames) {
		graphicsWrapper->frame = 0;
	}
}
