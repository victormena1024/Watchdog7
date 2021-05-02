
// Library dependencies: libSDL, libSDL_net


#include <iostream>
#include <string>
#include <cstdlib>
#include <SDL_net.h>
#include <SDL.h>
#include "ClientSocket2.h"

#include <vector>
#include <cassert>
#include <iostream>
#include <fstream>
#include <cstdarg>


//float tx = 0.0, ty=0.0;
//int   itx, ity;
float incomingangle = 0.0;
float incomingdiameter = 90.0;
//void cacheUpCommand(char *);
//void sendAllCashedCommands();


//static int foreground_color;
//static int background_color;



// Create a pointer to a ServerSocket object
ClientSocket *cs;
int begin = 0;
char sdestinationLine[4096 + 7];

void sendInteger(int);				// A
void sendIntegerX(int);				// B
void plotRGB(int _red, int _green, int _blue);	// C
void sendText(char *);				// D
void sendTextLines(char *);			// E
void plotXY(int x, int y, int color);// F
void plotBinary(int);				// G
//
void queueCommand(char *baffer);
void sendAllQueuedCommands();




int main(int argc, char *argv[])
{
	// Initialise SDL_net (Note: We don't initialise or use normal SDL at all - only the SDL_net library!)
	if (SDLNet_Init() == -1)
	{
		std::cout << "Failed to intialise SDL_net: " << SDLNet_GetError() << std::endl;
		exit(-1);
	}
	// Create a pointer to a ServerSocket object
//	ClientSocket *cs;
	try
	{
		// Now try to instantiate the client socket
		// Parameters: server address, port number, buffer size (i.e. max message size)
		// Note: You can provide the serverURL as a dot-quad ("1.2.3.4") or a hostname ("server.foo.com")
		
		cs = new ClientSocket("127.0.0.1", 12345, 4096);
	//	cs = new ClientSocket("127.0.0.1", 12345, 512); // original
		//	cs = new ClientSocket("localhost", 12345, 255 );
	}
	catch (SocketException e)
	{
		std::cout << "Something went wrong creating a ClientSocket object." << std::endl;
		std::cout << "Error is: " << e.what()   << std::endl;
		std::cout << "Exit code is 777" << endl; 
		std::cout << "Terminating application." << std::endl;
		exit(-1);
	}


	try
	{
		cs->connectToServer();// Attempt to connect to the server at the provided address and port
		string receivedMessage = "";
		std::cout << "Use /quit to disconnect or /s to shutdown the server." << endl;
		// Display the initial prompt
//		cs->displayPrompt();
		// Run the main loop...
		do
		{

#ifdef NEV
			// Check if we've received a message
			receivedMessage = cs->checkForIncomingMessages();
			//			receivedMessage = "";
			// If so then...
			if (receivedMessage != "")
			{
				// Display the message and then blank it...
				cs->displayMessage(receivedMessage);
				// and then re-display the prompt along with any typed-but-not-yet-sent input
				std::cout << "receivedMessage: '" << receivedMessage << "'\n";
				//sendInteger(999);
				//SDL_Delay(99);
			}
#endif


			/*
			for(int i=0;i<360;i++)
			{
			sendInteger(i);
			sendIntegerX(i);
			sendIntegerY(i);
			sendText("mixtext[ijkk++]AAAAAAAAAAAAAAAAAAAAAAAAAAAAARRRRRRRRRRRRRRRRRRGH!");
			sendTextLines("This is another textual line that i want you to send, cool huh? - yesh! meow! by all means.continue so ");
			sendAllCashedCommands();
			SDL_Delay(10);	// needed for synchronization
		}
			exit(0);
*/




//			exit(0);
#ifdef dev
			// add one command at a time
			cacheUpCommand("A111");			// wheel
			cacheUpCommand("B222");			// plot x
			cacheUpCommand("C333");			// plot y
			cacheUpCommand("DTesting"); // textbox
			cacheUpCommand("E100,100,2");	 // plot x,y
			cacheUpCommand("F100");		     // binary bits
			cacheUpCommand("G<++++ AAAAAAAAAAAAAAAAAA   ++++++>");
			cacheUpCommand("G<++++ BBBBBBBBBBBBBBBBBB   ++++++>");
			//cacheUpCommand("E<++++++!==================================================!++++++>");
			sendAllCashedCommands();// send all cached commands
//			sendAllCashedCommands();
			exit(0);
#endif
		//	exit(0);
		//	tx += 0.0;
		//	ty += 0.0;

			static int itx = 0;
			itx++;
							
			sendInteger(  itx);
			sendIntegerX( itx );

			char *mixtext[] = {
				{ ".*0*. dont scare me away           " },
				{ ".*1*.get the hideaway           " },
				{ ".*2*.This is some text sent through" },
				{ ".*3*.help someone here?            " },
				{ ".*4*.blackbird                     " },
				{ ".*5*.nasty dogs and funky kings    " },
				{ ".*6*.I knocked down your door      " },
				{ ".*7*.en stund, en ....             " },
				{ ".*8*.        -= hellow =-          " },
				{ ".*9*.   aaa   -= bye =-   aaa       " },
				{ " - + - " },
				{ nullptr }
			};
			char *mixtext3[] = {
				{ "***              * * *               xaa" },
				{ "f***             *****            xxaaaa " },
				{ "fff***             *          xxxaaaa   " },
				{ ".*3*.hello         *       xxxdfsfdaaf      " },
				{ ".*4*.blackbird           xxxxweraerwe       " },
				{ ".*5*.nasty dogs         xxkingsa   " },
				{ ".*6*.I knocked         xfaaora gfdgd    " },
				{ ".*7*.en stund      1 nxxa aa        " },
				{ ".*8*. aaaaaaa-=ahe  ow =a  " },
				{ ".*9*.    aaaaaaaaaaaa   " },
				{ " - + - " },
				{ nullptr }
			};

					
			char *mixtext1[] = {
				{ "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et" },
				{ "consectetur adipiscing elit, sed do dolore magna aliqua. Ut enim ad minim " },
				{ "eiusmod tempor incididunt ut labore et" },
				{ "dolore magna aliqua. Ut enim ad minim " },
				{ "veniam, quis nostrud exercitation " },
				{ "ullamco laboris nisi ut aliquip ex " },
				{ "ea commodo consequat. Duis aute " },
				{ "irure dolor in reprehenderit " },
				{ "in voluptate velit esse cillum dolore" },
				{ "eu fugiat nulla pariatur. Excepteur sint" },
				{ "occaecat cupidatat non proident, sunt in" },
				{ "culpa qui officia deserunt mollit anim " },
				{ "id est laborum" },
				{ "" },
				{ "" },
				{ "" },
				{ "" }
			};

			static int ijkk = 0;
			ijkk &= 7;
			sendText(mixtext1[ijkk++]);


//			sendAllCashedCommands();
	//sendTextLines("This is another textual line that i want you to send, cool huh? - yesh! meow! by all means.continue so )");
//	sendAllCashedCommands();

			char *mixtext2[] = {
//				{ "This is another textual line that i want you to send, cool huh? - yesh! meow! by all means )" },
				{ ".*0*.#                        " },
				{ ".*1*. #                       " },
				{ ".*2*.  #                      " },
				{ ".*3*.   #                     " },
				{ ".*4*.    #                    " },
				{ ".*5*.     #                   " },
				{ ".*6*.      #                  " },
				{ ".*7*.       #                 " },
				{ ".*8*.        #                " },
				{ ".*9*.         #               " },
				{ ".*a*.          #              " },
				{ ".*b*.           #             " },
				{ ".*c*.            #            " },
				{ ".*d*.             #           " },
				{ ".*e*.              #          " },
				{ ".*f*.               #         " },
				{ ".*0*.                #########" },
				{ ".*1*.    this               # " },
				{ ".*2*.         is           #  " },
				{ ".*3*.           a         #   " },
				{ ".*4*.            test    #    " },
				{ ".*5*.                   #     " },
				{ ".*6*.                  #      " },
				{ ".*7*.                 #       " },
				{ ".*8*.                #        " },
				{ ".*9*.               #         " },
				{ ".*a*.              #          " },
				{ ".*b*.             #           " },
				{ ".*c*.            #            " },
				{ ".*d*.           #             " },
				{ ".*e*.          #              " },
				{ ".*f*.##########               " },
				{ " - + - " },
				{ nullptr }
			};
//			sendTextLines(mixtext2[ijk++]);

			static int ijk = 0;
			ijk &= 31;
			sendTextLines(mixtext2[ ijk++ ]);

			sendAllQueuedCommands();
			SDL_Delay(10);	// needed for synchronization

			
//#ifdef DEV
			/*
			if (incomingColor == 1) _color = joinColorValue2(0, 0, 0, SDL_ALPHA_OPAQUE);// black
			if (incomingColor == 2) _color = joinColorValue2(0, 0, 170, SDL_ALPHA_OPAQUE);//blue
			if (incomingColor == 3) _color = joinColorValue2(0, 170, 0, SDL_ALPHA_OPAQUE);//green
			if (incomingColor == 4) _color = joinColorValue2(0, 170, 170, SDL_ALPHA_OPAQUE);//cyan
			if (incomingColor == 5) _color = joinColorValue2(170, 0, 0, SDL_ALPHA_OPAQUE);//red
			if (incomingColor == 6) _color = joinColorValue2(170, 0, 170, SDL_ALPHA_OPAQUE);//magenta
			if (incomingColor == 7) _color = joinColorValue2(170, 85, 0, SDL_ALPHA_OPAQUE);//brown
			if (incomingColor == 8)  _color = joinColorValue2(170, 170, 170, SDL_ALPHA_OPAQUE);//gray
			if (incomingColor == 9)  _color = joinColorValue2(85, 85, 85, SDL_ALPHA_OPAQUE);//dark gray
			if (incomingColor == 10) _color = joinColorValue2(85, 85, 255, SDL_ALPHA_OPAQUE);//bright blue
			if (incomingColor == 11) _color = joinColorValue2(85, 255, 85, SDL_ALPHA_OPAQUE);//bright green
			if (incomingColor == 12) _color = joinColorValue2(85, 255, 255, SDL_ALPHA_OPAQUE);//bright cyan
			if (incomingColor == 13) _color = joinColorValue2(255, 85, 85, SDL_ALPHA_OPAQUE);//bright red
			if (incomingColor == 14) _color = joinColorValue2(255, 85, 255, SDL_ALPHA_OPAQUE);//bright magenta
			if (incomingColor == 15) _color = joinColorValue2(255, 255, 85, SDL_ALPHA_OPAQUE);//yellow
			*/

			float incomingangle2 = 0;

			for (int i = 0; i < 12; i ++)
			{
				static int col1 = 2, col2 = 3, col3 = 5, col4 = 4;
				
				int	ppx = rand() % 250;
				int ppy = rand() % 250;;

			plotXY(ppx, ppy, 9 ); // gray

				incomingangle += 3.0f;
				incomingangle2 += 2.3f;
				incomingdiameter -= 0.4f;
				float rad1 = (float)incomingangle * (M_PI / 180.0f);
				float py = sinf(rad1) * (incomingdiameter)+128.0f;
				float px = cosf(rad1) * (incomingdiameter)+128.0f;
				float pz = cosf(rad1*1.4f) * (incomingdiameter)+128.0f;
				if (incomingdiameter < 2.0f) incomingdiameter = 90.0f;
				plotXY(px, py, 10);	// blue

//		plotRGB(118,118,118);
		plotRGB(px, py, pz);

				float rad2 = ((float)incomingangle + 33.0f) * (M_PI / 180.0);
				py = sinf(rad2) * (cosf(incomingdiameter)*120.0f) + 128.0;
				px = cosf(rad2) * (sinf(incomingdiameter)*120.0f) + 128.0;
				plotXY(px, py, 13); // red

				float rad3 = ((float)incomingangle + 66.0f) * (M_PI / 180.0f);
				float rad4 = ((float)incomingangle + 55.0f) * (M_PI / 180.0f);
				py = (sinf(rad3) + cosf(rad4 * 4.0) / 2.3f) * 90.0f + 128.0f;	// 4.0 2.3
				px = (cosf(rad3) + sinf(rad4 * 4.0) / 2.3f) * 90.0f + 128.0f; // 4.0 2.3
				plotXY(px, py, 15); // yellow

				static int index1 = 0, index2 = 0;
				index1++;
				if (index1 == 1200){
					index1 = 0;
					plotXY(0, 0, 0);  // clear plot area
				}
			
			}

			static int index2=0;
			index2++;
			plotBinary(index2);

#ifdef DEV
			static int pu=0;
			static float aincomingangle = 0.0f;
			static float aincomingangle2 = 0.0f;
			static float aincomingdiameter = 120.0f;
			aincomingangle2 += 8.5f;
			aincomingangle    += 5.5f;
			aincomingdiameter -= 0.2f;
			float rad1 = (float)aincomingangle * (M_PI / 180.0f);
			float rad2 = (float)aincomingangle2 * (M_PI / 180.0f);
			float py = sinf(rad1); // *(aincomingdiameter);// +128.0;
			float px = cosf(rad1*2.3); // *(aincomingdiameter);// +128.0;
			//float pz = tanf(rad1*1.4) * (aincomingdiameter)+128.0;
			float pz = ((px + py)*50.0f) + 128.0f;
			px = px * 50.0f + 128.0f;

			if (aincomingdiameter < 2.0) aincomingdiameter = 180.0f;
			sendIntegerY(px, py*50.0f + 128.0f, (int)pz);
	//		sendIntegerY((int)px, (int)py, (int)pz);
	pu++;
	pu &= 127;

//	sendIntegerY(0,128,255);

#endif


	sendAllQueuedCommands();
	SDL_Delay(10);	// needed for synchronization

//#endif










		// ... until we decide to quit or the server is shut down
		} while ( (cs->getShutdownStatus() == false));

	}
	catch (SocketException e)
	{
		std::cout << "Caught an exception in the main loop..." << endl;
		std::cout << e.what() << endl;
		std::cout << "Exit code is 1101" << endl;
		std::cout << "Terminating application." << endl;
	}
	// Shutdown SDLNet - our ClientSocket will clean up after itself on destruction
	SDLNet_Quit();
	return 0;
}




