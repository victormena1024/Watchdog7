#ifndef IMAGEPROCESSORx_H
#define IMAGEPROCESSORx_H

#include <vector>
#include <SDL.h>
#include <GE/Animation.h>
// #include <GameEngine/Sprite.h>

namespace play{


class ImageProcessor
{
public:
	ImageProcessor();
	~ImageProcessor();

	ImageProcessor& operator=(const ImageProcessor &other);

	// Animationprocessing while copying surface.... :)
	/*
	process0 = copy with alpha (range: 0 to 1 )
	process1 = lightening on destination(background)
	process2 = values addded to rgb. add light or subtract from colors.
	process3 = random grey scale value on chosen R,G or B channel.
	process4 = From color to greyscale
	process5 = invert chosen color channels, rgb
	process6 = show Animation on non-alpha colors. picture-in-picture, with displacement.
	process7 = draw black lines around sprite, around alpha barriers.
	process8 = colorize all non-alpha pixels with color.
	process9 = add horizontal or vertical lines


	type0:( float alpha )
	set alpha transparency for non transparent pixels, making them transparent.
	alpha value must be between 0.0 to 1.0
	value 0.0 is total invisible, 1.0 total opaque.
	
	type1:( int r, int g, int b )
	add light to destination for each color, red, green, blue, used to create shadows.
	values range from -254 to +254
	example:  red = 0,green=0, blue = -100   will create a yellow back drop

	type2: ( int r, int g, int b )
	add light to source for each color, red, green, blue
	values range from -254 to +254
	example:  red = 0,green=0, blue = -100   will create a yellow image

	type3: (bool r, bool g, bool b)
	One binary value for each rgb if true, then that channel will
	be selected for randomness.

	type4: ()
	convert all-non alpha pixels into greyscale

	type5: (bool r, bool g, bool b)
	invert selected r,g,b channel if true, else not.

	type6: ( Animation *source, float speedX, float speedY )
	The source Animation is drawn on all the non-alpha pixels.
	speedX and speedY is the speed to shift the picture-in-picture.
	speed can be positive or negative.
	It is possible to create a scroll effect with this function.

	type7: (int red,int green,int blue)	
	red,green,blue, = which color to outline with.
	draws outlines pixels between alpha and non-alpha pixels

	type8: (int r, int g, int b)
	All non-alpha pixels will be given this r,g,b color.

	type9: (bool horizontal, bool vertical)
	draw horizontal or vertical lines on all non-alpha pixels.

	*/



	 bool isImageprocess(void);
	 void ImageprocessOn();
	 void ImageprocessOff();
	 void ImageprocessType0Set(float alpha);
//	 void ImageprocessType1Set(float red, float green, float blue);
	 void ImageprocessType1Set(int red, int green, int blue);
	 void ImageprocessType2Set(float red, float green, float blue);
	 void ImageprocessType3Set(bool red, bool green, bool blue);
	 void ImageprocessType4Set();
	 void ImageprocessType5Set(bool red, bool green, bool blue);
	 void ImageprocessType6Set(SDL_Surface *source, float speedX, float speedY); //speed may be either positive or negative
	 void ImageprocessType6Set(Animation *source, float speedX, float speedY); //speed may be either positive or negative
	 void ImageprocessType7Set(int red, int green, int blue);
	 void ImageprocessType8Set(int red, int green, int blue);
	 void ImageprocessType9Set(bool horizontal, bool vertical);

	 void ImageprocessType0Clear();
	 void ImageprocessType1Clear();
	 void ImageprocessType2Clear();
	 void ImageprocessType3Clear();
	 void ImageprocessType4Clear();
	 void ImageprocessType5Clear();
	 void ImageprocessType6Clear();
	 void ImageprocessType7Clear();
	 void ImageprocessType8Clear();
	 void ImageprocessType9Clear();

	 void ImageprocessDoHW(SDL_Surface *source, SDL_Surface *destination, int px, int py, int pw, int ph);
	 void ImageprocessDoHW(SDL_Surface *source, SDL_Surface *destination, int sourceX, int sourceY, int px, int py, int pw, int ph);

	 void setTimeUntilDisplayEnd(int time);	// default is 0 (all time), else how many ticks to display the imageprocess.


	 void drawrectWH(SDL_Surface *Image, int x, int y, int w, int h);

	 void animEnlargeCanvas(std::vector<SDL_Surface*> mySurfaces,int amount);
	 void animFlipX(std::vector<SDL_Surface*> mySurfaces);
	 void animFlipY(std::vector<SDL_Surface*> mySurfaces);
	 void animScaleUpXY(std::vector<SDL_Surface*> mySurfaces,bool horizontal, bool vertical); // scale up 2 times
	 void animScaleDownXY(std::vector<SDL_Surface*> mySurfaces,bool horizontal, bool vertical); // scale down 2 times
	 //
	 void animProcessIntoGrey(std::vector<SDL_Surface*> mySurfaces); // convert all non-alpha colors to grey color
	 void animProcessIntoNoise(std::vector<SDL_Surface*> mySurfaces); // convert all non-alpha colors into noise

