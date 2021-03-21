#include <map>

#include <SDL.h>

#ifndef KEYBOARDHANDLER_HPP
#define KEYBOARDHANDLER_HPP

class KeyboardHandler {
	private:
		std::map<SDL_Keycode, Uint32> keyStates;

	public:
		void handleKeyboardEvent(Uint32 keyCode, Uint32 eventType);
		bool isPressed(Uint32 keyCode);
		bool isReleased(Uint32 keyCode);
};

#endif
