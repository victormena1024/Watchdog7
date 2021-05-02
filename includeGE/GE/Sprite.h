#ifndef SPRITEBV_H
#define SPRITEBV_H


#include <vector>

#include "GE/Animation.h"
#include "GE/ImageProcessor.h"
#include "GE/TimerListener.h"
#include "GE/Imageutils.h"
#include "GE/Constraint.h"


namespace play{

class Sprite
	{
	public:
		~Sprite(void);
		Sprite(void);
		Sprite(char *spriteName);

		void renderSelf();

		// copy operator override
		Sprite& operator=(const Sprite&);

		// statisk metod
		static Sprite* copySpriteWithReference(Sprite *source);
		static Sprite* copySpriteWithBlitAllocation(Sprite *source);

		// other
		void tick(void);		// do movement, do visibility, increment self-timer
		void animTick(void);
		void movementTick(void);
		void constraintTick(void);

		// this function is called repeadtely when number of 'ticks' have passed
		// 
		void setTickerFunction(void(*myfunc)(Sprite *self), int ticks);
		void tickerTick();	// called from tick()




		
		bool		addAnimation(Animation *imag);	// add Animation to this sprite, return false on error
		//
		Animation*	getAnimation(char *name);		// get a named Animation based on name, "up", "down", "left", "right", etc.
		Animation*  getAnimation(int index);		// select Animation based on index
		Animation*	getAnimation();					// select current Animation
		//														//
		int getAnimationMaxIndex();			// maximum index of animations for  this sprite
		int getAnimationMaxSize();			// maximum index of animations for  this sprite

		void animReset(void);					// 
		void debugDumpAnimationNames();			// debug output

		float getLocalDX(void);
		float getLocalDY(void);

		float getW();
		float getH();
	
		ImageProcessor* getImageProcessor();
		
		void debugOn();
		void debugOff();
		bool isDebug();


// ** constraint functions ** //
		Constraint * getConstraint();
// ** constraint functions ** //


		// -------------------
		void *getUserData(void);
		void setUserData(void *usr);
		float getUserDataFloat(void);
		void setUserDataFloat(float usr);
		// -------------------

		int  getUniqueID();
		void setUniqueID(int);
		char *getName(void);
		void setName(char*);
		void debugPrint();
		bool isAlive(void);
		void setAlive(bool);


		// coordinates	
		void  setX(float);
		void  setY(float);
		void  setXY(float, float);
		void  setXY2(float, float);
		void  setX2(float);
		void  setY2(float);
		//
//		virtual float getW(void) = 0;
//		virtual float getH(void) = 0;
		//
		float getX(void);
		float getY(void);
		float getX2(void);
		float getY2(void);
		//
		float getCX(void);			// get center x of sprite
		float getCY(void);			// get center y of sprite
		void  setCX(float);			// set center x of sprite
		void  setCY(float);			// set center y of sprite
		void  setCXY(float, float);	// set center x,y of sprite
		//
//		virtual float getLocalDX(void) = 0;
//		virtual float getLocalDY(void) = 0;
		//
		void  setGlobalDisplacementX(float);
		void  setGlobalDisplacementY(float);
		float getGlobalDisplacementX(void);
		float getGlobalDisplacementY(void);
		int  ticktimerGetValue(void); // increased for every tick()=0;
		void ticktimerSetValue(int);  // increased for every tick()=0;
		void registerTimerListener(TimerListener *timerListener);
		void tickTimer();
		// ** movement functions ** //
		bool isMovable(void);
		void setMovable(bool smf);
		void setSpeed(float s);
		float getSpeed();
		void setDeltaXY(float dx, float dy);
		void setDeltaX(float dx);
		void setDeltaY(float dy);
		float getDeltaX(void);
		float getDeltaY(void);
		// ** movement functions ** //

		// suicide, self deletion
		void suicide(void);
		void suicideSetTimer(int);
		void suicideTick();			// called from tick()
		
		// ghost
		bool isGhost(void);		// unused for now

		// other
		void pause(bool pauseOn);	// pause tick()
		
		void setPauseAnimation(bool _p);
		bool getPauseAnimation();

		// visibility
		//void visibleOn(bool on);
		void setVisible(bool _flag);
		bool getVisible();
		bool isVisible(void);
		// debug

		void  debugdisplayOn(void);		// turn on display a square around sprite object.
		void  debugdisplayOff(void);		// turn off display a square around sprite object.
		void  debugdisplayNameOn(void);	// very useful
		void  debugdisplayNameOff(void);	// very useful
		bool  isDebugdisplay();			// very useful

		void collisionSetHiPrecision(bool p);
		bool isHiPrecisionCollision(void);
		bool isCollidable(void);
		void setCollidable(bool b);
		bool isPixelInside(int bx, int by);
		bool isCollisionWith(Sprite *spr);

		void setFullCopyFlag(bool status);


private:
		// code
		void privateInitialize(char *_spriteName);
		char *pCS(char *input);
		char *pCS(std::string input);
		//	
		// data
		int	tickerTimer=0;		
		int tickerTimerDefaultValue = 0;
		void(*tickerFunction)(Sprite *self);
		// data
		ImageProcessor *imp = nullptr;
        snaf::Imageutils     *ima = nullptr;

		int		currentAnimation;	// 
		std::vector<Animation*> animations;		// multi-animations, contains displacementX and Y for all frames.
		play::Constraint *constraint = nullptr;
		void *userData = nullptr;
		float userDataFloat = 0.0f;
		//
		float deltaX=0, deltaY=0;		// delta movement added to coordinates for each tick.
		float movementSpeed = 1.0f;	// multipled to deltaX, deltaY to scale them before adding them to x,y
		//
		char  spriteName[256];		// 
		int	  uniqueID=0;			// a unique identifier for each sprite
		//
		bool  debuggy = false;
		bool  statusAliveFlag = true;
		bool  visibleFlag = true;				// if this sprite is visible or not
		bool  collisionEnableFlag = true;		// if this sprite participate in collisions if true
		bool  debugFlag = false;		 // used for development.
		bool  debugDisplayRect = true;  // very useful
		bool  debugDisplayName = true;	 // very useful
		bool  movementFlag = true;			// if this sprite is moving or not
		bool  pauseTickFlag = false;		 // if tick() is paused or not
		bool  pauseAnimationFlag = false;	// stop animation if true

		float aspr_x, aspr_y;			// position
		float globalDisplacementX=0;
		float globalDisplacementY=0;
		int   suicide_counter = -1;
		int	  ticktimer=0;		 // increases for each tick();
									 
									 //
		TimerListener *timerListener = nullptr;
		bool copyFullPixels = false;	// copy and allocate all pixels, if true


	// ************* COLLISION  *************. //
		bool  hi_precision_collision_flag=false;	// false is box collision only (default).
		Uint32 collision_criterion=127;		// (SDL_ALPHA_OPAQUE + SDL_ALPHA_TRANSPARENT)/2;
		bool testPrecisionCollision(Sprite *spra, Sprite *sprb, SDL_Rect a, SDL_Rect b);
		// ************* COLLISION  *************. //


};	// class

}	//namespace



#endif
