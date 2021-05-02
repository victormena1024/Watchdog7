#ifndef TIMERLISTENER_H
#define TIMERLISTENER_H

namespace play{

	class Sprite;

	class TimerListener
	{
	public:
		virtual void onTimerEnd(Sprite* aspr) = 0;
	};
}

#endif