#ifndef CONSTRAINT_H
#define CONSTRAINT_H

#include <cstdio>
#include <cstdlib>


namespace play{

class Constraint
{
public:

	enum ACTION { NOTHING, STOP, WRAP, BOUNCE, DIE };	// constraint action

	Constraint( bool(*myfunc)(Constraint*, void *, bool, bool, bool, bool) );
	~Constraint();
	Constraint& operator=(const Constraint &other);	// copy operator override

	// the sprite is passed on to the callback function
	bool check(
		float &x1,	
		float& y1,
		float& x2,	
		float& y2,
		float& deltax,
		float& deltay,
		float& width,
		float& height,
		bool& isMovable,
		bool& isAlive,
		bool& isSuicide,
		void *sprite);

	// ************************ CONSTRAINT ************************. //
	void setAction(ACTION action);			// set action to execute when sprite reaches constraint limit. 
	void setLimitsXYWH(float x, float y, float w, float h);
	void setLimitsX1Y1X2Y2(float x1, float y1, float x2, float y2);
	void getLimitsXYWH(float& x, float& y, float& w, float& h);
	void getLimitsX1Y1X2Y2(float& x1, float& y1, float& x2, float& y2);
	void setFlags(bool x1, bool y1, bool x2, bool y2);
	void getFlags(bool& x1, bool& y1, bool& x2, bool& y2);
	void enable();
	void enable(float x1, float y1, float x2, float y2);
	void disable();
	bool isEnable(void);
	void setCallback( bool(*myc)(Constraint*, void *, bool, bool, bool, bool) );
	// ************************ CONSTRAINT ************************. //

//	void SetCallback(bool(*myCallBack)(Constraint *, void*, bool, bool, bool, bool));
//	void Enable(float x1, float y1, float x2, float y2);
//	void Disable();






private:
	// 
	// ************************ CONSTRAINT ************************. //
	bool (*myCallback)(Constraint *, void *,bool,bool,bool,bool);
	bool constraintFlag;		// if movement constraints are enabled or disabled
	float constraintX=0.0f;
	float constraintY=0.0f;
	float constraintW=1.0f;
	float constraintH=1.0f;
	bool constraintFlagX1 = false;
	bool constraintFlagY1 = false;
	bool constraintFlagX2 = false;
	bool constraintFlagY2 = false;
	ACTION constraintAction = NOTHING;
	// ************************ CONSTRAINT ************************. //


};	// class

}//namespace

#endif