
//
// SERVER COMMANDS
//
#include "Commands.h"
#include "SDL.h"

//namespace comtex{

#include "SDL_draw.h"
#include <list>

#ifndef M_PI
#define M_PI  3.14159265358979323846264338327950288
//	const double PI = 3.14125627
#endif




/*
SDL_Texture* textureGet(int index);		// return Texture
SDL_Surface* SurfaceGet(int handle);		// returns Image
loadSingleSurface(char* filename, bool = true);
*/
//typedef int(*PFI)(char *, char *);

typedef struct Mixi
{
	bool active; //
	bool activeOnlyOnce; //
	int type;			 // type from 'A' to 'z'
	int index;			 // from 0 to 9. (unused)
	char *description;	 // (unused)
	//
	int posX;
	int posY;
	int sizeX;
	int sizeY;
	//
	int posX2;
	int posY2;
	int sizeX2;
	int sizeY2;
	//
} Mixi;


// Uint32 c_white = SDL_MapRGBA( surface - format, r, g, b, a);
Uint32 c_black;
Uint32 c_white;
Uint32 c_gray;
Uint32 c_lgray;
Uint32 c_dgray;
Uint32 c_red;
Uint32 c_green;
Uint32 c_blue;
Uint32 c_yellow;
Uint32 c_yellowT; // full transparent
Uint32 c_magenta;
Uint32 c_cyan;
Uint32 c_pale_yellow;
Uint32 c_pale_red;
Uint32 c_pale_green;
Uint32 c_pale_blue;
Uint32 c_redT;	// semi-transparent
Uint32 c_greenT;	//semi- transparent
Uint32 c_blueT;	// semi-transparent




static Mixi mixibuffer[] =
{
	//                                     posX, posY, sizeX, sizeY,    posX2, posY2, sizeX2, sizeY2
	{ false, false, 'A', 0, "Degree Wheel", 1, 1, 201, 201, 0, 0, 0, 0 },
	{ false, false, 'B', 1, "plot x", 10, 214, 300, 32, 0, 0, 0, 0 },
	{ false, false, 'C', 2, "plot red,green,blue", 324, 2, 36, 280, 360, 14, 240, 258 },
	{ false, false, 'D', 3, "textbox", 8, 574, 600, 18, 0, 0, 0, 0 },
	{ false, false, 'E', 4, "TextLines", 310, 290, 280, 280, 0, 0, 0, 0 },
	{ false, false, 'F', 5, "plotpixels X.Y.", 4, 280, 280, 280, 0, 0, 0, 0 },
	{ false, false, 'G', 6, "Binary Bits", 220, 0, 80, 210, 0, 0, 0, 0 },

	{ false, false, 'H', 7, "nothing", 0, 0, 100, 200 },
	{ false, false, 'Z', 99, nullptr, 0, 0, 0, 0 }
};






Commands::Commands()
{
	delay = 0;
	alreadyInitted = false;
}

Uint32  Commands::joinColorValue2(int r, int g, int b, int a)
{
	r &= 255;	g &= 255;	b &= 255;	a &= 255;
	Uint32 color = 0;
	Uint32 Rmask, Gmask, Bmask, Amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	Rmask = 0xff000000; Gmask = 0x00ff0000; Bmask = 0x0000ff00; Amask = 0x000000ff;
#else
	Rmask = 0x000000ff; Gmask = 0x0000ff00; Bmask = 0x00ff0000; Amask = 0xff000000;
#endif 
	g <<= 8;
	b <<= 16;
	a <<= 24;
	r &= Rmask;
	g &= Gmask;
	b &= Bmask;
	a &= Amask;
	color = r | g | b | a;
	return color;
}



	// 
	// 
	//  Initialize hardware and allocate default values
