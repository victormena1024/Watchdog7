#ifndef DERIVEDINPUTEVENTLISTENER_H
#define DERIVEDINPUTEVENTLISTENER_H



#include "GameEngine/InputEventListener.h"
#include "GameEngine/Sprite.h"
//#include "GameEngine/Imageprocessor.h"

//#ifdef __cplusplus
//extern "C" {
//#endif


class DerivedInputEventListener : public play::InputEventListener
{
public:
	DerivedInputEventListener();
	~DerivedInputEventListener();

	bool onMainEvent(SDL_Event*);
	void onQuit();
	bool onKeyboardUp(int);
	bool onKeyboardDown(int);
	bool onMouseMotion(int, int, int, int, Uint8);
	bool onMouseClick(int, int, Uint8);
	bool onMouseUnclick(int, int, Uint8);
	bool onJoystick(       int, Uint8, Sint16 );
	bool onJoystickKeyUp(  int, Uint8, Uint8  );
	bool onJoystickKeyDown(int, Uint8, Uint8  );
	
	/*
	Joystick data:
	eve.jaxis.which,   // the instance of the joystick
		eve.jaxis.axis,	// index of axis (x(0) or y(0)), uint8
		eve.jaxis.value	// -32768 to +32768,  Sint16
		*/

	/*

SDL_JoystickID		which
		the instance id of the joystick that reported the event
		Uint8		button
		the index of the button that changed
		Uint8		state
		the state of the button; SDL_PRESSED or SDL_RELEASED
		*/
};

//#ifdef __cplusplus
//}
//#endif



#endif
