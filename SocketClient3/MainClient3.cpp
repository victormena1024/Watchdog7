

// Library dependencies:  SDL2.lib ; SDL2_net.lib
//
// SDL2main.lib 

#include <string>
#include <cstdlib>
//#include <SDL_net.h>
#include <SDL.h>
#include <vector>
#include <cassert>
#include <iostream>
#include <fstream>
#include <cstdarg>
#include "watchdogClient3.h"


int main(int argc, char *argv[])
{
	ClientSocket3 *cs = new ClientSocket3("127.0.0.1", 12345, 4096);
	cs->wd_BEGIN();
	for (int i = 0; i < 360; i++){
		cs->wd_sendInteger(i);
		cs->wd_sendIntegerX(i);
		cs->wd_flush();
	}
	cs->wd_END();	//
	return 0;
}

