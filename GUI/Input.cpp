#include "Input.h"
#include "Output.h"


Input::Input(window* pW) 
{
	pWind = pW; //point to the passed window
}

void Input::GetPointClicked(int &x, int &y) const
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

string Input::GetSrting(Output *pO) const 
{
	string Label;
	char Key;
	while(1)
	{
		pWind->FlushKeyQueue();
		pWind->FlushMouseQueue();
		pWind->WaitKeyPress(Key);
		if(Key == 27 )	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if (Key == 13)	//ENTER key is pressed
		{
			pWind->FlushMouseQueue();
			return Label;
		}
		if((Key == 8) && (Label.size() >= 1))	//BackSpace is pressed
			Label.resize(Label.size() -1 );			
		else
			Label += Key;
		if (pO)
			pO->PrintMessage(Label);
	}
}

//This function reads the position where the user clicks to determine the desired action
ActionType Input::GetUserAction() const
{	
	int x,y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if(UI.InterfaceMode == MODE_DRAW)	//GUI in the DRAW mode
	{
		//[1] If user clicks on the Toolbar
		if ( y >= 0 && y < UI.ToolBarHeight)
		{	
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / (UI.MenuItemWidth +UI.wx));
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_SWITCH_PM: return TO_PLAY;
			case ITM_SELECT: return SELECT_FIGURE;
			case ITM_UNDO: return TO_UNDO;
			case ITM_REDO: return TO_REDO;
			case ITM_SAVE: return SAVE_FIGURE;
			case ITM_RECT: return DRAW_RECT;
			case ITM_SQUARE: return DRAW_SQUARE;
            case ITM_TRIANGLE: return DRAW_TRIANGLE;
            case ITM_HEXA: return DRAW_HEXA;
            case ITM_CIRCLE: return DRAW_CIRCLE;
			case ITM_MOVE_FIGURE: return MOVE_FIGURE; 			
            case ITM_PLAY_RECORDING: return PLAY_RECORDING;
			case ITM_START_RECORDING: return START_RECORDING;
			case ITM_STOP_RECORDING: return STOP_RECORDING;
			case ITM_LOAD: return TO_LOAD;
			case ITM_COLORS: return TO_COLOR;
			case ITM_CLEAR: return TO_CLEAR;
			case ITM_SOUND: return SOUND_MODE;
			case ITM_DELETE: return TO_DELETE;
			case ITM_EXIT: return EXIT;

			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}

		//[2] User clicks on the drawing area
		if ( y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;	
		}

		
		//[3] User clicks on the status bar
		return STATUS;
	}
	else	//GUI is in PLAY mode
	{
		///TODO: //perform checks similar to Draw mode checks above and return the correspoding action --DONE!--

		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = x / (UI.MenuItemWidth + UI.wx);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case MENU_SWITCH_DM: return TO_DRAW;
			case MENU_PickByColor: return TO_PICK_BY_COLOR;
			case Menu_PickByShape: return TO_PICK_BY_SHAPE;
			case Menu_PickByBoth: return TO_PICK_BY_BOTH;

			default: return EMPTY;	//just for now. This should be updated //edit: updated!
			}
		}
		//[2] User clicks on the drawing area
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;
		}


		//[3] User clicks on the status bar
		return STATUS;
	}


}


ColorType Input::GetColor() const
{
	int x, y;
	pWind->WaitMouseClick(x, y);

	if (y >= UI.ToolBarHeight && y < UI.ToolBarHeight + UI.ColorItemWidth)
	{
		int ClickedColorOrder = (x - UI.ColorXi )/ UI.ColorItemWidth ;

		switch (ClickedColorOrder)
		{
		case CLR_GREEN: return COLOR_GREEN;
		case CLR_RED: return COLOR_RED;
		case CLR_ORANGE: return COLOR_ORANGE;
		case CLR_YELLOW: return COLOR_YELLOW;
		case CLR_BLUE: return COLOR_BLUE;
		case CLR_BLACK: return COLOR_BLACK;
		default: return NO_COLOR;
		}
	}
	return NO_COLOR;

}

///////////////////////Shapes Validation Functions/////////////////////////

