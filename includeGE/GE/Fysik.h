/*
* fysik
*/
#ifndef FYSIKH_H
#define FYSIKH_H

#include "GE/Sprite.h"

// #include <iostream>


#define PI (float)3.141592653589793238462

namespace play{
class Fysik
{
public:
	Fysik(void);
	~Fysik(void);
	float degreeToRadians( float degrees );
	float radiansToDegree( float radians );
	//
	void  fromAngleToDirections( float angle, float scalefactor, float& fx, float& fy );
	float getAngle(        Sprite *objekt1, Sprite *objekt2 );
	float inverseGetAngle( Sprite *objekt1, Sprite *objekt2 );
	float distance(        Sprite *objekt1, Sprite *objekt2 );
	//
	float acceleration(float kraft, float massa);
	float strecka(float initialVelocity, float acceleration, float tid);
	float tid(float hastighet, float acceleration);
	float hastighet(float acceleration, float tid);
	float kraft(float massa, float acceleration);
	float kraft2(float G, float massa1, float massa2, float radie);
	float gravitationskonstant(float G, float massa, float radie);


private:
};
} // namespace

#endif
