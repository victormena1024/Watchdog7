
#ifdef NEIVERR

#ifdef NEIVERR
#include <cmath>
#include <SDL.h>
#include <iostream>

void Line( float x1, float y1, float x2, float y2, const Color& color )
{
	// Bresenham's line algorithm
	const bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
	if(steep)
	{
		std::swap(x1, y1);
		std::swap(x2, y2);
	}

	if(x1 > x2)
	{
		std::swap(x1, x2);
		std::swap(y1, y2);
	}

	const float dx = x2 - x1;
	const float dy = fabs(y2 - y1);

	float error = dx / 2.0f;
	const int ystep = (y1 < y2) ? 1 : -1;
	int y = (int)y1;

	const int maxX = (int)x2;

	for(int x=(int)x1; x<maxX; x++)
	{
		if(steep)
		{
			SetPixel(y,x, color);
		}
		else
		{
			SetPixel(x,y, color);
		}

		error -= dy;
		if(error < 0)
		{
			y += ystep;
			error += dx;
		}
	}
}
#endif

#ifdef NEIVERR

	SDL_InitSubSystem(SDL_INIT_JOYSTICK);
SDL_Joystick *joy = nullptr;	// = new _SDL_Joystick();
// Initialize the joystick subsystem
SDL_InitSubSystem(SDL_INIT_JOYSTICK);
// Check for joystick
if (SDL_NumJoysticks() > 0) {
	// Open joystick
	joy = SDL_JoystickOpen(0);
	if (joy) {
		printf("Opened Joystick 0\n");
		//	printf("Name:              %s\n", SDL_JoystickNameForIndex(0));
		printf("Number of Axes:    %d\n", SDL_JoystickNumAxes(joy));
		printf("Number of Buttons: %d\n", SDL_JoystickNumButtons(joy));
		printf("Number of Balls:   %d\n", SDL_JoystickNumBalls(joy));
	}
	else {
		printf("Couldn't open Joystick 0\n");
	}
}



Sprite *bg = spelmotor->createSpriteInstance("background", 0, 0);
Sprite *goblin = spelmotor->createSpriteInstance("goblin", 200, 200);
spelmotor->run();
if (SDL_JoystickGetAttached(joy)) { SDL_JoystickClose(joy); }







//	std::vector<std::string>  Image_filenames;	// Array, unused
//	std::vector<SDL_Surface*> Image_surfaces;	// Array, unused 

#endif

/*
* Copyright 2015 MovingBlocks
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/
package org.terasology.commonworld.geom;
import org.terasology.math.Vector2i;
import java.util.EnumSet;
import java.util.Set;
/**
* Created by Skaldarnar on 07.03.2015.
*/
public class BresenhamLineIterator {

	/**
	* Overlap mode
	*/
	public static enum Overlap {
		/**
		* Overlap - first go major then minor direction
		*/
		MAJOR,

		/**
		* Overlap - first go minor then major direction
		*/
		MINOR
	}

	/**
	* Thickness mode
	*/
	public static enum ThicknessMode {
		/**
		* Line goes through the center
		*/
		MIDDLE,

		/**
		* Line goes along the border (clockwise)
		*/
		CLOCKWISE,

		/**
		* Line goes along the border (counter-clockwise)
		*/
		COUNTERCLOCKWISE
	}

	/**
	* Classical Bresenham line drawing algorithm without overlapping pixels.
	*
	* @param start the start position
	* @param end the end position
	*/
	public static void iterateLine2D(Vector2i start, Vector2i end, BresenhamVisitor visitor) {
		iterateLine2D(start, end, visitor, EnumSet.noneOf(Overlap.class));
	}

	/**
	* Modified Bresenham line drawing algorithm with optional overlap (esp. for drawThickLine())
	* Overlap draws additional pixel when changing minor direction - for standard bresenham overlap = LINE_OVERLAP_NONE (0)
	* <pre>
	*  Sample line:
	*    00+
	*     -0000+
	*         -0000+
	*             -00
	*  0 pixels are drawn for normal line without any overlap
	*  + pixels are drawn if LINE_OVERLAP_MAJOR
	*  - pixels are drawn if LINE_OVERLAP_MINOR
	* </pre>
	*
	* @param start the start position
	* @param end the end position
	* @param overlap the overlap specification
	*/
	public static void iterateLine2D(Vector2i start, Vector2i end, BresenhamVisitor visitor, Set<Overlap> overlap) {
		iterateLine2D(start.x, start.y, end.x, end.y, visitor, overlap);
	}

