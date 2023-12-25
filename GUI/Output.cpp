#include "Output.h"


Output::Output()
{
	//Initialize user interface parameters
	UI.InterfaceMode = MODE_DRAW;

	UI.width = 1250;
	UI.height = 650;
	UI.wx = 5;
	UI.wy = 5;


	UI.StatusBarHeight = 50;
	UI.ToolBarHeight = 60;
	UI.MenuItemWidth = 50;
	UI.ColorItemWidth = 30;
	//check it
	//UI.ColorXi = ITM_COLORS * (UI.MenuItemWidth + UI.wx);
	UI.ColorXi = ITM_DRAW_COLOR * (UI.MenuItemWidth + UI.wx);

	UI.DrawColor = BLUE;	//Drawing color
	UI.FillColor = WHITE;	//Filling color
	UI.MsgColor = BLACK;		//Messages color
	UI.DrawColor = BLUE;	//Drawing color 
	UI.FillColor = GREEN;	//Filling color 
	UI.MsgColor = BLACK;		//Messages color 
	UI.BkGrndColor = WHITE;	//Background color changed color from LIGHTGOLDENRODYELLOW to WHITE
	UI.HighlightColor = MAGENTA;	//This color should NOT be used to draw figures. use if for highlight only
	UI.StatusBarColor = LIGHTSTEELBLUE;
	UI.DrawBarColor = LIGHTSTEELBLUE;

	UI.PenWidth = 4;	//width of the figures frames

	//Shapes_Constants
	UI.HEXAGON_LENGTH = 100;
	UI.SQUARE_LENGTH = 140;

	//Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	//Change the title
	pWind->ChangeTitle("Paint for Kids - Programming Techniques Project");

	CreateDrawToolBar();
	CreateStatusBar();
}


Input* Output::CreateInput() const
{
	Input* pIn = new Input(pWind);
	return pIn;
}

//======================================================================================//
//								Interface Functions										//
//======================================================================================//

