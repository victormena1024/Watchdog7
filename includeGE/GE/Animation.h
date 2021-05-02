#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL.h>
#include <vector>
//#include <cstdarg>
//#include <iostream>
//#include "GameEngine/Loader.h"
#include "Imageutils.h"

namespace play{

	class Animation
	{
	public:

		enum { LOOP, PINGPONG, ONESHOT, ONESHOTDELETE };

		Animation(char *name,bool _copyFullPixels);
		~Animation(void);
		//
		void addSurfaceDxDy(SDL_Surface *m, float _dx, float _dy); // push surface and displacement on vector
		//
		void setAnimationStyle( int mStyle ); // LOOP, PINGPONG, ONESHOT, ONESHOTDELETE
		int  getAnimationStyle();
		//
		void setFullCopyFlag(bool status);	// using blit to copy instead of reference
		//
		void  setDisplacementX(float _dx);
		void  setDisplacementY(float _dy);
		float getDisplacementX();
		float getDisplacementY();
		//
		SDL_Surface* getCurrentSurface();
		SDL_Surface* getFirstSurface();
		SDL_Surface* getLastSurface();
		//
		int	getNumberOfSurfaces(void); // number of surfaces.
		//
		char *getName(void);		// get textual name for this Animation
		void setName(char*);		// set name for this Animation
		void setTypeOfAlignment(int);		// from 1 to 9, set type AND align.
		int  getTypeOfAlignment(void);		// from 1 to 9 (default is 1, unaligned)
		//
		// these functions returns adjusted indexes.
		int  goIndex(int);		// set current index to position given.
		int  goFirst(void);		// go to first in array
		int  goNext(void);		// advance automatically, wrap automatically
		int  goPrev(void);		// advance automatically, wrap automatically
		int  goLast(void);		// go to last in array
		//
		//
		void setDelay(int);			// 0 means no delay (default)
		void setSpeed(float);		// 0.0 to 1.0 means less than one frame per tick, else more than one tick
		void reverseDirection(void);//
		void setDirection(bool);	// true means forward animation
		bool getDirection(void);	// true means forward animation
		bool isTimeForAutoDelete(void);	// if setOneshotAutoDelete() has been ordered, returns true on animation ended.
		//
		void tick(void);		// take care of animating frames
		//
		void reset(void);		// reset animation parameters. directionFlag is not changed
		//
		// copy operator
		Animation& operator=(const Animation& other);
		Animation* copyImage(Animation *source);

		void debugPrint();
		void setDebug(bool debugFlag);
		std::vector<SDL_Surface*> getAllSurfaces();
		// -------------------
		void *getUserData(void);
		void setUserData(void *usr);
		// -------------------
		void pauseOn();
		void pauseOff();
		//
	private:
		void privateForwardCurrentFrame();
		void privateBackwardCurrentFrame();
		void privateAdjustCurrentFrameToLimits();

		void privateAnimAdjustAxis(int alignment);		// calculate new displacements to justify alignment requirements.			
		void privateAnimAdjustX(bool middle_x);
		void privateAnimAdjustY(bool middle_y);
		//DATA
		int style;				//		AnimationStyle style;
		char animationName[256];	// textual name for this Animation, used to identify the kind of animation it is.
		int alignment;			// from 1(default) to 9
		std::vector<SDL_Surface*> surfaces;		// Array 
		std::vector<float>displacementX;		// dynamic array. for offseting Images x. so all the Images will be centered with frame 0
		std::vector<float>displacementY;		// dynamic array. for offseting Images y. so all the Images will be centered with frame 0	
		//
		int  delayCounter;		// counter down from 'delayTicks' to 0.
		int  delayTicks;		// contains how many ticks of delay we use.
		float speed = 1.0f;		// animation speed
		float currentFrame = 0.0f;		// current frame index for retrieving surfaces
		//
		bool animationEndedFlag;// true on end of animation
		bool runOneMoreTick;	// true on end of animation
		bool directionFlag;		// true = forward (default). false = backward. 
		bool debugFlag;			// textual output if true
		//
		void *userData = nullptr;
		bool pauseAnimationFlag = false;
		snaf::Imageutils *ima = nullptr;

		bool copyFullPixels = false;	// copy and allocate all pixels, // TODO, make it selectable
//


	};
}//namespace


#endif
