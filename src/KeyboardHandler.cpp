#include <map>

#include <SDL.h>

#include "KeyboardHandler.hpp"

void KeyboardHandler::handleKeyboardEvent(Uint32 keyCode, Uint32 eventType) {
	keyStates[keyCode] = eventType;
}

bool KeyboardHandler::isPressed(Uint32 keyCode) {
	return keyStates[keyCode] == SDL_KEYDOWN;
}

bool KeyboardHandler::isReleased(Uint32 keyCode) {
	return keyStates[keyCode] == SDL_KEYUP;
}