void Input::Point_Validation(Point& P, Output* pOut)
{
	while (P.y < UI.ToolBarHeight || P.y > UI.height - UI.StatusBarHeight)
	{
		pOut->PrintMessage("Please pick a valid point");
		GetPointClicked(P.x, P.y);
	}

	if (P.y > UI.ToolBarHeight || P.y < UI.height - UI.StatusBarHeight)
    {
		pOut->PrintMessage("You picked a valid point <3");
    }
	//Makes sure that the chosen points are inside the drawing area
}

void Input::Hexagon_Validation(Point& P, Output* pO)
{
	
	while (
		P.y < UI.wy + UI.ToolBarHeight + sqrt(3) / 2 * UI.HEXAGON_LENGTH ||
		UI.height - P.y < UI.HEXAGON_LENGTH + UI.StatusBarHeight + UI.wy ||
		P.x < UI.wx + UI.HEXAGON_LENGTH ||
		UI.width - P.x < UI.HEXAGON_LENGTH + 3 * UI.wx)
	{
		pO->PrintMessage("Please pick a valid point");
		GetPointClicked(P.x, P.y);
	}

	/*
	1) Checks if the point is inside the drawing area
	2) Makes sure that when the square is drawn takes the clicked point as its center will be drawn inside the drawing area
	*/
}

void Input::Circle_Validation(Point& P1, Point& P2, GfxInfo gfxInfo, Output* pO)
{
	gfxInfo.CircleRadius = sqrt(pow(P1.x - P2.x, 2) + pow(P1.y - P2.y, 2));

	while (
		abs(P1.x - UI.wx)
		< gfxInfo.CircleRadius ||
		abs(P1.x - UI.width) < gfxInfo.CircleRadius ||
		abs(P1.y - (UI.ToolBarHeight)) < gfxInfo.CircleRadius ||
		abs(P1.y - ((UI.height) - UI.StatusBarHeight)) < gfxInfo.CircleRadius ||
		((P1.x == P2.x) && (P1.y == P2.y)))
	{
		if ((P1.x == P2.x) && (P1.y == P2.y))
			pO->PrintMessage("You picked the same point, Please choose different  points");
		else
		pO->PrintMessage("Please pick another valid point");
		GetPointClicked(P1.x, P1.y);//Wait for any click

		GetPointClicked(P2.x, P2.y);
		gfxInfo.CircleRadius = sqrt(pow(P1.x - P2.x, 2) + pow(P1.y - P2.y, 2));

	}
	/*
	 1) Checks if the two points are in the drawing area
	 2) Checks if the normal distance between the two points -RADIUS- creates a circle that's inside the drawig area
	 3) Checks that the picked points are not the same
	*/
}

//square validation function
void Input::Square_Validation(Point& p1, Output* pO)
{
	//float Square_length = 100;
	while (p1.y < ( UI.wy+UI.ToolBarHeight + UI.SQUARE_LENGTH / 2) ||
		p1.y > UI.height - UI.StatusBarHeight -UI.wy||
		p1.y > UI.height - (UI.wy+UI.StatusBarHeight + UI.SQUARE_LENGTH / 2) ||
		p1.x < (UI.wx+UI.SQUARE_LENGTH / 2) ||
		p1.x > UI.width - UI.SQUARE_LENGTH / 2-(3*UI.wx))
	{
		pO->PrintMessage("Please pick a valid point");
		GetPointClicked(p1.x, p1.y);
	}
	/*
	1) Checks if the point is inside the drawing area
	2) Makes sure that when the square is drawn takes the clicked point as its center will be drawn inside the drawing area
	*/
}

// makes sure the chosen points are different 
void Input::Repeatability_Validation(Point& p1, Point& p2, Output* pO)
{
		while (p1.x == p2.x && p1.y == p2.y)
		{
			pO->PrintMessage("You picked the same point, Please choose different  points");
			GetPointClicked(p2.x, p2.y);
		}
		Point_Validation(p2, pO);
		if (p1.x != p2.x || p1.y != p2.y)
		{
			pO->PrintMessage("You picked a valid point <3");
		}
 //Makes sure that the picked points are not the same
}
Input::~Input()
{
}
