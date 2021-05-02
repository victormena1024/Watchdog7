
#include "LowLevel.h"
#include <cstring>


LowLevel::LowLevel(){}
LowLevel::~LowLevel(){ SDL_FreeSurface (privateSurface); }
//
//
// 
LowLevel::LowLevel(
	bool _active,
	bool _activateOnlyOnce,
	int _type, int _index, 
	int _positionX, int _positionY, int _sizeX, int _sizeY,
	int _positionX2, int _positionY2, int _sizeX2, int _sizeY2
	)
{
	active = _active;
	activateOnlyOnce = _activateOnlyOnce;
	type = _type;
	index = _index;
	positionX = _positionX;
	positionY = _positionY;
	sizeX = _sizeX;
	sizeY = _sizeY;
	positionX2 = _positionX2;
	positionY2 = _positionY2;
	sizeX2 = _sizeX2;
	sizeY2 = _sizeY2;
	privateSurface = ima->createSurface( sizeX, sizeY );
	if( sizeX2 !=0 && sizeY2 !=0 )
	privateSurface2 = ima->createSurface(sizeX2, sizeY2);
}

#ifdef NEIVERR
void LowLevel::executeServerCommand( int type, int index, char *_incomingString )
{
	if (privateSurface == nullptr) return;
	int x=0, y=0;

	_incomingString = "123,199";

	char * cstr = new char[ strlen(_incomingString) + 1];
	std::strcpy(cstr, _incomingString );
	sscanf( cstr, "%d,%d", &x, &y);
	ima->print(privateSurface, 0, 0, cstr);
	//	void print2(SDL_Surface *surf, int x, int y, char *text);	// display fixed b/w 16x16 text onto surface
	//scratchpadSurface
	//print_configureTextOutputColors(SDL_Color foregroundColor, SDL_Color backgroundColor);
//	ima->print(scratchpadSurface, x, y, _incomingStringc);
//	ima->print(mainDisplaySurface, x, y, _incomingString);
/*
	static void print(SDL_Surface *surf, int x, int y, char *text);	// display fixed b/w 8x8 text onto surface
	void print2(SDL_Surface *surf, int x, int y, char *text);	// display fixed b/w 16x16 text onto surface
	static void printf(SDL_Surface *surf, int x, int y, char *text, ...); // print formatted text
	void printf2(SDL_Surface *surf, int x, int y, char *text, ...); // print formatted text
	void print_configureTextOutputColors(SDL_Color foregroundColor, SDL_Color backgroundColor);
*/
//	sscanf(incomingString, "%d", &rotation);
//	sscanf(incomingString, "%d,%d", &argumentX, &argumentY);
//	comandos->executeCommandA(argumentX, argumentY);
//	ima->putblock(mainScratchpadSurface, x, y, 0xff776644, 4);
	//ima->putpixel(mainScratchpadSurface, positionX, positionY, 0xffaa9977);
	ima->drawrectWH(privateSurface, 0, 0, width, height);
//	mainDisplayTexture =
/*
	mScratchpadSurface;
	SDL_RenderCopy(mainDisplayRenderer, mBitmapTexture, &srcrect, &dstrect);
	SDL_RenderPresent(mRenderer);
	SDL_Surface  *mainDisplaySurface = nullptr; // the screen to draw onto, (big box)
	SDL_Texture  *mainDisplayTexture = nullptr; // the screen to draw onto, (big box)
	SDL_Renderer *mainDisplayRenderer = nullptr; // the screen to draw onto, (big box)
	SDL_Window	 *mainDisplayWindow = nullptr; // the screen to draw onto, (big box)
*/
}


// blit small display box into big screen
SDL_Surface *LowLevel::displayServerCommand()
{
	if (privateSurface == nullptr) return nullptr;
	SDL_Color colour1 = {240,200,180};
//	ima->fillSurface(mScratchpadSurface, colour1);
	ima->drawrectWH(privateSurface, 0, 0, privateSurface->w, privateSurface->h);
//	mainDisplayTexture = (SDL_Texture*)SDL_CreateTextureFromSurface(mainDisplayRenderer, mScratchpadSurface);
//	ima->drawrectWH(scratchpadSurface, 0, 0, width, height);
//	SDL_Surface *mainDisplaySurface = nullptr; // the screen to draw onto, (big box)
//	SDL_Texture *mainDisplayTexture = nullptr; // the screen to draw onto, (big box)
	//mScratchpadSurface
	//  ******* ima->blitSurface( source, destination )
	// do: copy into mScratchpadSurface 
//	ima->blitSurface( mScratchpadSurface, mainDisplaySurface, positionX, positionY);
	return privateSurface;
}
#endif