	 void animColorizeNonAlpha(std::vector<SDL_Surface*> mySurfaces,SDL_Color); // fill all-non alpha with color for all range from begin to end.
	 void animColorizeAlpha(std::vector<SDL_Surface*> mySurfaces,SDL_Color); // fill all alpha with color for all range from begin to end.
	 // copy all-non alpha pixels with source Image pixels for all range from begin to end.
	 // offsets can be positive or negative. offsets can be increased or decreased to do scroll effect.
	 void animCopyNonAlpha(std::vector<SDL_Surface*> mySurfaces,SDL_Surface *source, int sourceOffsetX, int sourceOffsetY);
	 // copy all alpha pixels with source Image pixels for all range from begin to end.
	 // offsets can be positive or negative. offsets can be increased or decreased to do scroll effect.
	 void animCopyAlpha(std::vector<SDL_Surface*> mySurfaces,SDL_Surface *source, int sourceOffsetX, int sourceOffsetY);
	 // copy all-non alpha pixels with source Image pixels for all range from begin to end.
	 // offsets can be positive or negative. offsets can be increased or decreased to do scroll effect.
	 void animCopyNonAlpha(std::vector<SDL_Surface*> mySurfaces,Animation *source, int sourceOffsetX, int sourceOffsetY);
	 // copy all alpha pixels with source Image pixels for all range from begin to end.
	 // offsets can be positive or negative. offsets can be increased or decreased to do scroll effect.
	 void animCopyAlpha(std::vector<SDL_Surface*> mySurfaces,Animation *source, int sourceOffsetX, int sourceOffsetY);
	 //
//	 void copySurfaceNonAlpha(std::vector<SDL_Surface*> mySurfaces,SDL_Surface *source, SDL_Surface *destination, int sourceOffsetX, int sourceOffsetY);
//	 void copySurfaceAlpha(std::vector<SDL_Surface*> mySurfaces,SDL_Surface *source, SDL_Surface *destination, int sourceOffsetX, int sourceOffsetY);






private:
	// data
	int displayCounter;
	int displayTicks;
	int collision_criterion;
	// code
	void safe_putpixel(int  bytesperline, SDL_Surface *Image, int px, int py, Uint32 color);
	bool  ImageprocessFlag;
	bool  ImageprocessType0Flag;
	bool  ImageprocessType1Flag;
	bool  ImageprocessType2Flag;
	bool  ImageprocessType3Flag;
	bool  ImageprocessType4Flag;
	bool  ImageprocessType5Flag;
	bool  ImageprocessType6Flag;
	bool  ImageprocessType7Flag;
	bool  ImageprocessType8Flag;
	bool  ImageprocessType9Flag;
	float ImageprocessType0Alpha;
	int ImageprocessType1red;
	int ImageprocessType1green;
	int ImageprocessType1blue;
	float ImageprocessType2red;
	float ImageprocessType2green;
	float ImageprocessType2blue;
	bool  ImageprocessType3red;
	bool  ImageprocessType3green;
	bool  ImageprocessType3blue;
	bool  ImageprocessType5red;
	bool  ImageprocessType5green;
	bool  ImageprocessType5blue;
	SDL_Surface		*ImageprocessType6Surface;
	play::Animation *ImageprocessType6Animation;
	float ImageprocessType6CounterX;
	float ImageprocessType6SpeedX;
	float ImageprocessType6CounterY;
	float ImageprocessType6SpeedY;
	int  ImageprocessType7red;
	int  ImageprocessType7green;
	int  ImageprocessType7blue;
	int ImageprocessType8red;
	int ImageprocessType8green;
	int ImageprocessType8blue;
	bool ImageprocessType9Horizontal;
	bool ImageprocessType9Vertical;

	// * * * * * 
	void privateProcessIntoGrey(SDL_Surface *surf);
	void privateProcessIntoNoise(SDL_Surface *surf);
	//CODE, mostly copied from Imageutils
	void privateFlipX(SDL_Surface *Image);
	void privateFlipY(SDL_Surface *Image);
	SDL_Surface* privateCopyNewScaleUpXY(SDL_Surface *source, bool horizontal, bool vertical);
	SDL_Surface* privateCopyNewScaleDownXY(SDL_Surface *source, bool horizontal, bool vertical);
	SDL_Surface* privateCreateSurfaceRGBA(int width, int height);
	SDL_Surface* privateCopyNewSurface(SDL_Surface* source);
	void privateCopySurface(SDL_Surface* source, SDL_Surface* destination,int source_x, int source_y, int source_w, int source_h,	int destination_x, int destination_y);
	SDL_Surface* privateEnlargeCanvas(SDL_Surface *source, int amount);
	void privateCopySurface(SDL_Surface* source, SDL_Surface* destination, int destination_x, int destination_y);
	void privateCopySurface(SDL_Surface* source, SDL_Surface* destination);

	void privateColorizeNonAlpha(SDL_Surface *surf, SDL_Color incolor);
	void privateColorizeAlpha(SDL_Surface *surf, SDL_Color incolor);
	void privateCopySurfaceAlpha(SDL_Surface *source, SDL_Surface *destination, int sourceOffsetX, int sourceOffsetY);
	void privateCopySurfaceNonAlpha(SDL_Surface *source, SDL_Surface *destination, int sourceOffsetX, int sourceOffsetY);

	void privateCopySurfaceAlphaAndNonAlpha(SDL_Surface *source, SDL_Surface *destination, int sourceOffsetX, int sourceOffsetY, bool whichAlphaType);

};
}

#endif