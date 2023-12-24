#ifndef DEFS_H
#define DEFS_H

#include "CMUgraphicsLib\CMUgraphics.h"

//This file contains some global constants and definitions to be used in the project.
enum ActionType //The actions supported (you can add more if needed)
{
	TO_PLAY,            //Switch interface to Play mode  
	SELECT_FIGURE,
	TO_UNDO,
	TO_REDO,
	SAVE_FIGURE,

	DRAW_RECT,		    //Draw Rectang
	DRAW_SQUARE,		//Draw square
	DRAW_TRIANGLE,		//Draw triangle
	DRAW_HEXA,		    //Draw hexa
	DRAW_CIRCLE,        //Draw circle

	MOVE_FIGURE,
	PLAY_RECORDING,
	START_RECORDING,
	STOP_RECORDING, //Switch interface to Draw mode
	TO_LOAD,

	FILL_COLOR,
	DRAW_COLOR,
	TO_COLOR,
	TO_CLEAR,
	TO_DELETE,

	EXIT,			//Exit		
	EMPTY,			//A click on empty place in the toolbar
	DRAWING_AREA,	//A click on the drawing area
	STATUS,			//A click on the status bar

	TO_DRAW,

	TO_PICK_BY_COLOR,
	TO_PICK_BY_SHAPE,
	TO_PICK_BY_BOTH



	///TODO: Add the other action types of the two modes
};


enum ColorType
{
	COLOR_GREEN,
	COLOR_RED,
	COLOR_ORANGE,
	COLOR_YELLOW,
	COLOR_BLUE,
	COLOR_BLACK,
	NO_COLOR
};

struct Point	//To be used for figures points
{ int x,y; };

struct GfxInfo	//Graphical info of each figure (you may add more members)
{
	color DrawClr;	//Draw color of the figure
	color FillClr;	//Fill color of the figure
	bool isFilled;	//Figure Filled or not
	int BorderWidth;	//Width of figure borders
	double CircleRadius; //radii of circle
};


#endif