void Commands::beginHardware()
	{
		if (alreadyInitted == true) return;
		alreadyInitted = true;	// call this once only
		Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
		int posX = 8, posY = 28, width = 640, height = 600;
		
		/*
		
    SDL_INIT_TIMER: timer subsystem
    SDL_INIT_AUDIO: audio subsystem
    SDL_INIT_VIDEO: video subsystem; automatically initializes the events subsystem
    SDL_INIT_JOYSTICK: joystick subsystem; automatically initializes the events subsystem
    SDL_INIT_HAPTIC: haptic (force feedback) subsystem
    SDL_INIT_GAMECONTROLLER: controller subsystem; automatically initializes the joystick subsystem
    SDL_INIT_EVENTS: events subsystem
    SDL_INIT_EVERYTHING: all of the above subsystems
    SDL_INIT_NOPARACHUTE: compatibility; this flag is ignored

		*/
		
		SDL_Init(SDL_INIT_EVERYTHING);
		mainDisplayWindow = SDL_CreateWindow("-= Hello^World =-", posX, posY, width, height, flags);
		mainDisplayRenderer = SDL_CreateRenderer(mainDisplayWindow, -1, SDL_RENDERER_ACCELERATED);

#ifdef DEVELOPMENT
		mainDisplaySurface = SDL_LoadBMP("hello.bmp");
		mainDisplayTexture = SDL_CreateTextureFromSurface(mainDisplayRenderer, mainDisplaySurface);
		SDL_Rect srcrect, dstrect;
		srcrect.w = 600;
		srcrect.h = 200;
		srcrect.x = 0;
		srcrect.y = 0;
		dstrect.w = 600;
		dstrect.h = 200;
		dstrect.x = 25;
		dstrect.y = 25;
		SDL_RenderCopy(    mainDisplayRenderer, mainDisplayTexture, &srcrect, &dstrect);
		SDL_RenderPresent( mainDisplayRenderer );
		SDL_FreeSurface(mainDisplaySurface);
#endif
//		SDL_DestroyTexture(mainDisplayTexture);
//		SDL_DestroyRenderer(mainDisplayRenderer);
//		SDL_DestroyWindow(mainDisplayWindow);

		// VGA COLORS
		c_black = joinColorValue2(0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
		c_white = joinColorValue2(0xee, 0xee, 0xee, SDL_ALPHA_OPAQUE);
		c_gray = joinColorValue2(0x88, 0x88, 0x88, SDL_ALPHA_OPAQUE);
		c_lgray = joinColorValue2(0xcc, 0xcc, 0xcc, SDL_ALPHA_OPAQUE);
		c_dgray = joinColorValue2(0x55, 0x55, 0x55, SDL_ALPHA_OPAQUE);
		c_red = joinColorValue2(0xf0, 0x55, 0x33, SDL_ALPHA_OPAQUE);
		c_green = joinColorValue2(0x00, 0xf0, 0x00, SDL_ALPHA_OPAQUE);
		c_yellow = joinColorValue2(0xf0, 0xf0, 0x00, SDL_ALPHA_OPAQUE);
		c_blue = joinColorValue2(0x44, 0x55, 0xf0, SDL_ALPHA_OPAQUE);
		c_yellowT = joinColorValue2(0xff, 0xff, 0x00, SDL_ALPHA_TRANSPARENT); // Transparent color, 100%
		c_magenta = joinColorValue2(0x00, 0xee, 0xdd, SDL_ALPHA_OPAQUE);
		c_cyan = joinColorValue2(0xdd, 0xee, 0x00, SDL_ALPHA_OPAQUE);
		c_pale_yellow = joinColorValue2(0xf0, 0xf0, 0x60, SDL_ALPHA_OPAQUE);
		c_pale_red = joinColorValue2(0xf9, 0xaa, 0x99, SDL_ALPHA_OPAQUE);
		c_pale_green = joinColorValue2(0xbb, 0xf0, 0x99, SDL_ALPHA_OPAQUE);
		c_pale_blue = joinColorValue2(0x6e, 0x8c, 0xd2, SDL_ALPHA_OPAQUE);
		c_redT = joinColorValue2(0xf9, 0xaa, 0x99,   128);// Transparent color
		c_greenT = joinColorValue2(0xbb, 0xf0, 0x99, 128);// Transparent color
		c_blueT = joinColorValue2(0x6e, 0x8c, 0xd2,  128);// Transparent color
} 



void Commands::beginAllocateDefaultPrivateData()
{
	serverCommandsArray.clear();
	int size = 15;
	for (int i = 0; i < size; i++){
		LowLevel *srvcmd = new LowLevel(
			mixibuffer[i].active,
			mixibuffer[i].activeOnlyOnce,
			mixibuffer[i].type, mixibuffer[i].index,
			mixibuffer[i].posX, mixibuffer[i].posY, mixibuffer[i].sizeX, mixibuffer[i].sizeY,
			mixibuffer[i].posX2, mixibuffer[i].posY2, mixibuffer[i].sizeX2, mixibuffer[i].sizeY2
			);	
		serverCommandsArray.push_back(srvcmd);
		if (mixibuffer[i].description == nullptr) break;
	}
 }







void Commands::executeCommand( int _type, char *_str )
	{
		char cindexIntoArray= (char) _type;
		cindexIntoArray -= '@';
		cindexIntoArray &= 15;
		int indexIntoArray = (char) cindexIntoArray;

		if (indexIntoArray == 0)	// --- ==== A ==== --- //
			exeCommandA(serverCommandsArray[0], _str);//Degree Wheel (0 - 360+)

		if (indexIntoArray == 1)	// --- ==== B ==== --- //
			exeCommandB(serverCommandsArray[1], _str);// plot X (0-255)

		if (indexIntoArray == 2)	// --- ==== C ==== --- //
			exeCommandC(serverCommandsArray[2], _str);// plot (red(0-255),green(0-255),blue(0-255))

		if (indexIntoArray == 3)	// --- ==== D ==== --- //
			exeCommandD(serverCommandsArray[3], _str);// textbox

		if (indexIntoArray == 4)	// --- ==== D ==== --- //
			exeCommandE(serverCommandsArray[4], _str);// multiple textlines

		if (indexIntoArray == 5)	// --- ==== F ==== --- //
			exeCommandF(serverCommandsArray[5], _str);// plotpixels x,y  ( 0-255, 0-255 )
		
		if (indexIntoArray == 6)	// --- ==== G ==== --- //
			exeCommandG(serverCommandsArray[6], _str);// bitboxes
		

//		if (indexIntoArray == 6)	// --- ==== G ==== --- //
//			exeCommandG(serverCommandsArray[6], _str );// multiple textlines

		if (indexIntoArray > 6){
			exeCommandZ(serverCommandsArray[7], _str);// unknown
			exit(0);
		}



}


void Commands::exeCommandA(LowLevel* lo, char *_str)
{
	lo->active = true;
	SDL_Surface *ss = lo->privateSurface;
	//
	int incomingdata = atoi(_str);
	if (lo->activateOnlyOnce == false){
		lo->activateOnlyOnce = true;
		SDL_Rect rect = { 0, 0, ss->w, ss->h };
		SDL_FillRect(ss, &rect, c_yellowT );    //fill with transparent
	}
	double px, py, px2,py2, px3,py3, px4,py4;
	int x1, y1;
	x1 = 100;
	y1 = 100;
	Draw_FillCircle(ss, x1, y1, 100, c_blue);	// large circle filled
	ima->drawrectWH(ss, 0, 0, x1 * 2, y1 * 2);
	double rad1 = (double) incomingdata * (M_PI / 180.0);
	py = sinf(rad1) * (90.0 ) + y1;
	px = cosf(rad1) * (90.0)  + x1;
	double rad2 = ((double)incomingdata + 90.0) * (M_PI / 180.0);
	py2 = sinf(rad2) * (20.0) + y1;
	px2 = cosf(rad2) * (20.0) + x1;
	double rad3 = ((double)incomingdata - 90.0) * (M_PI / 180.0);
	py3 = sinf(rad3) * (20.0) + y1;
	px3 = cosf(rad3) * (20.0) + x1;
	Draw_FillCircle(ss, px, py, 8, c_gray);			// smallest circle
	for (int i = 0; i < 10; i++){
		py4 = sinf(rad2) * (i*2.0) + y1;
		px4 = cosf(rad2) * (i*2.0) + x1;
		Draw_Line(ss, px4, py4, px, py, c_white);
		py4 = sinf(rad3) * (i*2.0) + y1;
		px4 = cosf(rad3) * (i*2.0) + x1;
		Draw_Line(ss, px4, py4, px, py, c_white);
	}
	Draw_Line(ss, px, py,  x1, y1,  c_white);	// middle line
	Draw_Line(ss, px, py, px2, py2, c_white );	// outer line
	Draw_Line(ss, px, py, px3, py3, c_white );  // outer line
	Draw_FillCircle(ss, x1, y1, 20, c_dgray);	// smaller circle
	Draw_Circle(ss, x1, y1, 20, c_white);	    // smaller circle
	int len = strlen(_str) * 8;
	
//	ima->zprintf2_configureTextOutputColors({ 250, 250, 250, 255 }, { 70, 70, 70, 0 });
	
	ima->zprintf (ss, x1 - len/2, y1 - 4, _str);   // central text
	ima->zprintf (ss, x1 * 2 - 12, y1 - 4, "0");
	ima->zprintf (ss, 2,  y1 - 4,  "180");
	ima->zprintf (ss, x1 - 9, y1 * 2 - 9,  "90");
	ima->zprintf (ss, x1 - 12, 4, "270");
	// ...
//	ima->zprintf2_configureTextOutputColors({ 25, 25, 25, 255 }, { 250, 250, 250, 255 });
	return;
}
void Commands::exeCommandB( LowLevel* lo, char *_str )	// plot x
	{
		lo->active = true;
		SDL_Surface *ss = lo->privateSurface;
		//
		bool overflow = false, underflow = false;
		//
		int incomingdata = atoi(_str);
		//
		if (incomingdata <0   ) underflow = true;
		if (incomingdata > 255) overflow  = true;
		//
		Draw_Rect(ss, 
			0,0, 
			lo->sizeX, lo->sizeY, c_red);
		//
		int offsetx = 10;
		int x1 = incomingdata + offsetx;
		int y1 = 4;
		int y2 = 8 * 2;

		if (lo->activateOnlyOnce == false){
			lo->activateOnlyOnce = true;

			SDL_Rect rect = { 0, 0, ss->w-1, ss->h-1 };
			SDL_FillRect(ss, &rect, c_pale_yellow);// 0xff60f0f0);	// pale yellow

			for (int i = 0; i < 255; i += 10){		// grid
				Draw_Line(ss, i, 0, i, 12, c_dgray);
				Draw_Line(ss, i + 1, 0, i + 1, 12, c_dgray);
			}
			ima->zprintf (ss, offsetx + 0,   y1, "0");
			ima->zprintf (ss, offsetx + 128, y1, "128");
			ima->zprintf (ss, offsetx + 255, y1, "255");
		}
		//
		Draw_Line(ss,   offsetx + 0,   0,  offsetx + 0,   24, c_white);	// #1
		Draw_Line(ss,   offsetx + 1,   0,  offsetx + 1,   24, c_white); // #1
		Draw_Line(ss,   offsetx + 128, 0,  offsetx + 128, 24, c_white);	// #2
		Draw_Line(ss,   offsetx + 129, 0,  offsetx + 129, 24, c_white);	// #2
		Draw_Line(ss,   offsetx + 255, 0,  offsetx + 255, 24, c_white);	// #3
		Draw_Line(ss,   offsetx + 256, 0,  offsetx + 256, 24, c_white);	// #3
			SDL_Rect rect;
			rect.x = offsetx;
			rect.y = y2+1;
			rect.w = 8*35;
			rect.h = 9;
			SDL_FillRect(ss, &rect, c_pale_green);// 0xffa0ffa0); // pale green block

		if (overflow == false && underflow == false){
			// ima->zprintf2_configureTextOutputColors({ 250, 250, 250, 255 }, { 0, 0, 0, 0 });
			ima->zprintf (ss, x1 + 1, y2 + 2, _str);
		}
		if (underflow)
			Draw_FillRect(ss,
			offsetx + 1, 
			y2+1,
			10, 9, c_pale_red); // underflow
		if (overflow)
			Draw_FillRect(ss, 
			offsetx + 256 + 1*8 + 4,
			y2+1, 
			10, 9, c_pale_red); // overflow
		return;
}









// * * * * * * * * * * * * * * *
// * * * * * * * * * * * * * * *
// * * * * * * * * * * * * * * *
// * * * * * * * * * * * * * * *
// * * * * * * * * * * * * * * *
// * * * * * * * * * * * * * * *
// * * * * * * * * * * * * * * *
// * * * * * * * * * * * * * * *
// * * * * * * * * * * * * * * *



void Commands::exeCommandC(LowLevel* lo, char *_str)	// plot red,green,blue
{
	lo->active = true;
	SDL_Surface *ss = lo->privateSurface;
	SDL_Surface *ss2 = lo->privateSurface2;
	//
	int incomingRed, incomingGreen, incomingBlue;
	bool status = false;
	char p0, p1, p2, p3, p4,p5;
	p0 = _str[0];	p1 = _str[1]; // [msb|lsb]
	p2 = _str[2];	p3 = _str[3]; // [msb|lsb]
	p4 = _str[4];	p5 = _str[5]; // [msb|lsb]
	incomingRed   = joinLsbMsb(p0, p1) & 255;
	incomingGreen = joinLsbMsb(p2, p3) & 255;
	incomingBlue  = joinLsbMsb(p4, p5) & 255;
	//
//	int incomingdata = atoi( _str );
//	if (incomingdata <0)    underflow = true;
//	if (incomingdata > 255) overflow = true;
	//
	//int offsety = 10;	
	int offsety = 14;
//	int y1 = incomingRed + offsety;
	int x1 = 6;
	int x2 = 8 * 3;
	//
	if (lo->activateOnlyOnce == false){
		lo->activateOnlyOnce = true;
		ima->drawrectWH(ss2, 0, 0, ss2->w, ss2->h);
		SDL_Rect rect;
		rect.x = rect.y = 0;
		rect.w = ss->w;
		rect.h = ss->h;
		SDL_FillRect(ss, &rect, c_lgray); // ***************
		//SDL_FillRect(ss, &rect, c_red);	 // ***************
		Draw_FillRect(ss2, 0, 0, ss2->w, ss2->h, c_black); // clear all
//		ima->zprintf2(ss, x1, 10 + 0,    "0");
//		ima->zprintf2(ss, x1, 10 + 128, "128");
//		ima->zprintf2(ss, x1, 10 + 255, "255");
	}
	SDL_Rect rect;
	rect.x = x1;
	rect.y = 8;
	rect.w = 8 * 3;
	rect.h = 8 * 33 + 2;
	SDL_FillRect(ss, &rect, c_pale_green);
	//
	//ima->zprintf2_configureTextOutputColors({ 250, 250, 250, 255 }, { 0, 0, 0, 0 });
	ima->zprintf (ss, x1, 10 + 128, "128");
	ima->zprintf (ss, x1, 10 + 0,    "0");
	ima->zprintf (ss, x1, 10 + 255, "255");
	//
	offsety = 0;
	rect.x = x1 + 0;
	rect.y = offsety + incomingRed + 11;
	rect.w = 8 * 1;
	rect.h = 6;
	SDL_FillRect(ss, &rect, c_red);
	//
	rect.x = x1 + 7;
	rect.y = offsety + incomingGreen + 11;
	rect.w = 8 * 1;
	rect.h = 6;
	SDL_FillRect(ss, &rect, c_green);
	//
	rect.x = x1 + 7 + 8;
	rect.y = offsety + incomingBlue + 11;
	rect.w = 8 * 1;
	rect.h = 6;
	SDL_FillRect(ss, &rect, c_blue);
	//
	Draw_FillRect(ss2, 0, 0, 1, ss2->h, c_black);
	Draw_FillRect(ss2, ss2->w - 1, 0, 1, ss2->h, c_black);
	Draw_FillRect(ss2, 0, incomingRed,   2, 2, c_red); 
	Draw_FillRect(ss2, 0, incomingGreen, 2, 2, c_green);
	Draw_FillRect(ss2, 0, incomingBlue,  2, 2, c_blue);
	ima->shiftRight1Pixel(ss2);
	return;
}


// * * * * * * * * * * * * * * *
// * * * * * * * * * * * * * * *
// * * * * * * * * * * * * * * *
// * * * * * * * * * * * * * * *
// * * * * * * * * * * * * * * *


void Commands::exeCommandD(LowLevel* lo, char *_str) // draw simple text line
{
	char lineTemp[256];
	int end = lo->sizeX / 16;
	int size = strlen( _str );
	strcpy_s(lineTemp,254, _str);
	if (size > end) lineTemp[end] = 0;
	lo->active = true;
	SDL_Surface *ss = lo->privateSurface;
	if (lo->activateOnlyOnce == false){
		lo->activateOnlyOnce = true;
		Draw_Rect(ss, 0, 0, lo->sizeX-5, lo->sizeY, c_pale_red); //
	}
	//ima->zprintf2_configureTextOutputColors({ 230, 150, 230, 255 }, { 50, 60, 90, 0 });
	ima->zprintf2(ss, 2, 1, lineTemp);
	return;
}


int Commands::joinLsbMsb(char p1, char p2){
	char hexchars[] = "0123456789ABCDEF\0";
	int lsb = 0, msb = 0;
	for (int i = 0; i < 16; i++){
		if (hexchars[i] == p1){
			msb = i;
			break;
		}
	}
	for (int i = 0; i < 16; i++){
		if (hexchars[i] == p2){
			lsb = i;
			break;
		}
	}
	return (int)(msb << 4) | lsb;
}

void Commands::exeCommandF(LowLevel* lo, char *_str)	// plot ( color, x,y )
{
	char hexchars[] = "0123456789ABCDEF\0";
	lo->active = true;
	SDL_Surface *ss = lo->privateSurface;
	char cstrTemp[256];
	char *cstr = &cstrTemp[0];
	unsigned int incomingColor = 0, incomingX = 0, incomingY = 0;
	bool status = false;
	char p0, p1, p2, p3, p4;
	p0 = _str[0];	// [color]
	p1 = _str[1];	p2 = _str[2]; // [msb|lsb]
	p3 = _str[3];	p4 = _str[4]; // [msb|lsb]

	incomingColor = joinLsbMsb(0, p0);
	incomingX = joinLsbMsb(p1, p2);
	incomingY = joinLsbMsb(p3, p4);

	Uint32 _color = 0;
	bool alreadystarted = lo->activateOnlyOnce;
	if (alreadystarted == false){
		lo->activateOnlyOnce = true;
		incomingColor = 0;
	}
/*
CGA 	EGA 	VGA 	    RGB 	    Web 	    Example
0x0 	0x0 	0,0,0 	    0,0,0 	    #000000 	black
0x1 	0x1 	0,0,42   	0,0,170 	#0000aa 	blue
0x2 	0x2 	00,42,00 	0,170,0 	#00aa00 	green
0x3 	0x3 	00,42,42 	0,170,170 	#00aaaa 	cyan
0x4 	0x4 	42,00,00 	170,0,0 	#aa0000 	red
0x5 	0x5 	42,00,42 	170,0,170 	#aa00aa 	magenta
0x6 	0x14 	42,21,00 	170,85,0 	#aa5500 	brown
0x7 	0x7 	42,42,42 	170,170,170	#aaaaaa 	gray
0x8 	0x38 	21,21,21 	85,85,85 	#555555 	dark gray
0x9 	0x39 	21,21,63 	85,85,255 	#5555ff 	bright blue
0xA 	0x3A 	21,63,21 	85,255,85 	#55ff55 	bright green
0xB 	0x3B 	21,63,63 	85,255,255 	#55ffff 	bright cyan
0xC 	0x3C 	63,21,21 	255,85,85 	#ff5555 	bright red
0xD 	0X3D 	63,21,63 	255,85,255 	#ff55ff 	bright magenta
0xE 	0x3E 	63,63,21 	255,255,85 	#ffff55 	yellow
0xF 	0x3F 	63,63,63 	255,255,255	#ffffff 	white
*/
	if (incomingColor == 0){ _color = 0; status = true; }
	if (incomingColor == 1)  _color = joinColorValue2(0, 0, 0, SDL_ALPHA_OPAQUE);// black
	if (incomingColor == 2)  _color = joinColorValue2(0, 0, 170, SDL_ALPHA_OPAQUE);//blue
	if (incomingColor == 3)  _color = joinColorValue2(0, 170, 0, SDL_ALPHA_OPAQUE);//green
	if (incomingColor == 4)  _color = joinColorValue2(0, 170, 170, SDL_ALPHA_OPAQUE);//cyan
	if (incomingColor == 5)  _color = joinColorValue2(170, 0, 0, SDL_ALPHA_OPAQUE);//red
	if (incomingColor == 6)  _color = joinColorValue2(170, 0, 170, SDL_ALPHA_OPAQUE);//magenta
	if (incomingColor == 7)  _color = joinColorValue2(170, 85, 0, SDL_ALPHA_OPAQUE);//brown
	if (incomingColor == 8)  _color = joinColorValue2(170, 170, 170, SDL_ALPHA_OPAQUE);//gray
	if (incomingColor == 9)  _color = joinColorValue2(85, 85, 85, SDL_ALPHA_OPAQUE);//dark gray
	if (incomingColor == 10) _color = joinColorValue2(85, 85, 255, SDL_ALPHA_OPAQUE);//bright blue
	if (incomingColor == 11) _color = joinColorValue2(85, 255, 85, SDL_ALPHA_OPAQUE);//bright green
	if (incomingColor == 12) _color = joinColorValue2(85, 255, 255, SDL_ALPHA_OPAQUE);//bright cyan
	if (incomingColor == 13) _color = joinColorValue2(255, 85, 85, SDL_ALPHA_OPAQUE);//bright red
	if (incomingColor == 14) _color = joinColorValue2(255, 85, 255, SDL_ALPHA_OPAQUE);//bright magenta
	if (incomingColor == 15) _color = joinColorValue2(255, 255, 85, SDL_ALPHA_OPAQUE);//yellow
	if (incomingColor == 16) _color = joinColorValue2(255, 255, 255, SDL_ALPHA_OPAQUE);//white

	int px = incomingX + 10;
	int py = incomingY + 10;
	//	Draw_FillRect(ss, px - 1, py - 1, 1, 1, _color);
	Draw_FillRect(ss, px - 1, py - 1, 2, 2, _color);
	//	Draw_FillRect(ss, px - 2, py - 2, 4, 4, _color);

	if (status == true){	// clear area
		SDL_Rect rect = {0,0,ss->w, ss->h};
		SDL_FillRect(ss, &rect, c_black);
		for (int i = 10; i < 280; i += 10){
			Draw_Line(ss, i, 10, i, 270, c_dgray);
			Draw_Line(ss, 10, i, 270, i, c_dgray);
		}
		ima->drawrectWH(ss, 0, 0, ss->w - 1, ss->h - 1);
		return;
	}
	return;
}




void Commands::exeCommandG(LowLevel* lo, char *_str)	// binary rectangles
{
	//ima->zprintf2_configureTextOutputColors({ 250, 250, 250, 255 }, { 70, 70, 70, 0 });
	lo->active = true;
	SDL_Surface *ss = lo->privateSurface;
	char cstrTemp[256];
	char *cstr = &cstrTemp[0];
	strcpy_s(cstr, 24, _str);
	unsigned int incoming = atoi(cstr);
	unsigned int temp_incoming = incoming & 0x0000ffff;

	char *nums[] = {
		{ "1" }, { "2" }, { "4" }, { "8" }, { "16" }, { "32" }, { "64" }, { "128" },
		{ "255" }, { "512" }, { "1024" }, { "2048" }, { "4096" }, { "8192" }, { "16384" }, { "32768" },
		{ "65535" }
	};
	if (lo->activateOnlyOnce == false){
		lo->activateOnlyOnce = true;
		SDL_Rect rect = { 0, 0, ss->w, ss->h };
		SDL_FillRect(ss, &rect, c_pale_blue);
		int x = 8;
		int y = 16;
		int j = 0;
		for (int i = 0; i < 16; i++){
			int	px = x;
			int	py = y + i * 12;
			int index = i;
			index &= 15;
			ima->zprintf (ss, px + 3 * 8, py + 1, nums[index]);
			Draw_Rect(ss,
				px,
				py,
				10, 10,
				c_white);
		}
	}
	int x = 8;
	int y = 16;
	unsigned int j = 0;
	for (int i = 0; i < 16; i++){
		int	px = x;
		int	py = y + i * 12;
		j = temp_incoming;
		temp_incoming >>= 1;
		j &= 1;
		Draw_Rect(ss,
			px,
			py,
			10, 10,
			c_white);
		if (j == 0)
		{
			Draw_FillRect(ss,
				px+1,
				py+1,
				8, 8,
				c_blue);
		}
		else
		{
			Draw_FillRect(ss,
				px+1,
				py+1,
				8, 8,
				c_white);
		}
	}
	Draw_FillRect(ss,
		x + 3 * 8,
		8,
		6 * 8, 8,
		c_pale_blue);
//	ima->zprintf2_configureTextOutputColors({ 230, 150, 230, 255 }, { 0, 0, 0, 0 });
	ima->zprintf (ss, x + 3 * 8, 8, cstr);
	return;
	
}

//void shiftDataline(LowLevel* lo, SDL_Surface *ss );
void Commands::shiftDataline(LowLevel* lo, SDL_Surface *ss)
{
	SDL_Rect  srcrect, dstrect;
	for (int i = 0; i < 250; i += 8){	// 250
	dstrect.x = 6;
	dstrect.y = (8 + i);
	dstrect.w = lo->sizeX - 12;
	dstrect.h = 8;
	srcrect.x = 6;
	srcrect.y = (16 + i);
	srcrect.w = lo->sizeX - 12;
	srcrect.h = 8;
	SDL_BlitSurface(ss, &srcrect, ss, &dstrect);
}
}
void Commands::printDataLine(LowLevel* lo, SDL_Surface *ss, char *str)
{
	ima->zprintf (ss, 8, lo->sizeY - 16, "                                 ");
	ima->zprintf (ss, 8, lo->sizeY - 16, str);
}

void Commands::exeCommandE(LowLevel* lo, char *_str) // draw multiple text lines with wrap
{
	//ima->zprintf2_configureTextOutputColors({ 250, 250, 250, 255 }, { 70, 70, 70, 0 });

	lo->active = true;
	SDL_Surface *ss = lo->privateSurface;
	if (lo->activateOnlyOnce == false){
		lo->activateOnlyOnce = true;
		Draw_FillRect(ss, 0, 0, lo->sizeX, lo->sizeY, 0xffbbcaa0);
		Draw_Rect(    ss, 8, 8, lo->sizeX - 15, lo->sizeY - 15, 0x00fefefe);
	}
//	SDL_Rect  srcrect;
	//int wrap = 33;	//33

	int wrap = lo->sizeX/8;

	// + + + + + + + + + + + + + + +
	// + + + + + + + + + + + + + + +
	char c0[1024];
	int size = strlen(_str);
	if (size < wrap  ){	// no wrap needed
		shiftDataline(lo, ss);
		printDataLine(lo, ss, _str);
	}else{ // split into multiple lines
		int bits = size / wrap;
		int rest = size % wrap;
		int i = 0;
		for ( i = 0; i < bits; i++){
			strncpy(c0, &_str[wrap*i], wrap );
			c0[wrap] = 0;
			shiftDataline(lo, ss);
			printDataLine(lo, ss, c0);
		}
		if (rest != 0){
			strncpy(c0, &_str[wrap*i], rest);
			c0[rest] = 0;
			shiftDataline(lo, ss);
			printDataLine(lo, ss, c0);
		}
	}
	return;
}





void Commands::exeCommandZ(LowLevel* lo, char *_str)
{
	lo->active = true;
	int i = strlen( _str );
	lo->sizeX = i * 9;
	SDL_Surface *ss = lo->privateSurface;
	SDL_Color color = { 250, 150, 100 };
	ima->fillSurface(ss, color);
	ima->drawrectWH(ss, 0, 0, ss->w - 1, ss->h - 1);
//	ima->zprintf2(ss, 2, 3, lo->stringeling );
	return;
}





void Commands::tickExecuteDisplay()
{
		SDL_Rect srcrect, dstrect;
		int size = serverCommandsArray.size();
		for (int i = 0; i < size; i++){
			LowLevel *lo = serverCommandsArray[i];
			if (lo->active == true){
				srcrect.w = lo->sizeX;
				srcrect.h = lo->sizeY;
				srcrect.x = 0;
				srcrect.y = 0;
				dstrect.w = srcrect.w;
				dstrect.h = srcrect.h;
				dstrect.x = lo->positionX;
				dstrect.y = lo->positionY;
				SDL_Texture *tstx = SDL_CreateTextureFromSurface(mainDisplayRenderer, lo->privateSurface);
				SDL_RenderCopy(mainDisplayRenderer, tstx, &srcrect, &dstrect);
				SDL_DestroyTexture( tstx );

				if (lo->privateSurface2!= nullptr){
					srcrect.w = lo->sizeX2;
					srcrect.h = lo->sizeY2;
					srcrect.x = 0;
					srcrect.y = 0;
					dstrect.w = srcrect.w;
					dstrect.h = srcrect.h;
					dstrect.x = lo->positionX2;
					dstrect.y = lo->positionY2;
					tstx = SDL_CreateTextureFromSurface(mainDisplayRenderer, lo->privateSurface2);
					SDL_RenderCopy(mainDisplayRenderer, tstx, &srcrect, &dstrect);
					SDL_DestroyTexture(tstx);
				}
			}
		}
		SDL_RenderPresent(mainDisplayRenderer);
	}
	// *********************************************************************************
void Commands::end()
	{
		if (alreadyInitted == false) return;
		alreadyInitted = false;	// call this once only
//		SDL_DestroySurface(mainDisplaySurface);
		SDL_DestroyTexture(mainDisplayTexture);
		SDL_DestroyRenderer(mainDisplayRenderer);
		SDL_DestroyWindow( mainDisplayWindow );
		mainDisplayTexture = nullptr;
		mainDisplayRenderer = nullptr;
		mainDisplayWindow = nullptr;
	}
Commands::~Commands(){
	//	end();
}

//};

