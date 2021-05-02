#ifndef IMAGEUTILST_H
#define IMAGEUTILST_H
#include <SDL.h>
#include <iostream>
/*
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <cstdarg>
#include <cmath>
#include <cstdio>
#include <algorithm>
#include <string> 
*/



// myFlagAlpha
//  Criteria::Topleft, means alpha value is whatever color is on top left pixel (0,0) in graphics
//	Criteria::Magenta, means alpha value is full magenta, R=255, G=0, B=255,
//	Criteria::Alphavalue, means use alpha value in 32 bit pixel values
//	Criteria::anycolor, means alpha value can be any color, R=?, G=?, B=?


#ifndef M_PI
#define M_PI (float)3.141592653589793238462
#endif
#define DEG_TO_RAD(degrees) degrees * (M_PI/180.0)
#define RAD_TO_DEG(radians) radians * (180.0/M_PI)


namespace snaf {


enum criteriaFlags_
{
	criteriaFlag_none       = 0,
	criteriaFlag_enabled    = 1 << 0,
	criteriaFlag_topleft    = 1 << 1,
	criteriaFlag_alpha		= 1 << 2,
	criteriaFlag_anycolor	= 1 << 3,
	criteriaFlag_magenta    = 1 << 4
};
enum animationFlags_
{
	animationFlag_none = 0,
	animationFlag_enabled  = 1 << 0,
	animationFlag_pingpong = 1 << 1,
};


//namespace snaf{

class Imageutils
{
public:

	// in code:  void ShowFileDialog(bool* open, char* buffer, unsigned int bufferSize, Criteria crit = Criteria::Topleft ) {
	enum class Criteria {
		topleft,
		alpha,
		anycolor,
		magenta
	};


	// in code:  if (fileNameSortOrder == Criteria::Magenta ) {
	// in code:  void SomeFunction(bool* open, char* buffer, int bufferSize, Criteria crit = Criteria::Topleft ) {

	Imageutils(void);
	~Imageutils(void);

	// static...
	std::string stringToLower(std::string sourceString);
	SDL_Surface* createSurface( int width, int height );
	SDL_Surface* createSurface24(int width, int height);
	SDL_Surface* createSurface32(int width, int height);
	SDL_Surface* copyNewSurface( SDL_Surface* source );
	SDL_Surface* copyNewSurfaceFrom24to32(SDL_Surface* source);
	SDL_Surface* copyNewSurfaceFrom32to24(SDL_Surface* source);
	// ...static

	void blitSurface( SDL_Surface* source, SDL_Surface* destination, int destination_x, int destination_y);
	void blitSurface( SDL_Surface* source, SDL_Surface* destination  );
	void blitSurface( SDL_Surface* source, SDL_Surface* destination, int source_x, int source_y, int source_w, int source_h,int destination_x, int destination_y );


	// copy and scale up with 2 in X axis
	void blitScaleSurface2X( SDL_Surface* source, SDL_Surface* destination  );
	// copy and scale up with 2 in Y axis
	void blitScaleSurface2Y( SDL_Surface* source, SDL_Surface* destination  );

// RETAIN //
	bool similar( int a, int b);
	// fill all chosen colors found with alpha.
	void transformColorIntoAlpha(SDL_Surface *surf, SDL_Color incolor );
	// fill all non-alpha colors with chosen color
	void colorizeNonAlpha(SDL_Surface *surf, SDL_Color incolor );
	// fill all alpha colors with chosen color
	void colorizeAlpha(SDL_Surface *surf, SDL_Color incolor );
	// fill all non-alpha colors with chosen source Image
	// offsets where to write the source Image
	void copySurfaceNonAlpha( SDL_Surface *source, SDL_Surface *destination, int sourceOffsetX, int sourceOffsetY);
	// fill all non-alpha colors with chosen source Image
	// offsets where to write the source Image
	void copySurfaceAlpha( SDL_Surface *source, SDL_Surface *destination, int sourceOffsetX, int sourceOffsetY);
// RETAIN //

	// double the size of chosen axis, creates a new surface.
	SDL_Surface* copyNewScaleUpXY( SDL_Surface *source, bool horizontal, bool vertical );
	// half the size of chosen axis, creates a new surface.	
	SDL_Surface* copyNewScaleDownXY( SDL_Surface *source, bool horizontal, bool vertical );
	//
	void putpixel( SDL_Surface *surf, int px, int py, Uint32 color );
	int  getpixel( SDL_Surface *surf, int px, int py );
	void putblock( SDL_Surface *surf, int px, int py, Uint32 color, int blocksize = 1 );
	//
	void safe_putpixel( int  bytesperline, SDL_Surface *surf, int px, int py, Uint32 color );
	void safe_putpixel2(int  bytesperline, Uint32 *imagebuffer, int px, int py, Uint32 color);
	void safe_putpixel3(int maxdestindex, int  bytesperline, Uint32 *SourceImage, int px, int py, Uint32 color);
	void drawrectWH( SDL_Surface *Image, int px, int py, int pw, int ph );
	void drawrectWH(SDL_Surface *Image); // new version, new functionality

	void copy_surface_with_alpha( SDL_Surface *source, SDL_Surface *destination, int x, int y );
	void Imageprocess_do_HW( SDL_Surface *source, SDL_Surface *destination, int px, int py, int pw, int ph );
	//

