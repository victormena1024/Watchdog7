
#include "ClientSocket2.h"

// Static constants
const std::string  ClientSocket::SERVER_NOT_FULL           = "OK";        // Server's response when there are free spots a client can join
const std::string  ClientSocket::SERVER_FULL               = "FULL";      // Server's response when there are no free spots, so a client cannot join
//const std::string  ClientSocket::SHUTDOWN_SIGNAL           = "/shutdown"; // What you type to shutdown the server
const std::string  ClientSocket::SHUTDOWN_SIGNAL			= "/s"; // What you type to shutdown the server
const std::string  ClientSocket::QUIT_SIGNAL               = "/quit";     // What you type to shutdown the client
const unsigned int ClientSocket::CONNECTION_TIMEOUT_PERIOD = 5000;        // 5 second connection timeout
const unsigned int ClientSocket::SOCKET_SET_POLL_PERIOD    = 10;          // 10ms, so poll 100 times/second

// ClientSocket constructor
ClientSocket::ClientSocket(string theServerAddress, unsigned int theServerPort, unsigned int theBufferSize)
{
	debug          = true;      // Flag to control whether to output debug info
	shutdownClient = false;     // Flag to control whether it's time to shut down the client
	// The host name of the server.
	// This can be either a dot-quad like 127.0.0.1 or a hostname like "localhost" or "foo.com" etc.
	serverHostname = theServerAddress;
	serverPort = theServerPort; // The port on the server to connect to
	bufferSize = theBufferSize; // The maximum message size
	inputLength = 0;
	try
	{
		pBuffer = new char[bufferSize]; // Create the transmission buffer character array
		// Create a socket set big enough to hold the server socket and our own client socket
		socketSet = SDLNet_AllocSocketSet(2);
		// If we couldn't create the socket set then throw an exception
		if (socketSet == NULL)
		{
			string msg = "Failed to allocate the socket set in ClientSocket constructor: ";
			msg += SDLNet_GetError();
			SocketException e(msg);
			throw e;
		}
	}
	catch (SocketException e)
	{
		// Re-throw the exception to be dealt with appropriately elsewhere
		throw e;
	}

} // End of ClientSocket constructor

// ClientSocket destructor
ClientSocket::~ClientSocket()
{
	// Close our server and client sockets
	SDLNet_TCP_Close(serverSocket);
	SDLNet_TCP_Close(clientSocket);
	// Free our socket set (i.e. all the clients in our socket set)
	SDLNet_FreeSocketSet(socketSet);
	// Release any properties on the heap
	delete pBuffer;
}

void ClientSocket::connectToServer()
{
	// Try to resolve the hostname to an IP address, if it's already an IP address then that's fine
	// If successful, this places the connection details in the serverIP object.
	int hostResolved = SDLNet_ResolveHost(&serverIP, serverHostname.c_str(), serverPort);
	// If we couldn't resolve the hostname then throw an error
	if (hostResolved == -1)
	{
		string msg = "Error: Failed to resolve the server hostname to an IP address.";
		SocketException e(msg);
		throw e;
	}
	else // otherwise if we successfully resolved the hostname...
	{
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
		string msg = "Error: Failed to open connection to server: ";
		msg += SDLNet_GetError();
		SocketException e(msg);
		throw e;
	}
	else // If we successfully opened a connection then check for the server response to our connection
	{
		// Add our socket to the socket set for polling
		SDLNet_TCP_AddSocket(socketSet, clientSocket);

		// Wait for up to five seconds for a response from the server.
		// Note: If we don't check the socket set and WAIT for the response, we'll be checking before the
		// server can respond, and it'll look as if the server sent us nothing back!
		int activeSockets = SDLNet_CheckSockets(socketSet, ClientSocket::CONNECTION_TIMEOUT_PERIOD);

		// Check if we got a response from the server
		int gotServerResponse = SDLNet_SocketReady(clientSocket);
		if (gotServerResponse != 0)
		{
			// Read the message on the client socket
			int serverResponseByteCount = SDLNet_TCP_Recv(clientSocket, pBuffer, bufferSize);
			// Get the contents of the buffer as a string
			string bufferContents = pBuffer;
			// If we got the SERVER_NOT_FULL response from the server then we can join!
			if ( pBuffer == ClientSocket::SERVER_NOT_FULL )
			{
//
			}
			else // Otherwise we must have got the SERVER_FULL response so we can't.
			{
				string msg = "Error: Server is full...";
				SocketException e(msg);
				throw e;
			}
		}
		else // If there's no activity on the client socket then we've failed to connect
		{
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
}


// Function to check for any incoming messages
string ClientSocket::checkForIncomingMessages()
{
	// Define a string with a blank message
	string receivedMessage = "";
	// Poll for messages for a specified time (default: 10ms, so 100 times per second)
	int activeSockets = SDLNet_CheckSockets(socketSet, ClientSocket::SOCKET_SET_POLL_PERIOD);
	// This produces a LOT of debug output, so only uncomment if the code's really misbehaving...
	//if (debug) { cout << "There are " << activeSockets << " socket(s) with data on them at the moment." << endl; }
	if (activeSockets != 0)
	{
		// Check if we got a message from the server
		int gotMessage = SDLNet_SocketReady(clientSocket);
		if (gotMessage != 0)
		{
			int serverResponseByteCount = SDLNet_TCP_Recv(clientSocket, pBuffer, bufferSize);

			std::cout << endl << "Got message: " << pBuffer << " (" << serverResponseByteCount << " bytes)" << endl;

			if (serverResponseByteCount != 0)
			{
				receivedMessage = toString(pBuffer);
				// If we've received the shutdown signal set the flag appropriately
				if (receivedMessage == ClientSocket::SHUTDOWN_SIGNAL)
				{
					shutdownClient = true;
				}
			}
			else // If we've received a 0 byte message from the server then we've lost the connection!
			{
				// ...generate a suitable error message...
				string msg = "Lost connection to the server!";
				// ...and then throw it as an exception!
				SocketException e(msg);
				throw e;
			}
		} // End of if (gotMessage != 0) section
	} // End of if (activeSockets != 0) section
	// Return the message, whether the actually is a message, or whether it's blank
// std::cout << "receivedMessage;  '"<< receivedMessage<<"' \n";

	return receivedMessage;
}
//#endif

// Function do display a received message and then blank the message
void ClientSocket::displayMessage(string &receivedMessage)
{
	// Display the message and then...
//	cout << endl << "Received: " << receivedMessage << endl;
	// Blank it! Because we pass a reference to a string into this function
	// it's the actual receivedMessage that's blanked and not just a copy
	receivedMessage = "";
}




// Function to get user input in a non-blocking manner
void ClientSocket::sendCommand( char *stringCommand )
{
	inputLength = strlen(stringCommand) + 1;
//	if (userInput != ClientSocket::QUIT_SIGNAL)
//	{
	//SDL_Delay(21);
	// ...attempt to send the message to the server
		if (SDLNet_TCP_Send(clientSocket, (void *)stringCommand, inputLength) < inputLength)
		{
			std::cout << "AAAAAAAARGH !!!\n";
			std::cout << "inputLength  : " << inputLength << ", ";
			std::cout << "stringCommand: " << stringCommand << "\n";
			string msg = "Argh...Error: Failed to send message: ";
			msg += SDLNet_GetError();
			SocketException e(msg);
			throw e;
		}
		//SDL_Delay(9);	// ESSENTIAL, for sync()
		SDL_Delay(1);

}

// Function to return the shutdownStatus, used by our main loop
bool ClientSocket::getShutdownStatus()
{
	return shutdownClient;
}