window* Output::CreateWind(int w, int h, int x, int y) const
{
	window* pW = new window(w, h, x, y);
	pW->SetBrush(UI.BkGrndColor);
	pW->SetPen(UI.BkGrndColor, 1);

	// draw drawing area 
	pW->DrawRectangle(0, UI.ToolBarHeight, w, h);
	return pW;
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar() const
{
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearStatusBar() const
{
	//Clear Status bar by drawing a filled white rectangle
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateDrawToolBar() const
{
	UI.InterfaceMode = MODE_DRAW;

	//background color of drawtoolbar
	pWind->SetPen(UI.DrawBarColor, 1);
	pWind->SetBrush(UI.DrawBarColor);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);


	//You can draw the tool bar icons in any way you want.
	//Below is one possible way

	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in UI_Info.h ==> enum DrawMenuItem
	string MenuItemImages[DRAW_ITM_COUNT];
	//shapes images
	MenuItemImages[ITM_RECT] = "images\\MenuItems\\Menu_Rect.jpg";
	MenuItemImages[ITM_SQUARE] = "images\\MenuItems\\Menu_Squ.jpg";
	MenuItemImages[ITM_TRIANGLE] = "images\\MenuItems\\Menu_Tri.jpg";
	MenuItemImages[ITM_CIRCLE] = "images\\MenuItems\\Menu_Circ.jpg";
	MenuItemImages[ITM_HEXA] = "images\\MenuItems\\Menu_Hexa.jpg";
	//Features images
	MenuItemImages[ITM_SWITCH_PM] = "images\\MenuItems\\Menu_SwitchPM.jpg";
	MenuItemImages[ITM_SELECT] = "images\\MenuItems\\Menu_Select.jpg";
	MenuItemImages[ITM_UNDO] = "images\\MenuItems\\Menu_Undo.jpg";
	MenuItemImages[ITM_REDO] = "images\\MenuItems\\Menu_Redo.jpg";
	MenuItemImages[ITM_SAVE] = "images\\MenuItems\\Menu_Save.jpg";
	MenuItemImages[ITM_MOVE_FIGURE] = "images\\MenuItems\\Menu_Move.jpg";
	MenuItemImages[ITM_PLAY_RECORDING] = "images\\MenuItems\\Menu_Play.jpg";
	MenuItemImages[ITM_START_RECORDING] = "images\\MenuItems\\Menu_Start_Recording.jpg";
	MenuItemImages[ITM_STOP_RECORDING] = "images\\MenuItems\\Menu_Stop_Recording.jpg";
	MenuItemImages[ITM_LOAD] = "images\\MenuItems\\Menu_loadgraph.jpg";
	MenuItemImages[ITM_DRAW_COLOR] = "images\\MenuItems\\Menu_Draw_Clr.jpg";
	MenuItemImages[ITM_FILL_COLOR] = "images\\MenuItems\\Menu_Fill_Clr.jpg";
	MenuItemImages[ITM_CLEAR] = "images\\MenuItems\\Menu_clear.jpg";
	MenuItemImages[ITM_SOUND] = "images\\MenuItems\\Menu_Sound.jpg";
	MenuItemImages[ITM_DELETE] = "images\\MenuItems\\Menu_Delete.jpg";
	MenuItemImages[ITM_EXIT] = "images\\MenuItems\\Menu_Exit.jpg";

	//TODO: Prepare images for each menu item and add it to the list //Done!

	//Draw menu item one image at a time
	for (int i = 0; i < DRAW_ITM_COUNT; i++) {
		pWind->DrawImage(MenuItemImages[i], (i * UI.MenuItemWidth) + (UI.wx * i), UI.wy, UI.MenuItemWidth, UI.ToolBarHeight - UI.wy * 2);
	}

}
//////////////////////////////////////////////////////////////////////////////////////////

//Created a color palette 

void Output::CreateColorPalette() const
{

	string ColorItemImages[CLR_ITM_COUNT];

	ColorItemImages[CLR_RED] = "images\\MenuItems\\Menu_red.jpg";
	ColorItemImages[CLR_ORANGE] = "images\\MenuItems\\Menu_orange.jpg";
	ColorItemImages[CLR_YELLOW] = "images\\MenuItems\\Menu_yellow.jpg";
	ColorItemImages[CLR_GREEN] = "images\\MenuItems\\Menu_green.jpg";
	ColorItemImages[CLR_BLUE] = "images\\MenuItems\\Menu_blue.jpg";
	ColorItemImages[CLR_BLACK] = "images\\MenuItems\\Menu_black.jpg";

	for (int i = 0; i < CLR_ITM_COUNT; i++)
		pWind->DrawImage(
			ColorItemImages[i],
			UI.ColorXi + (i * UI.ColorItemWidth),
			UI.ToolBarHeight,
			UI.ColorItemWidth,
			UI.ColorItemWidth);
}

void Output::ClearColorPalette()const
{
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(UI.ColorXi, UI.ToolBarHeight, UI.ColorXi * (CLR_ITM_COUNT + UI.ColorItemWidth), UI.ToolBarHeight + UI.ColorItemWidth);
}


void Output::CreatePlayToolBar() const
{
	pWind->SetPen(UI.DrawBarColor, 1);
	pWind->SetBrush(UI.DrawBarColor);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);

	///TODO: write code to create Play mode menu
	string PlayMenuItems[PLAY_ITM_COUNT];
	PlayMenuItems[MENU_SWITCH_DM] = "images\\MenuItems\\Menu_SwitchDM.jpg";
	PlayMenuItems[MENU_PickByColor] = "images\\MenuItems\\Menu_Pick_Color.jpg";
	PlayMenuItems[Menu_PickByShape] = "images\\MenuItems\\Menu_Pick_Shape.jpg";
	PlayMenuItems[Menu_PickByBoth] = "images\\MenuItems\\Menu_Pick_Both.jpg";


	//Draw menu item one image at a time
	for (int i = 0; i < PLAY_ITM_COUNT; i++)
		pWind->DrawImage(PlayMenuItems[i], (i * UI.MenuItemWidth) + (UI.wx * i), UI.wy, UI.MenuItemWidth, UI.ToolBarHeight - UI.wy * 2);

}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::ClearDrawArea() const
{
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(UI.BkGrndColor);
	// test 
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);

}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::PrintMessage(string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar

	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->DrawString(10, UI.height - (int)(UI.StatusBarHeight / 1.5), msg);
}
//////////////////////////////////////////////////////////////////////////////////////////

