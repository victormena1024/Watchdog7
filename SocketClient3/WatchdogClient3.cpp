
/*
	SDL2.lib ; SDL2main.lib ; SDL2_Net.lib ; Ws2_32.lib ; Spelmotorlib.lib ; SDL_draw_static.lib

	depends on:
	SDL2_Net.lib
	Ws2_32.lib ?
*/
#include "WatchdogClient3.h"


// ClientSocket3 constructor
ClientSocket3::ClientSocket3(string theServerAddress, unsigned int theServerPort, unsigned int theBufferSize)
{
	failedCommunication = true;
	debug = false;      // Flag to control whether to output debug info
	shutdownClient = false;     // Flag to control whether it's time to shut down the client
	// The host name of the server.
	// This can be either a dot-quad like 127.0.0.1 or a hostname like "localhost" or "foo.com" etc.
	serverHostname = theServerAddress;
	serverPort = theServerPort; // The port on the server to connect to
	bufferSize = theBufferSize; // The maximum message size
	inputLength = 0;
	try
	{
		if (SDLNet_Init() == -1)
		{
			std::cout << "Failed to intialise SDL_net: " << SDLNet_GetError() << std::endl;
			exit(-1);
		}
		pBuffer = new char[bufferSize+7]; // Create the transmission buffer character array
		// Create a socket set big enough to hold the server socket and our own client socket
		socketSet = SDLNet_AllocSocketSet(2);
		// If we couldn't create the socket set then throw an exception
		if (socketSet == NULL)
		{
			string msg = "Failed to allocate the socket set in ClientSocket3 constructor: ";
			msg += SDLNet_GetError();
			SocketException e(msg);
			throw e;
		}
		failedCommunication = false;
	}
	catch (SocketException e)
	{
		// Re-throw the exception to be dealt with appropriately elsewhere
		throw e;
		exit(-1);
	}
} // End of ClientSocket3 constructor

// Static constants
const std::string  ClientSocket3::SERVER_NOT_FULL           = "OK";        // Server's response when there are free spots a client can join
const std::string  ClientSocket3::SERVER_FULL               = "FULL";      // Server's response when there are no free spots, so a client cannot join
//const std::string  ClientSocket3::SHUTDOWN_SIGNAL			= "/s"; // What you type to shutdown the server
//const std::string  ClientSocket3::QUIT_SIGNAL               = "/quit";     // What you type to shutdown the client
const unsigned int ClientSocket3::CONNECTION_TIMEOUT_PERIOD = 5000;        // 5 second connection timeout
const unsigned int ClientSocket3::SOCKET_SET_POLL_PERIOD    = 10;          // 10ms, so poll 100 times/second


// ClientSocket3 destructor
ClientSocket3::~ClientSocket3()
{
	if (failedCommunication == true){
	}
	// Close our server and client sockets
	SDLNet_TCP_Close(serverSocket);
	SDLNet_TCP_Close(clientSocket);
	// Free our socket set (i.e. all the clients in our socket set)
	SDLNet_FreeSocketSet(socketSet);
	// Release any properties on the heap
	delete pBuffer;
}
void ClientSocket3::connectToServer()
{
	failedCommunication = true;

	// Try to resolve the hostname to an IP address, if it's already an IP address then that's fine
	// If successful, this places the connection details in the serverIP object.
	int hostResolved = SDLNet_ResolveHost(&serverIP, serverHostname.c_str(), serverPort);
	// If we couldn't resolve the hostname then throw an error
	if (hostResolved == -1)
	{
		failedCommunication = true;
		string msg = "Error: Failed to resolve the server hostname to an IP address.";
		SocketException e(msg);
		throw e;
	}
	else // otherwise if we successfully resolved the hostname...
	{
		failedCommunication = false;
		// ...get our IP address in dot-quad format by breaking up the 32-bit unsigned host address
		// and splitting it into an array of four 8-bit unsigned numbers...
		Uint8 * dotQuad = (Uint8*)&serverIP.host;
		dotQuadString  = toString( (unsigned short)dotQuad[0] );
		dotQuadString += ".";
		dotQuadString += toString( (unsigned short)dotQuad[1] );
		dotQuadString += ".";
		dotQuadString += toString( (unsigned short)dotQuad[2] );
		dotQuadString += ".";
		dotQuadString += toString( (unsigned short)dotQuad[3] );
		//... and then outputting them. Then read the last 16 bits of the serverIP object to get the port number
	}

	// Try to open a connection between the client and the server - quit out if we can't connect
	clientSocket = SDLNet_TCP_Open(&serverIP);
	if (!clientSocket)
	{
		failedCommunication = true;
		string msg = "Error: Failed to open connection to server: ";
		msg += SDLNet_GetError();
		SocketException e(msg);
		throw e;
	}
	else // If we successfully opened a connection then check for the server response to our connection
	{
		failedCommunication = false;
		// Add our socket to the socket set for polling
		SDLNet_TCP_AddSocket(socketSet, clientSocket);

		// Wait for up to five seconds for a response from the server.
		// Note: If we don't check the socket set and WAIT for the response, we'll be checking before the
		// server can respond, and it'll look as if the server sent us nothing back!
		int activeSockets = SDLNet_CheckSockets(socketSet, ClientSocket3::CONNECTION_TIMEOUT_PERIOD);

		// Check if we got a response from the server
		int gotServerResponse = SDLNet_SocketReady(clientSocket);
		if (gotServerResponse != 0)
		{
			// Read the message on the client socket
			int serverResponseByteCount = SDLNet_TCP_Recv(clientSocket, pBuffer, bufferSize);
			// Get the contents of the buffer as a string
			string bufferContents = pBuffer;
			// If we got the SERVER_NOT_FULL response from the server then we can join!
			if ( pBuffer == ClientSocket3::SERVER_NOT_FULL )
			{
//
			}
			else // Otherwise we must have got the SERVER_FULL response so we can't.
			{
				failedCommunication = true;
				string msg = "Error: Server is full...";
				SocketException e(msg);
				throw e;
			}
		}
		else // If there's no activity on the client socket then we've failed to connect
		{
			failedCommunication = true;
			string msg = "Error: No response from server: ";
			msg       += serverHostname;
			msg       += " at IP: ";
			msg       += dotQuadString;
			msg       += " on port ";
			msg       += serverIP.port;
			SocketException e(msg);
			throw e;
		}

	} // End of if we managed to open a connection to the server condition
	failedCommunication = false;
//	std::cout << "Communication success\n";
}

