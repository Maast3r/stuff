#include <SDL.h>
#include <SDL_ttf.h>

#ifndef GRAPHICSWRAPPER_HPP
#define GRAPHICSWRAPPER_HPP

class GraphicsWrapper {
    public:
        SDL_Window* window;
        SDL_Renderer* renderer;
        TTF_Font* font;
        int frame;
        static const int screenWidth = 800;
        static const int screenHeight = 600;

        GraphicsWrapper();
        ~GraphicsWrapper();
};

#endif