color Output::getCrntDrawColor() const	//get current drawing color
{
	return UI.DrawColor;
}
void Output::setCrntDrawColor(color newcolor)
{
	UI.DrawBarColor = newcolor;
}
//////////////////////////////////////////////////////////////////////////////////////////

color Output::getCrntFillColor() const	//get current filling color
{
	return UI.FillColor;
}
void Output::setCrntFillColor(color newcolor)
{
	UI.FillColor = newcolor;
}
//////////////////////////////////////////////////////////////////////////////////////////

int Output::getCrntPenWidth() const		//get current pen width
{
	return UI.PenWidth;
}

void Output::ClearToolbar() const
{
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);
}

//======================================================================================//
//								Figures Drawing Functions						  //
//======================================================================================//

void Output::DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
	{
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	}
	else
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWidth);
	drawstyle style;
	if (RectGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else
		style = FRAME;

	pWind->DrawRectangle(P1.x, P1.y, P2.x, P2.y, style);

}
//The Draw_Square function

void Output::DrawSquare(Point p, GfxInfo SqrGfxInfo, bool selected) const
{
	SqrGfxInfo.BorderWidth = UI.PenWidth;
	const int n = 4;
	double angle = atan(1); ;
	int x[n];
	int y[n];

	for (int i = 0; i < n; i++)
	{
		x[i] = p.x + UI.SQUARE_LENGTH * sqrt(2) / 2 * cos(angle);
		y[i] = p.y - UI.SQUARE_LENGTH * sqrt(2) / 2 * sin(angle);
		angle += asin(1);
	}

	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = SqrGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, SqrGfxInfo.BorderWidth);
	drawstyle style;
	if (SqrGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(SqrGfxInfo.FillClr);
	}
	else
		style = FRAME;


	pWind->DrawPolygon(x, y, n, style);

}



//The Draw_triangle function
void Output::DrawTri(Point p1, Point p2, Point p3, GfxInfo TriGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = TriGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, TriGfxInfo.BorderWidth);
	drawstyle style;
	if (TriGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(TriGfxInfo.FillClr);
	}
	else
		style = FRAME;

	pWind->DrawTriangle(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, style);
}


// Draw hexagon function
void Output::DrawHexagon(Point P, GfxInfo HexaGfxInfo, bool selected) const {

	const int n = 6;
	//const int HexagonLength = 100;
	color DrawingClr; 

	// pi/3 value, hexagon is divided into 6 equal parts 
	const double angle = (4.0 / 3.0) * atan(1.0);

	int x[n]; int y[n];

	for (int i = 0; i < n; i++) {
		x[i] = P.x + UI.HEXAGON_LENGTH * cos(angle * i);
		y[i] = P.y - UI.HEXAGON_LENGTH * sin(angle * i);
	}


	if (selected)
		DrawingClr = UI.HighlightColor; 
	else
		DrawingClr = HexaGfxInfo.DrawClr; 

	pWind->SetPen(DrawingClr, HexaGfxInfo.BorderWidth); 

	drawstyle style;
	if (HexaGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(HexaGfxInfo.FillClr);
	}
	else
		style = FRAME;

	pWind->DrawPolygon(x, y, n, style);
}

void Output::DrawCircle(Point P1, Point P2, GfxInfo CircleGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = CircleGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, CircleGfxInfo.BorderWidth);
	drawstyle style;
	if (CircleGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(CircleGfxInfo.FillClr);
	}
	else
		style = FRAME;
	CircleGfxInfo.CircleRadius = sqrt(pow(P1.x - P2.x, 2) + pow(P1.y - P2.y, 2));

	pWind->SetBrush(CircleGfxInfo.FillClr);
	pWind->SetBrush(CircleGfxInfo.FillClr);
	pWind->DrawCircle(P1.x, P1.y, CircleGfxInfo.CircleRadius, style);

}

//////////////////////////////////////////////////////////////////////////////////////////
Output::~Output()
{
	delete pWind;
}