#ifdef DEV
// Function to check for any incoming messages
string ClientSocket3::checkForIncomingMessages()
{
	// Define a string with a blank message
	string receivedMessage = "";

	if (failedCommunication == true){
		return receivedMessage;
	}
	// Poll for messages for a specified time (default: 10ms, so 100 times per second)
	int activeSockets = SDLNet_CheckSockets(socketSet, ClientSocket3::SOCKET_SET_POLL_PERIOD);
	// This produces a LOT of debug output, so only uncomment if the code's really misbehaving...
	//if (debug) { cout << "There are " << activeSockets << " socket(s) with data on them at the moment." << endl; }
	if (activeSockets != 0)
	{
		// Check if we got a message from the server
		int gotMessage = SDLNet_SocketReady(clientSocket);
		if (gotMessage != 0)
		{
			int serverResponseByteCount = SDLNet_TCP_Recv(clientSocket, pBuffer, bufferSize);

			std::cout << std::endl << "Got message: " << pBuffer << " (" << serverResponseByteCount << " bytes)" << std::endl;

			if (serverResponseByteCount != 0)
			{
				receivedMessage = toString(pBuffer);
			
				// If we've received the shutdown signal set the flag appropriately
				if (receivedMessage == ClientSocket3::SHUTDOWN_SIGNAL)
				{
					shutdownClient = true;
				}
			}
			else // If we've received a 0 byte message from the server then we've lost the connection!
			{
				failedCommunication = true;
				// ...generate a suitable error message...
				string msg = "Lost connection to the server!";
				// ...and then throw it as an exception!
				SocketException e(msg);
				throw e;
			}
		} // End of if (gotMessage != 0) section
	} // End of if (activeSockets != 0) section
	// Return the message, whether the actually is a message, or whether it's blank
	return receivedMessage;
}
#endif

#ifdef DEV
// Function do display a received message and then blank the message
void ClientSocket3::displayMessage(string &receivedMessage)
{
	// Display the message and then...
//	cout << endl << "Received: " << receivedMessage << endl;
	// Blank it! Because we pass a reference to a string into this function
	// it's the actual receivedMessage that's blanked and not just a copy
	receivedMessage = "";
}
#endif
// Function to get user input in a non-blocking manner
void ClientSocket3::sendCommand( char *stringCommand )
{
	if (failedCommunication == true){
#ifndef WITHOUT_SDL
		SDL_Delay(9);
#endif
		return;
	}
	inputLength = strlen(stringCommand) + 1;
//	{
	// ...attempt to send the message to the server
		if (SDLNet_TCP_Send(clientSocket, (void *)stringCommand, inputLength) < inputLength)
		{
			//std::cout << "AAAAAAAARGH !!!\n";
			std::cout << "inputLength  : " << inputLength << ", ";
			std::cout << "stringCommand: " << stringCommand << "\n";
			string msg = "Error: Failed to send message: ";
			msg += SDLNet_GetError();
			SocketException e(msg);
			throw e;
		}
#ifndef WITHOUT_SDL
		SDL_Delay(9);	// ESSENTIAL, for sync()
#endif
}

