#ifndef TOWER_H
#define TOWER_H
/**
* Tower is a class that "contains" sprites. 
* Each of the sprites that are contained by this class share a common zOrder.
* There is an unique zOrder for each tower.
* Each tower contains an array of sprites that share a common zOrder.
* done: make it possible to identify by a string text.
*
*
*/
#include <SDL.h>
//#include <string>
#include <vector>
//#include <cassert>
//#include <iostream>
#include "GE/Sprite.h"



namespace play{
class Tower
{
public:
	Tower(Sprite *inputPrototypeSprite, char *name);
	~Tower(void);
	//
	// -------------------
	void setUserData(void *usr);
	void *getUserData(void);
	// -------------------
	void debugOn();
	void debugOff();
	bool isDebug();
	//
	bool isAlive();
	void setAlive(bool);
	//
	char *getName();
	void setName(char * newName);
	//
	bool createInstancesFromPrototypeSprite( int howmany );
	//
	void setFullCopyFlag(bool status);
	//
	void killAll(void);		// kill all alive sprites. quick removing by only marking them as "dead".
	void reviveAll(void);	// revive all dead sprites.
	void renderAll(void);	// render all sprites for this tower, on screen.
	void tickAll(void);
	// ... //
	int	getNumberOfSprites();
	int	getNumberOfSpritesAlive();
	int	getNumberOfSpritesDead();
	// ... //					
	Sprite* getSprite(int index);		// should return NULL on "dead"  sprites.
	Sprite *getSprite(char *name);		// should return NULL on not found sprite.
	Sprite *getAndReviveSingleSprite();	// get first dead sprite and revive it.
	//
	void    setFirstAliveSpriteIndex();		//
	Sprite *getNextAliveSprite();	// should return NULL on no more alive sprites.





	// ... //
	// ... //	 
	// ... //
	void debugPrint();

	Sprite *getPrototypeSprite();
	void    setPrototypeSprite(Sprite *inputspr);


private:
	char *pCS(std::string input);
	//
	int		currentSpriteIndex = 0;

	char _towerName[256];	//
	Sprite *prototype = nullptr;		// to copy sprite from, easy copy.
	std::vector<play::Sprite*> sprites;			// all sprites for this tower are stored here.
	bool statusAliveFlag = true;	// 
//	int  aliveSprites;	// how many sprites alive (unused)
//	int  totalSprites;	// total number of sprites (unused)
	bool debugFlag;		//
	//
	void *userData;		// 
	//
	bool copyFullPixels = false;	// copy and allocate all pixels, if true.
};
}
#endif