	void clearSurface( SDL_Surface *Image );
	void clearSurface( SDL_Surface *Image, SDL_Color col );
	void clearSurfaceAlpha( SDL_Surface *Image );
	void clearSurfaceAlpha( SDL_Surface *Image, SDL_Color col );
	void copyFrom8BppTo32Bpp( SDL_Surface *source, SDL_Surface *destination );


// **********
	void randomDots(  SDL_Surface *surf, SDL_Color incolor, int amount );
	void randomStars( SDL_Surface *surf, SDL_Color incolor, int amount );
	void randomBlobs( SDL_Surface *surf, SDL_Color incolor, int amount );
	void private_random_method( SDL_Surface *surf, SDL_Color incolor, int amount, int type_method );
	void private_method_blob( int  bytesperline, SDL_Surface *Image, int px, int py, Uint32 color );
	void private_method_star( int  bytesperline, SDL_Surface *Image, int px, int py, Uint32 color );
	void private_method_diamond( int  bytesperline, SDL_Surface *surface, int px, int py, Uint32 color );
	void outlineX( SDL_Surface *Image, SDL_Color outlinecolor );
	void outlineY( SDL_Surface *Image, SDL_Color outlinecolor );
	void outlineXblack( SDL_Surface *Image );
	void outlineYblack( SDL_Surface *Image );
	void outlineXwhite( SDL_Surface *Image );
	void outlineYwhite( SDL_Surface *Image );
// ************


	void flipX(SDL_Surface *Image);
	void flipY(SDL_Surface *Image);
	void fillSurface(SDL_Surface *surf, SDL_Color color);
	void shiftDown1Pixel( SDL_Surface *Image );
	void shiftUp1Pixel( SDL_Surface *Image );
	void shiftLeft1Pixel( SDL_Surface *Image );
	void shiftRight1Pixel( SDL_Surface *Image );	
	SDL_Surface *reflip_90(SDL_Surface *source, SDL_Surface *destination);
	void toGrey(SDL_Surface *Image);
	void recolorImage(SDL_Surface *Image);


	bool areColorsSimilar( int color1, int color2, int precision ); // Returns true if similar colors.
	void splitColorValue( int color, int& r,int& g, int& b, int& a );
	void joinColorValue(  int r,int g, int b, int a, int& color );
	int  joinColorValue(  int r,int g,int b,int a);
	int  joinColorValue2(int r, int g, int b, int a);
	// original code is from internet.
	void floodFillScanline(SDL_Surface *surf, int x, int y, int newColor, int oldColor,int precision = 0);
	
	SDL_Surface *loadRGB(char * filename);
	SDL_Surface *loadRGBA(char * filename);		// easy loading into 32 bits per pixel
	SDL_Surface *loadRGBA_with_transparency_magenta(char * filename);
	bool  isAlphaTransparent(int alfa);

	
	// // // // // //
	void display( char *description, float value );
	void display( char *description, bool value );
	void display( char *description, int value );

	void zprint(   SDL_Surface *surf, int x, int y, char *text);	// display fixed b/w 8x8 text onto surface
    void zprintf(  SDL_Surface *surf, int x, int y, char *text, ... ); // 8x8. print formatted text
	void zprint2(  SDL_Surface *surf, int x, int y, char *text);	// display fixed b/w 16x16 text onto surface
	void zprintf2( SDL_Surface *surf, int x, int y, char *text, ... ); // 16x16. print formatted text
	void zprintf_configureColors( SDL_Color foregroundColor, SDL_Color backgroundColor );

	void bitSlice(unsigned char input, SDL_Surface *surf, int x, int y );	
	void calcRotateMaximum( SDL_Surface *input, int& width, int& height );
	void rotate( SDL_Surface *input, SDL_Surface*output, double angle );
	void advancedRotation( SDL_Surface *input, SDL_Surface*output, double angle,
		int sourceX, int sourceY, int destinationX, int destinationY );
	void HSVToRGB (float h, float s, float v, float& r, float& g, float& b );
	void RGBToHSV (float r, float g, float b, float& h, float& s, float& v );
	// // // // // //
	
	SDL_Surface* privateCreateSurfaceRGBA(int width, int height);
	SDL_Surface* privateCreateSurfaceRGBx(SDL_Surface *input, int width, int height);
	SDL_Surface* privateEnlargeCanvas(SDL_Surface *source, int amount);

	// 2020.07.24
	void displaySurfaceData(SDL_Surface *surf); // Work In Progress


	int getAlphaValue(SDL_Surface *surf, int pixelvalue, Criteria criteria);
	int getAlphaValue(SDL_Surface *surf, Uint32 pixelvalue, Criteria criteria, Uint32 selectedAlphaColor);

	SDL_Surface *shrink(SDL_Surface *source);


	char *printStringFromInteger(int input);





private:
    void private_cacheGlyfs8x8();
    void private_cacheGlyfs16x16();
	void private_TranslateSurface(int index, SDL_Surface *surf);

	int	printf_foreground_color, printf_background_color;

//	SDL_Surface *img8x8;	// used by showText(...);                
//	SDL_Surface *img8x16;	// used by showText2(...);        
//	SDL_Surface *img16x16;	// used by showText2(...);
	//
	//
	//
	bool debugFlag;
	int	 collision_criterion;	// what alpha value that is considered transparent (default is 127)
	
};
}
#endif