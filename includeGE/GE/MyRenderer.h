#ifndef MYRENDERERz_H
#define MYRENDERERz_H

#ifdef UNUSEDOLDCODE

#include "GameEngine/Spelmotor.h"
#include "GameEngine/Globals.h"
#include <SDL.h>


namespace play {

    class MyRenderer {
    public:
        MyRenderer();
        MyRenderer(Spelmotor *);
        ~MyRenderer();

        SDL_Renderer * createWindow(char *name, int posX, int posY, int width, int height);

        void renderSprites();
        SDL_Window   * getWindow();
        SDL_Surface  * getSurfacez();
        SDL_Renderer * getRenderer();
        void destroyDefaultWindow();
        //
        void displayHardwareDrawingBuffer();
        void clearDrawingBuffer();
        void clearDrawingBuffer(int r, int g, int b, int alpha);
        void clearDrawingSurface(SDL_Surface *scr);
    private:

        SDL_Window   *mainWin;              // the window object
        SDL_Surface  *mainScreenSurface;    // screen to display Sprites on
         Globals      *globals;

    };
}
#endif

#endif