void sendInteger( int i ){
	char buffer[32];
	sprintf_s(&buffer[0],15, "A%d\0", i);
	queueCommand(buffer);
}
void sendIntegerX(int i){
	char buffer[32];
	sprintf_s(&buffer[0],15, "B%d\0", i);
	queueCommand(buffer);
}
void plotRGB(int _red, int _green, int _blue){
	char buffer[32];
	_red &= 255;
	_green &= 255;
	_blue &= 255;
	sprintf_s(&buffer[0], 25, "C%0.2X%0.2X%0.2X", _red, _green, _blue);
	queueCommand(buffer);
}
void sendText(char *text){
	char buffer[4096];
	sprintf_s(&buffer[0],4090,"D%s\0", text);
	queueCommand(buffer);
}
void sendTextLines(char *text){
	char buffer[4096];
	sprintf_s(&buffer[0], 4090, "E%s\0", text);
	queueCommand(buffer);
}

// if color == 0, it means clear drawing box
void plotXY(int itx, int ity, int color){
	char hexchars[] = "0123456789ABCDEF";
	char buffer[32]; // = { 'E', 0 };
	int _c = color & 15;
	int _x = itx & 255;
	int _y = ity & 255;
	if ( color == 0){ // reset
		sprintf_s(&buffer[0],15, "F00000");
	}
	else{
		sprintf_s(&buffer[0], 15, "F%X%0.2X%0.2X", _c, _x, _y);
	}
	queueCommand(buffer);
}
void plotBinary(int i){
	char buffer[32];
	sprintf_s(&buffer[0], 15, "G%d\0", i);
	queueCommand(buffer);
}
// queue one command at a time
void queueCommand(char *baffer)
{
	int incomingSize = strlen(baffer);
	strcpy_s( &sdestinationLine[ begin ], 4000, baffer );
	sdestinationLine[ begin + incomingSize ] = ':';
	sdestinationLine[ begin + incomingSize + 1 ] = '\0';
	begin += incomingSize + 1;
	if (incomingSize>4000 || begin>4000)  sendAllQueuedCommands();
}
//
void sendAllQueuedCommands()
{
	int size = strlen(sdestinationLine);
	if ( size == 0) return;
	sdestinationLine[4004] = 0;
	cs->sendCommand( &sdestinationLine[0] );
	begin = 0;
	// std::cout << "size : "<< size << ", line  = '" << (sdestinationLine) << "\n";
}










