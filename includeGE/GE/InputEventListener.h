#ifndef INPUTEVENTLISTENER_H
#define INPUTEVENTLISTENER_H

//#ifdef __cplusplus
//extern "C" {
//#endif


#include <SDL.h>

namespace play{
	class InputEventListener
	{
	public:
            InputEventListener();
            ~InputEventListener();

		virtual bool onMainEvent(SDL_Event*) = 0;
		virtual void onQuit() = 0;
		virtual bool onKeyboardUp(int) = 0;
		virtual bool onKeyboardDown(int) = 0;
		virtual bool onMouseMotion(int, int, int, int, Uint8) = 0;
		virtual bool onMouseClick(int, int, Uint8) = 0;
		virtual bool onMouseUnclick(int, int, Uint8) = 0;
		virtual bool onJoystick(int, Uint8, Sint16) = 0;
		virtual bool onJoystickKeyUp(int, Uint8, Uint8) = 0;
		virtual bool onJoystickKeyDown(int, Uint8, Uint8) = 0;
	};
}

//#ifdef __cplusplus
//extern "C" {
//#endif

#endif