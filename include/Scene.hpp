#include <SDL.h>

#include "GraphicsWrapper.hpp"
#include "SoundWrapper.hpp"

#ifndef SCENE_HPP
#define SCENE_HPP

class Scene {
	protected:
		Scene* nextScene;

	public:
		bool shouldPop;

		virtual void handleEvents(SDL_Event* event, SoundWrapper* soundWrapper) = 0;
		virtual void update(GraphicsWrapper* graphicsWrapper) = 0;
		virtual void render(GraphicsWrapper* graphicsWrapper) = 0;
		Scene* getNextScene();
		void destroyNextScene();
};

#endif