// Function to return the shutdownStatus, used by our main loop
//bool ClientSocket3::getShutdownStatus()
//{
//	return shutdownClient;
//}


// ######################################################################### //
// ######################################################################### //
// ######################################################################### //
// ######################################################################### //
// ######################################################################### //
// ######################################################################### //



#define WRITE_LOG_BUF_SIZE 512
void ClientSocket3::wd_log(const char *format, ...)
{
	char buffer[WRITE_LOG_BUF_SIZE + 77];
	va_list parms;
	int count = 0;
	va_start(parms, format);
	count = _vsnprintf(buffer, WRITE_LOG_BUF_SIZE - 1, format, parms);
	//	MessageBox((HWND) nullptr, (LPCTSTR)buffer, (LPCTSTR) "=== main ===", MB_OK);
	/*
	for (int i = 0; i < 70; i++){
		wd_plotBinary(i);
		wd_flush();
	}
	*/
	wd_sendTextLines( buffer );
	wd_flush();
	va_end(parms);
}




// ######################################################################### //
// ######################################################################### //
// ######################################################################### //
// ######################################################################### //
// ######################################################################### //


void ClientSocket3::wd_BEGIN()
{
	if (failedCommunication == true){
//		return;
	}
//	failedCommunication == false;
	connectToServer();// Attempt to connect to the server at the provided address and port
	string receivedMessage = "";
	// TODO, if connected or not
}


void ClientSocket3::wd_END()
{
	if (failedCommunication == true){
		return;
	}
	SDLNet_Quit();	// Shutdown SDLNet - our ClientSocket3 will clean up after itself on destruction
}

void ClientSocket3::wd_sendInteger(int i){
	char buffer[32];
	sprintf_s(&buffer[0], 15, "A%d\0", i);
	wd_queueCommand(buffer);
}
void ClientSocket3::wd_sendIntegerX(int i){
	char buffer[32];
	sprintf_s(&buffer[0], 15, "B%d\0", i);
	wd_queueCommand(buffer);
}
void ClientSocket3::wd_plotRGB(int _red, int _green, int _blue){
	char buffer[32];
	_red &= 255;
	_green &= 255;
	_blue &= 255;
	sprintf_s(&buffer[0], 25, "C%0.2X%0.2X%0.2X", _red, _green, _blue);
	wd_queueCommand(buffer);
}
void ClientSocket3::wd_sendText(char *text){
	char buffer[4096];
	sprintf_s(&buffer[0], 4090, "D%s\0", text);
	wd_queueCommand(buffer);
}
void ClientSocket3::wd_sendTextLines(char *text){
	char buffer[4096];
	sprintf_s(&buffer[0], 4090, "E%s\0", text);
	wd_queueCommand(buffer);
}
void ClientSocket3::wd_plotXY(int itx, int ity, int color){// if color == 0, it means clear drawing box
	char hexchars[] = "0123456789ABCDEF";
	char buffer[32]; // = { 'E', 0 };
	int _c = color & 15;
	int _x = itx & 255;
	int _y = ity & 255;
	if (color == 0){ // reset
		sprintf_s(&buffer[0], 15, "F00000");	// ?
//		sprintf_s(&buffer[0], 15, "F0000");	
	}
	else{
		sprintf_s(&buffer[0], 15, "F%X%0.2X%0.2X", _c, _x, _y);
	}
	wd_queueCommand(buffer);
}
void ClientSocket3::wd_plotBinary(int i){
	char buffer[32];
	sprintf_s(&buffer[0], 15, "G%d\0", i);
	wd_queueCommand(buffer);
}

void ClientSocket3::wd_queueCommand(char *baffer)// queue one command at a time
{
	int incomingSize = strlen(baffer);
	strcpy_s(&sdestinationLine[begin], 4090, baffer);
	sdestinationLine[begin + incomingSize] = ':';
	sdestinationLine[begin + incomingSize + 1] = '\0';
	begin += incomingSize + 1;
	if (incomingSize>4000 || begin>4000)  wd_flush();
}

void ClientSocket3::wd_flush()
{
	int size = strlen(sdestinationLine);
	if (size == 0) return;
	sdestinationLine[4090] = 0;
	sendCommand(&sdestinationLine[0]);
	begin = 0;	// std::cout << "size : "<< size << ", line  = '" << (sdestinationLine) << "\n";
}



// ######################################################################### //
// ######################################################################### //
// ######################################################################### //
// ######################################################################### //
// ######################################################################### //