	public static void iterateLine2D(int aXStart, int aYStart, int xEnd, int yEnd, BresenhamVisitor visitor, Set<Overlap> overlap) {
		int tDeltaX;
		int tDeltaY;
		int tDeltaXTimes2;
		int tDeltaYTimes2;
		int tError;
		int tStepX;
		int tStepY;

		if ((aXStart == xEnd) || (aYStart == yEnd)) {
			//horizontal or vertical line -> directly add all points
			int sx = Math.min(aXStart, xEnd);
			int sy = Math.min(aYStart, yEnd);
			int ex = Math.max(aXStart, xEnd);
			int ey = Math.max(aYStart, yEnd);

			for (int y = sy; y <= ey; y++) {
				for (int x = sx; x <= ex; x++) {
					visitor.visit(x, y);
				}
			}
		}
		else {
			//calculate direction
			tDeltaX = xEnd - aXStart;
			tDeltaY = yEnd - aYStart;
			if (tDeltaX < 0) {
				tDeltaX = -tDeltaX;
				tStepX = -1;
			}
			else {
				tStepX = +1;
			}
			if (tDeltaY < 0) {
				tDeltaY = -tDeltaY;
				tStepY = -1;
			}
			else {
				tStepY = +1;
			}
			tDeltaXTimes2 = tDeltaX << 1;
			tDeltaYTimes2 = tDeltaY << 1;
			// add start pixel
			visitor.visit(aXStart, aYStart);
			if (tDeltaX > tDeltaY) {
				// start value represents a half step in Y direction
				tError = tDeltaYTimes2 - tDeltaX;
				while (aXStart != xEnd) {
					// step in main direction
					aXStart += tStepX;
					if (tError >= 0) {
						if (overlap.contains(Overlap.MAJOR)) {
							// draw pixel in main direction before changing
							visitor.visit(aXStart, aYStart);
						}
						// change Y
						aYStart += tStepY;
						if (overlap.contains(Overlap.MINOR)) {
							// draw pixel in minor direction before changing
							visitor.visit(aXStart - tStepX, aYStart);
						}
						tError -= tDeltaXTimes2;
					}
					tError += tDeltaYTimes2;
					visitor.visit(aXStart, aYStart);
				}
			}
			else {
				tError = tDeltaXTimes2 - tDeltaY;
				while (aYStart != yEnd) {
					aYStart += tStepY;
					if (tError >= 0) {
						if (overlap.contains(Overlap.MAJOR)) {
							// draw pixel in main direction before changing
							visitor.visit(aXStart, aYStart);
						}
						aXStart += tStepX;
						if (overlap.contains(Overlap.MINOR)) {
							// draw pixel in minor direction before changing
							visitor.visit(aXStart, aYStart - tStepY);
						}
						tError -= tDeltaYTimes2;
					}
					tError += tDeltaXTimes2;
					visitor.visit(aXStart, aYStart);
				}
			}
		}
	}
}






