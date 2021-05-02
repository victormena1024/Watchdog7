#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

//#ifdef __cplusplus
//extern "C" {
//#endif

#include <SDL.h>
#include "GE/InputEventListener.h"

namespace play{
	class InputHandler
	{
	public:
		InputHandler();
		~InputHandler();
		void registerInputListener(InputEventListener *newListener);

		bool executeEventLoop();

	private:
		InputEventListener * listener;
	};
}

//#ifdef __cplusplus
//extern "C" {
//#endif

#endif