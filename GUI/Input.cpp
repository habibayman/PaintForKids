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
		pWind->FlushMouseQueue();
		pWind->FlushKeyQueue();
		pWind->WaitKeyPress(Key);
		if (Key == 27)	//ESCAPE key is pressed
			return "";
		//returns nothing as user has cancelled label
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
		///TODO: //perform checks similar to Draw mode checks above and return the correspoding action


		//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
		int ClickedItemOrder = x / (UI.MenuItemWidth + UI.wx);
		//Divide x coord of the point clicked by the menu item width (int division)
		//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

		MENU_PickByColor,
		Menu_PickByShape,
		Menu_PickByBoth;
		switch (ClickedItemOrder)
		{
		case MENU_SWITCH_DM: return TO_DRAW;
		case MENU_PickByColor: return TO_PICK_BY_COLOR;
		case Menu_PickByShape: return TO_PICK_BY_SHAPE; 
		case Menu_PickByBoth: return TO_PICK_BY_BOTH; 

		default: return EMPTY;	//just for now. This should be updated //edit: updated!
		}
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

void Input::Point_Validation(Point& P, Output* pOut, Input* pIn)
{
while (P.y < UI.ToolBarHeight || P.y > UI.height - UI.StatusBarHeight)
{
	pOut->PrintMessage("Please pick a valid point inside the drawing area");
	pIn->GetPointClicked(P.x, P.y);
}

if (P.y > UI.ToolBarHeight || P.y < UI.height - UI.StatusBarHeight)
{
	pOut->PrintMessage("You picked a valid point <3");
}
}

void Input :: Hexagon_Validation(Point& P, Output* pO){
	const int HexagonLength = 100;
	while (
		P.y < UI.ToolBarHeight + sqrt(3) / 2 * HexagonLength ||
		UI.height - P.y < HexagonLength + UI.StatusBarHeight ||
		P.x < HexagonLength ||
		UI.width - P.x < HexagonLength)

	{
		pO->PrintMessage("Please pick a valid point inside the drawing area");
		GetPointClicked(P.x, P.y);
	}
}

void Input::Circle_Validation(Point& P1, Point& P2, GfxInfo gfxInfo, Output* pO, Input* pI)
{
	
	gfxInfo.CircleRadius = sqrt(pow(P1.x - P2.x, 2) + pow(P1.y - P2.y, 2));

	while (
		abs(P1.x - 0) < gfxInfo.CircleRadius ||
		abs(P1.x - UI.width) < gfxInfo.CircleRadius ||
		abs(P1.y - (UI.ToolBarHeight)) < gfxInfo.CircleRadius ||
		abs(P1.y - ((UI.height) - UI.StatusBarHeight)) < gfxInfo.CircleRadius ||
		((P1.x==P2.x)&&(P1.y==P2.y)))
	{
		if ((P1.x == P2.x) && (P1.y == P2.y))
			pO->PrintMessage("There is no distance between the two points, Please choose another two points");
		else
		{
			pO->PrintMessage("Please pick a valid point inside the drawing area");
		}
		pI->GetPointClicked(P1.x, P1.y);	//Wait for any click

		pI->GetPointClicked(P2.x, P2.y);
		gfxInfo.CircleRadius = sqrt(pow(P1.x - P2.x, 2) + pow(P1.y - P2.y, 2));
		
	}
}

//square validation function
void Input::Square_Validation(Point& p1, Output* pO, Input* pI)
{
	float Square_length = 100;
	while (p1.y < (UI.ToolBarHeight + Square_length / 2) ||
		p1.y > UI.height - UI.StatusBarHeight ||
		p1.y > UI.height - (UI.StatusBarHeight + Square_length / 2) ||
		p1.x < Square_length / 2 ||
		p1.x > UI.width - Square_length / 2)
	{
		pO->PrintMessage("Please pick a valid point inside the drawing area");
		pI->GetPointClicked(p1.x, p1.y);
	}
}

//Rectangle validation function
void Input::Rect_Validation(Point& p1, Point& p2, Output* pO, Input* pI)
{
		while (p1.x == p2.x || p1.y == p2.y)
		{
			pO->PrintMessage("There is no distance between the two points, Please choose another two points");
			GetPointClicked(p1.x, p1.y);
			GetPointClicked(p2.x, p2.y);
		}

}
Input::~Input()
{
}
