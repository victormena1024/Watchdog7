#ifndef SERVERCOMMANDS_H
#define SERVERCOMMANDS_H

#include "SDL.h"
#include <vector>
#include <iostream>
#include <string>
#include <GE/ImageUtils.h>

class LowLevel
{
public:
	LowLevel();	// initiate empty default values

	// _incomingString is the maximum string size on input here
	LowLevel(
		bool active,
		bool _activateOnlyOnce,
		int type, int index,
		int positionX, int positionY, int sizeX, int sizeY,
		int _positionX2, int _positionY2, int _sizeX2, int _sizeY2
	);

	~LowLevel();
	//
	bool active;		// bool, active or inactive
	bool activateOnlyOnce = false;
	int type;		// type from 'A' to 'Z'
	int index;		// 0 to 27
	int positionX;		// position x
	int positionY;		// position y
	int sizeX;			// width
	int sizeY;			// height
	//
	int positionX2;		// position x
	int positionY2;		// position y
	int sizeX2;			// width
	int sizeY2;			// height
	//
	SDL_Surface  *privateSurface  = nullptr; // the local screen to draw onto, (small box)
	SDL_Surface  *privateSurface2 = nullptr; // the secondary local screen to draw onto, (small box)
	//
private:
	//
	snaf::Imageutils *ima = new snaf::Imageutils();
	//
};



#endif


