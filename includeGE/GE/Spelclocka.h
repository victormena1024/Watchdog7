#ifndef SPELCLOCKAh_H
#define SPELCLOCKAh_H
#include <iostream>
// #include "GameEngine/Spelmotor.h"


namespace play{

class Spelclocka
{
public:
	Spelclocka(void);
	Spelclocka(int time, void *, int& returnedHandle );
//	Spelclocka(int, void (*)(Spelmotor *), int&);
	
	~Spelclocka(void);
	int getHandle(void);
	void setTimer(int);
	void resetTimer(void);
	bool isTimer(void);
	void tick(void);
	bool isCallbackNeeded(void);
	void resetCallbackStatus(void);
	char *getCallbackFunc(void);
	void pauseOn(void);
	void pauseOff(void);
	// 
	void setName(std::string name);
	std::string getName();
	// ,,,
private:
	int handle;		// the handle that is assigned this object
	int timer_default;		// timer count.
	int	timer;				// running timer.
	bool timer_flag;		// true on timer out. is reset by is_timer() function call.
	void *callbackfunc;	
	//
	bool time_for_callback;	//
	bool pauseTimeFlag;		//
	// ,,,
	bool aliveFlag;		// dead or alive
	// ,,,
	std::string timerName;
};
}
#endif