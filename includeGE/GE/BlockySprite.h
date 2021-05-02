#ifndef BLOCKYSPRITE_H
#define BLOCKYSPRITE_H

#include <sdl.h>
#include "GE/Sprite.h"
#include "Imageutils.h"


namespace play{

	class BlockySprite : Sprite
	{
	public:
		BlockySprite();
		~BlockySprite();
	
		// Two constructors for creating ghosts only
		BlockySprite(char *_spriteName, float x, float y, int w, int h);


		float getLocalDX(void);
		float getLocalDY(void);


		void renderSelf();
		bool isGhost(void);
		// copy operator override
		BlockySprite& operator=(const BlockySprite &other);
		
		// other
		void tick(void);

		void  setW(int);
		void  setH(int);
		float getW(void);
		float getH(void);

		// ghost
		void setColor(int, int, int,int);
		void randomizeColor(void);

//protected:
private:
		int	  aspr_w, aspr_h;
		float   aspr_x, aspr_y;
		int	  ghostR, ghostG, ghostB, ghostA;
		Uint32 ghostColor;
		float localDX;			//
		float localDY;			//
        snaf::Imageutils *ima;
		bool  visibleFlag = true;
		bool debugDisplayRect=false;
		bool debugDisplayName=false;
		float	globalDisplacementX=0, globalDisplacementY=0;
	};
}
#endif