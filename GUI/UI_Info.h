#ifndef UI_INFO_H
#define UI_INFO_H

#include "..\CMUgraphicsLib\CMUgraphics.h"

//User Interface information file.
//This file contains info that is needed by Input and Output classes to
//handle the user interface

enum GUI_MODE	//Graphical user interface mode
{
	MODE_DRAW,	//Drawing mode (startup mode)
	MODE_PLAY	//Playing mode
};

enum DrawMenuItem //The items of the Draw menu (you should add more items)
{
	//Note: Items are **(ordered)** here as they appear in menu
	//If you want to change the menu items order, change the order here
	ITM_SWITCH_PM,  //Switch to play mode item in menu

	ITM_SELECT,     
	ITM_UNDO,
	ITM_REDO,
	ITM_SAVE,
	ITM_RECT,
	ITM_SQUARE,
	ITM_TRIANGLE,
	ITM_HEXA,
	ITM_CIRCLE,
	ITM_MOVE_FIGURE,
	ITM_PLAY_RECORDING,
	ITM_START_RECORDING,
	ITM_STOP_RECORDING,
	ITM_LOAD,
	ITM_COLORS,
	ITM_CLEAR,
	ITM_DELETE,
	ITM_SOUND,
	ITM_EXIT,		

	DRAW_ITM_COUNT		//no. of menu items ==> This should be the last line in this enum
	
};

enum ColorItems // The color items of the color tool bar 
{
	CLR_GREEN,
	CLR_RED,
	CLR_ORANGE,
	CLR_YELLOW,
	CLR_BLUE,
	CLR_BLACK,

	CLR_ITM_COUNT      //no of color icons added 
};

enum PlayMenuItem //The items of the Play menu (you should add more items)
{
	//Note: Items are **(ordered)** here as they appear in menu
	//If you want to change the menu items order, change the order here
	
	//TODO: Add more items names here
	MENU_SWITCH_DM,
	MENU_PickByColor,
	Menu_PickByShape,
	Menu_PickByBoth,
	
	PLAY_ITM_COUNT		//no. of menu items ==> This should be the last line in this enum	
};


__declspec(selectany) //This line to prevent "redefinition error"

struct UI_Info	//User Interface Info.
{
	GUI_MODE InterfaceMode;
	
	int	width, height,	    //Window width and height
		wx, wy,			//Window starting coordinates
		StatusBarHeight,	//Status Bar Height
		ToolBarHeight,		//Tool Bar Height (distance from top of window to bottom line of toolbar)
		ColorItemWidth,
		MenuItemWidth,		//Width of each item in toolbar menu
		ColorXi;

	color DrawColor;		//Drawing color
	color FillColor;		//Filling color
	color HighlightColor;	//Highlighting color
	color MsgColor;			//Messages color
	color BkGrndColor;		//Background color
	color StatusBarColor;	//Status bar color
	color DrawBarColor;     //Draw bar color 
	
	int PenWidth;			//width of the pen that draws shapes
	
	//shapes constant lengths
	float HEXAGON_LENGTH,
		SQUARE_LENGTH;

	/// Add more members if needed ------DONE!
	
}UI;	//create a global object UI


#endif
