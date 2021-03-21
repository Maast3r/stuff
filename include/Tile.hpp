#include <SDL.h>

#include "GraphicsWrapper.hpp"
#include "SoundWrapper.hpp"

#ifndef TILE_HPP
#define TILE_HPP

class Tile {
    private:
        SDL_Rect box;
        SDL_Texture* texture;
    
    public:
        int value;
        bool showValue;
        bool visited;

        Tile(int x, int y, int w, int h);
        ~Tile();
        void handleEvents(SDL_Event* event, SoundWrapper* soundWrapper);
        void update(GraphicsWrapper* graphicsWrapper);
        void render(GraphicsWrapper* graphicsWrapper);
        void placeBomb();
        void incrementBombProximityCount();
        bool isBomb();
};

#endif
