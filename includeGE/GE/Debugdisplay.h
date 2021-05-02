#ifndef DEBUGDISPLAY_H
#define DEBUGDISPLAY_H

#ifdef NEIVERR

#include <string>
#include <sstream>
#include <cstdlib>
#include <SDL.h>
//#include "GameEngine/Fontmachine.h"

namespace play{

class Debugdisplay
{
public:
	Debugdisplay(void);
	Debugdisplay( play::Fontmachine *fon );
	~Debugdisplay(void);
	//
	// private methods mostly
	SDL_Surface* create_surface( char *text );
	SDL_Surface* create_surface( int size_x, int size_y );
	SDL_Surface* create_surface( int size_x, int size_y, int r, int g, int b, int alpha );
	// private methods mostly
	//
	//
	SDL_Surface* get_background(void);
	void clear_background(void);
	void write_on_surface(SDL_Surface*,int,int);
	// display on graphics
	void display( int row, char *description, int value );
	void display( int row, char *description, bool value );
	void display( int row, char *description, float value );
	// display on std::cout << .....
	void display( char *description, int value );
	void display( char *description, bool value );
	void display( char *description, float value );
	//

private:
	Uint8 alpha;
	SDL_Color  bkgr;
	Fontmachine* fo;
	SDL_Surface *background;
	bool debugFlag;
	int font_h;		// font height
	int displacementX, displacementY;
};
}
#endif

#endif
