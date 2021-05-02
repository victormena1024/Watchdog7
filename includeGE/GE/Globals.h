#ifndef GLOBALS_H
#define GLOBALS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <SDL.h>

//#include <iostream>
//using namespace std;
//#include "GameEngine/MyRenderer.h"
//#include "GameEngine/Spelmotor.h"
//#include "GameEngine/Tower.h"
//#include "GameEngine/Castle.h"


// ********************** //
// ********************** //
// ********************** //
//
// Access code like this
//         	play::Globals::getinstance();
//
//	play::Globals *globals9 = play::Globals::getinstance();
//	globals9->testFunc();
//
// ********************** //
// ********************** //
// ********************** //

namespace play{


//	Globals *globals;
//	void *globals;

class Globals
  {
  public:
      static Globals *getinstance();
	  //Globals();
	  ~Globals();

	void  initAll(int width, int height);
	void deinitAll();
	// ... //
	SDL_Renderer *get_SDL_Renderer(); 
    SDL_Window *  get_Window();
    SDL_Surface * get_screenSurface(); 
	// ... //
	void          set_SDL_Renderer(SDL_Renderer *);
	void          set_Window(SDL_Window *);
	void          set_screenSurface (SDL_Surface * );
 // ------------------   
//	void * get_Spelmotor(void); 
//  void   set_Spelmotor(void * );
// -------------------
	static void * getinstanceCastle();
//    static void * getinstanceSpelmotor();
// -------------------
	void *getUserData(void);
	void setUserData(void *usr);
// -------------------


private:
	Globals(){
		mWindow = nullptr;
		mRenderer = nullptr;
		mScreen = nullptr;
	}
	//
	SDL_Renderer *mRenderer = nullptr;
    SDL_Window   *mWindow   = nullptr;
    SDL_Surface  *mScreen   = nullptr;
	//
//    void * mSpelmotor = nullptr;
	//
	void *userData;
	//
};

	// GLOBALS VARIABLES are created within functions

}// namespace





#ifdef __cplusplus
}
#endif

/*
void Spelmotor::run() {
		int	  event_fps;
		bool  event_activated_flag;

		Globals *globals = Globals::getinstance();
		DerivedInputEventListener *newListener = new DerivedInputEventListener();
		inputHandler->registerInputListener(  newListener );

	  bool quit = false;
		int tickInterval = 1000 / event_fps;
		Uint32 nextTick;
		while (!quit) {
			nextTick = SDL_GetTicks() + tickInterval;
			int delay = nextTick - SDL_GetTicks();

			quit = inputHandler->executeEventLoop();

			if (quit) return;
			collisionHandler->collisionTick();
			if (delay > 0) {
			  SDL_Delay(delay);
			}
		} // while
	}

*/

#endif