// SERVER
// Library dependencies: libSDL, libSDL_net
// IMPORTANT: 


#include "SDL.h"
#include "SDL_net.h"
#include "ServerSocket.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <ctime>



// #include "GE/Imageutils.h"
#include "GE/Loader.h"
//#include "GE/Loader.h"
#include "GE/Sprite.h"







//SDL_Window   *win = NULL;
//SDL_Renderer *renderer = NULL;
//SDL_Texture  *bitmapTex = NULL;

//void startup_graphics();
//void execute_graphic_loop();
//void modify_graphic_loop(int,int);
//void exit_graphics();


//void startup_graphics();
//void modify_graphic_loop(int _x, int _y);
//void execute_graphic_loop();
//void exit_graphics();



/*
#include <./include/GE/Everything.h>
#include <../include/GE/Everything.h>
#include <GE/Everything.h>
*/

//#include "GE/Sprite.h"
//#include "GE.h"

// ERROR
//#include "GE/Sprite.h"
//#include "b.h"
// ERROR

//#echo error
// #include <GE/everything.h>

//#ifdef NEIVERR
// #include <GE/everything.h>
#include <GE/Sprite.h>
#include <GE/Imageutils.h>
#include <GE/ImageProcessor.h>
#include <GE/BlockySprite.h>
#include <GE/castle.h>
#include <GE/Tower.h>
#include <GE/Loader.h>
#include <GE/Animation.h>
//#include <GE/Animhandler.h>
#include <GE/Audio.h>
//#include <GE/BoxCollider.h>
#include <GE/CollisionHandler.h>
#include <GE/CollisionListener.h>
//#include <GE/configfile.h>
#include <GE/DebugDisplay.h>
//#include <GE/Errorreport.h>
#include <GE/Fysik.h>
#include <GE/InputEventListener.h>
#include <GE/InputHandler.h>
//#include <GE/movement.h>
#include <GE/MyRenderer.h>
//#include <GE/parserV.h>
#include <GE/SpelClocka.h>
//#include <GE/SpriteConstraint.h>
#include <GE/TimerListener.h>
//#include <GE/VDEBUG.h>
//#endif


#pragma warning ( disable : 4305; disable : 4244 )

using namespace std;
//using namespace play;


#include "Commands.h"
extern Commands *commandLayer;





int main(int argc, char *argv[])
{

	//startup_graphics();
	commandLayer->beginHardware();	// init graphics and everything
	commandLayer->beginAllocateDefaultPrivateData();// allocate default data for all types
//	commandLayer->executeCommand();

	// HEXXOR
//	play::Spelmotor *spelmotor = new play::Spelmotor();
//	spelmotor->init();	// parse files
//	spelmotor->getCastle();
// HEXXOR

	/*
SDL_INIT_TIMER: timer subsystem
	SDL_INIT_AUDIO : audio subsystem
	SDL_INIT_VIDEO : video subsystem; automatically initializes the events subsystem
	SDL_INIT_JOYSTICK : joystick subsystem; automatically initializes the events subsystem
	SDL_INIT_HAPTIC : haptic(force feedback) subsystem
	SDL_INIT_GAMECONTROLLER : controller subsystem; automatically initializes the joystick subsystem
	SDL_INIT_EVENTS : events subsystem
	SDL_INIT_EVERYTHING : all of the above subsystems
	SDL_INIT_NOPARACHUTE : compatibility; this flag is ignored
*/

	// Initialise SDL_net
	if (SDLNet_Init() == -1)
	{
		std::cout << "Failed to intialise SDL_net: " << SDLNet_GetError() << std::endl;
		exit(-1000);
	}

	// Create a pointer to a ServerSocket object
	ServerSocket *ss;
	try
	{
		// Not try to instantiate the server socket
		// Parameters: port number, buffer size (i.e. max message size), max sockets
//		ss = new ServerSocket(12345, 512, 3);// original
//		ss = new ServerSocket(12345, 4096, 3);
		ss = new ServerSocket(12345, 4096, 3);
	}
	catch (SocketException e)
	{
		std::cout << "Something went wrong creating a SocketServer object." << std::endl;
		std::cout << "Error is: " << e.what()   << std::endl;
		std::cout << "Exit code is 222" << endl;
		std::cout << "Terminating application." << std::endl;
		exit(-1);
	}
	try
	{

		bool quitMeNow = false;
		// Specify which client is active, -1 means "no client is active"
		int activeClient = -1;
		// Main loop...
		do
		{
			// Check for any incoming connections to the server socket
			ss->checkForConnections();

			// At least once, but as many times as necessary to process all active clients...
			do
			{
				// ..get the client number of any clients with unprocessed activity (returns -1 if none)
				activeClient = ss->checkForActivity();
				// If there's a client with unprocessed activity...
				if (activeClient != -1)
				{
					// ...then process that client!

					ss->dealWithActivity(activeClient);	  // action here

				}


				SDL_Event e;
				if (SDL_PollEvent(&e)) {
					if (e.type == SDL_QUIT) { 
						quitMeNow = true;
						break; }
				}
				

			// When there are no more clients with activity to process, continue...
			} while (activeClient != -1 && quitMeNow== false );
		// ...until we've been asked to shut down.
		} while (ss->getShutdownStatus() == false && quitMeNow == false);
	}
	catch (SocketException e)
	{
		cout << "Caught an exception in the main loop..." << endl;
		cout << e.what() << endl;
		std::cout << "Exit code is 444" << endl;
		cout << "Terminating application." << endl;
	}
	// Shutdown SDLNet - our ServerSocket will clean up after itself on destruction
	SDLNet_Quit();
	commandLayer->end();
	return 0;
}



