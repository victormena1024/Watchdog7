// Re-written simple SDL_net socket client example | Nov 2011 | r3dux
// Library dependencies: libSDL, libSDL_net

// IMPORTANT: This project will only build successfully in Debug mode on Windows!

#include <iostream>
#include <string>
#include "SDL_net.h"
#include "SDL.h"
#include "ClientSocket.h"

#include <vector>
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdarg>


//#include "GameEngine/Imageutils.h"

/*
#include "GameEngine/VDEBUG.h"
#include <gameEngine/Spelmotor.h>
#include <gameEngine/Asprite.h>
#include <gameEngine/Sprite.h>
#include <gameEngine/Imageutils.h>
#include <gameEngine/ImageProcessor.h>
#include <gameEngine/BlockySprite.h>
#include <gameEngine/castle.h>
#include <gameEngine/Tower.h>
#include <gameEngine/Loader.h>
#include <gameEngine/Animation.h>
#include <gameEngine/Animhandler.h>
#include <gameEngine/Audio.h>
#include <gameEngine/BoxCollider.h>
#include <gameEngine/CollisionHandler.h>
#include <gameEngine/CollisionListener.h>
#include <gameEngine/configfile.h>
#include <gameEngine/DebugDisplay.h>
#include <gameEngine/Errorreport.h>
#include <gameEngine/Fysik.h>
#include <gameEngine/InputEventListener.h>
#include <gameEngine/InputHandler.h>
#include <gameEngine/movement.h>
#include <gameEngine/MyRenderer.h>
#include <gameEngine/parserV.h>
#include <gameEngine/SpelClocka.h>
#include <gameEngine/SpriteConstraint.h>
#include <gameEngine/TimerListener.h>
*/

int main(int argc, char *argv[])
{
	// Initialise SDL_net (Note: We don't initialise or use normal SDL at all - only the SDL_net library!)
	if (SDLNet_Init() == -1)
	{
		std::cout << "Failed to intialise SDL_net: " << SDLNet_GetError() << std::endl;
		exit(-1);
	}

	// Create a pointer to a ServerSocket object
	ClientSocket *cs;

	try
	{
		// Now try to instantiate the client socket
		// Parameters: server address, port number, buffer size (i.e. max message size)
		// Note: You can provide the serverURL as a dot-quad ("1.2.3.4") or a hostname ("server.foo.com")
		cs = new ClientSocket("127.0.0.1", 12345, 512);
	}
	catch (SocketException e)
	{
		std::cout << "Something went wrong creating a ClientSocket object." << std::endl;
		std::cout << "Error is: " << e.what()   << std::endl;
		std::cout << "Exit code is 555" << endl; 
		std::cout << "Terminating application." << std::endl;
		exit(-1);
	}

	try
	{
		// Attempt to connect to the server at the provided address and port
		cs->connectToServer();

		string receivedMessage = "";

		std::cout << "Use /quit to disconnect or /shutdown to shutdown the server." << endl;

		// Display the initial prompt
		cs->displayPrompt();

		// Run the main loop...
		do
		{
			// Check if we've received a message
			receivedMessage = cs->checkForIncomingMessages();
			// If so then...
			if (receivedMessage != "")
			{
				// Display the message and then blank it...
				cs->displayMessage(receivedMessage);
				// and then re-display the prompt along with any typed-but-not-yet-sent input
				cs->displayPrompt();
			}
			// Get and deal with input from the user in a non-blocking manner
			cs->getUserInput();
		// ... until we decide to quit or the server is shut down
		} while ( (cs->getShutdownStatus() == false));

	}
	catch (SocketException e)
	{
		std::cout << "Caught an exception in the main loop..." << endl;
		std::cout << e.what() << endl;
		std::cout << "Exit code is 666" << endl;
		std::cout << "Terminating application." << endl;
	}

	// Shutdown SDLNet - our ClientSocket will clean up after itself on destruction
	SDLNet_Quit();

	return 0;
}
