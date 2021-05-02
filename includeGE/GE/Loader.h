#ifndef Loader_H
#define Loader_H

#include <SDL.h>
#include <vector>
//#include <cassert>
//#include <iostream>
//#include <fstream>
//#include <string>
//#include <cstdarg>

#include "Imageutils.h"
//#include "GameEngine/VDEBUG.h"
//#include "GameEngine/Globals.h"
#include "GE/Globals.h"

namespace play{

	class Loader
	{
	public:
		~Loader();	
		static Loader* getInstance();
		
		SDL_Surface* surfaceGet( int handle );		// returns Image

		int  loadSingleSurface( char* filename, bool = true );				   // returns handle
		int  loadSingleSurface( char *directory, char* filename, bool = true );// returns handle
		//
		SDL_Surface *loadRGBA(char * filename);
		int  getBpp(  SDL_Surface *surf );
		void showBpp( SDL_Surface *surf );
		//
		//Audio* audio_get( int handle );					// returns audio
		int  audio_add( char* filename );					// returns handle
		int  audio_add( char *directory, char* filename );	// returns handle
		int  audio_add_multiple( char*, char**, int );			// returns handle
		bool audio_is_there_files_missing(void);
		// .........newfunc
		//
		void debugOn(void);
		void debugOff(void);
		void debugDisplayOn(void);
		void debugDisplayOff(void);


	private:
		Loader();  // Private so that it can  not be called
		// Global static pointer used to ensure a single instance of the class.
		//
		// Image
		std::vector<std::string>  Image_filenames;	// Array
		std::vector<SDL_Surface*> Image_surfaces;	// Array 
		//
		int Image_handle;		// egentligen en index till arrayen, men vi behandlar den som en handle
		// audio
		std::vector<std::string>  audio_filenames;	// Array
		//	std::vector<Audio*> audio_sounds;		// Array
		int audio_handle;		// egentligen en index till arrayen, men vi behandlar den som en handle
		bool debugFlag;
		//
		bool alphaTypemagenta;	// treat full magenta as transparent color
		bool alphaTypeColor;	// treat color zero (0,0,0) as transparent
		snaf::Imageutils		*ima;
//		SDL_Renderer	*mainRenderer;
//		VDEBUG_INIT

//		globals = Globals::getinstance();

	};
}
#endif