/*


//nerifrån uppåt (SW)
void drawLine(SDL_Surface *Screen, int x0, int y0, int x1, int y1, Uint32 pixel) {

int i;
double x = x1 - x0;
double y = y1 - y0;
double length = sqrt( x*x + y*y );
double addx = x / length;
double addy = y / length;
x = x0;
y = y0;

for ( i = 0; i < length; i += 1) {
putpixel(Screen, x, y, pixel );
x += addx;
y += addy;

}
}


int main(int argc, char** argv) {

Uint32 pixel;
printf("Initializing SDL.\n");
// Initialize defaults, Video and Audio subsystems 
if ((SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1)) {
	printf("Could not initialize SDL: %s.\n", SDL_GetError());
	exit(-1);
}

printf("SDL initialized.\n");

printf("Setting video mode.\n");
SDL_Surface* screen = SDL_SetVideoMode(600, 600, 32, SDL_DOUBLEBUF);
SDL_WM_SetCaption("Laboration med Linjer", NULL);
printf("Video mode set.\n");


int i, sx = 300, sy = 300, ex = 100, ey = 100;

for (i = 0; i < 17; i++) {
	drawLine(screen, sx, sy, ex, ey, pixel);
	SDL_Flip(screen);
	SDL_Delay(900);
	if (i < 4) {
		ex += 100;
	}
	if (i >= 4 && i < 8) {
		ey += 100;
	}
	if (i >= 8 && i < 12) {
		ex -= 100;
	}
	if (i >= 12 && i < 16) {
		ey -= 100;
	}
}

drawLine(screen, 100, 100, 500, 100, pixel);
drawLine(screen, 500, 100, 500, 500, pixel);
drawLine(screen, 500, 500, 100, 500, pixel);
drawLine(screen, 100, 500, 100, 100, pixel);
SDL_Flip(screen);
SDL_Delay(4000);

printf("Quitting SDL.\n");
// Shutdown all subsystems 
SDL_Quit();
printf("Quitting...\n");
exit(0);
}

*/

#endif












/* ********************
//		SDL_Surface* ss = ima->loadRGBA("img\\hello2.bmp");
//		lo->privateSurface = ss;

#include "SDL_draw.h"

//IMPORTANT: Call this function AFTER the call to 'SDL_SetVideoMode':
Draw_Init(); //Register the functions for current bpp


void Draw_Pixel(SDL_Surface *super,
	Sint16 x, Sint16 y,
	Uint32 color);

Draw a colored pixel on coordinates x, y.


void Draw_Line(SDL_Surface *super,
Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2,
Uint32 color);

Draw a line from x1, y1 to x2, y2.


void Draw_Circle(SDL_Surface *super,
Sint16 x0, Sint16 y0, Uint16 r,
Uint32 color);

Draw a circle with center x0, y0 and radius r.


void Draw_FillCircle(SDL_Surface *super,
Sint16 x0, Sint16 y0, Uint16 r,
Uint32 color);

Draw a filled circle with center x0, y0 and radius r.


void Draw_HLine(SDL_Surface *super,
Sint16 x0, Sint16 y0, Sint16 x1,
Uint32 color);

Draw a horizontal line from x0, y0 to x1, y0.


void Draw_VLine(SDL_Surface *super,
Sint16 x0, Sint16 y0, Sint16 y1,
Uint32 color);

Draw a vertical line from x0, y0 to x0, y1.


void Draw_Rect(SDL_Surface *super,
Sint16 x, Sint16 y, Uint16 w, Uint16 h,
Uint32 color);

Draw a rectangle with upper left corner in x, y being w the width and h the height.


void Draw_FillRect(SDL_Surface *super,
Sint16 x, Sint16 y, Uint16 w, Uint16 h,
Uint32 color);

The same as above but the rectangle is filled.This function is equivalent to SDL_FillRect(is a MACRO).


void Draw_Ellipse(SDL_Surface *super,
Sint16 x0, Sint16 y0,
Uint16 Xradius, Uint16 Yradius,
Uint32 color);

Draw a ellipse with center in x0, y0.Xradius is the major axis and Yradius is the minor axis.


void Draw_FillEllipse(SDL_Surface *super,
Sint16 x0, Sint16 y0,
Uint16 Xradius, Uint16 Yradius,
Uint32 color);

Draw a filled ellipse(same parameters as the above function).


void Draw_Round(SDL_Surface *super,
Sint16 x0, Sint16 y0, Uint16 w, Uint16 h,
Uint16 corner, Uint32 color);

Draw a rectangle with rounded corners.x0, y0 is the upper left corner of the rectangle, w is the width and h is the height.corner is the radius of the corner.


void Draw_Round(SDL_Surface *super,
Sint16 x0, Sint16 y0, Uint16 w, Uint16 h,
Uint16 corner, Uint32 color);

The same as above but the rounded rectangle is filled.
*/
