// server
//
#ifndef COMMANDS_H
#define COMMANDS_H

#include "SDL.h"
#include <list>
#include <vector>
#include <iostream>
#include "LowLevel.h"
#include "GE/Imageutils.h"


class Commands
{
public: 
	Commands();
	~Commands();
	//
	void beginHardware();
	void beginAllocateDefaultPrivateData();		// load defaults
	//
	void executeCommand( int type, char *str );
	//
	void tickExecuteDisplay(void);
	//
	void end(void);
	// ...
	Uint32  joinColorValue2(int r, int g, int b, int a);
//	void   shiftRight1Pixel(SDL_Surface *Image, int offsetX, int offsetX2);

	// ...
	//
	void exeCommandA(LowLevel*, char *);	// wheel
	void exeCommandB(LowLevel*, char *);	// plot x
	void exeCommandC(LowLevel*, char *);	// plot y
	void exeCommandD(LowLevel*, char *);	// text line
	void exeCommandE(LowLevel*, char *);	// plot x,y  pixels
	void exeCommandF(LowLevel*, char *);	// binary display
	void exeCommandG(LowLevel*, char *);	// multi lines text
	//
	void exeCommandZ(LowLevel*, char *);	// ...
	//
	//
	//

private:
	//
	void shiftDataline(LowLevel* lo, SDL_Surface *ss);
	void printDataLine(LowLevel* lo, SDL_Surface *ss, char *str);
	int joinLsbMsb(char p1, char p2);

	bool alreadyInitted = false;
	int delay = 20;
	//
	SDL_Surface  *mainDisplaySurface = nullptr;
	SDL_Texture  *mainDisplayTexture = nullptr;
	SDL_Renderer *mainDisplayRenderer = nullptr;
	SDL_Window	 *mainDisplayWindow = nullptr;
	//
	snaf::Imageutils *ima = new snaf::Imageutils();
	// all server commands
	std::vector<LowLevel*> serverCommandsArray;

};


#endif
