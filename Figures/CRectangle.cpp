#include "CRectangle.h"
#include <fstream>

CRectangle::CRectangle(Point P1, Point P2, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	Corner1 = P1;
	Corner2 = P2;
	FigureNumber = 1;
	deltaX = deltaY = 0;
	MoveCount = 0;
	for (int i = 0; i < 5; i++)
	{
		TempDelta[i].x = deltaX;
		TempDelta[i].y = deltaY;
	}
}

CRectangle::CRectangle()
{
	FigureNumber = 1;
	deltaX = deltaY = 0;
	MoveCount = 0;
	for (int i = 0; i < 5; i++)
	{
		TempDelta[i].x = deltaX;
		TempDelta[i].y = deltaY;
	}
}


void CRectangle::Draw(Output* pOut) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	pOut->DrawRect(Corner1, Corner2, FigGfxInfo, Selected);
}


bool CRectangle::Isbelonging(Point P) const
{
	int x1 = Corner1.x;
	int x2 = Corner2.x;
	int y1 = Corner1.y;
	int y2 = Corner2.y;
	if (x1 > x2)   //Make x2 always bigger than x1          
		swap(x1, x2);
	if (y1 > y2)  //Make y2 always bigger than y1        
		swap(y1, y2);

	if (P.x >= x1 && P.x <= x2 && P.y >= y1 && P.y <= y2)  //check that the point is inside the rectangle
	{
		return true;
	}
	return false;
}

void CRectangle::Move(Point P)
{
	//calculting center of old shape
	Point Center;
	Center.x = (Corner1.x + Corner2.x) / 2;
	Center.y = (Corner1.y + Corner2.y) / 2;

    deltaX = P.x - Center.x;
	deltaY = P.y - Center.y;

	//store delta to undo
	TempDelta[MoveCount].x = deltaX;
	TempDelta[MoveCount++].y = deltaY;

	Corner1.x += deltaX;
	Corner2.x += deltaX;

	Corner1.y += deltaY;
	Corner2.y += deltaY;
}

void CRectangle::UndoMove()
{
	deltaX = TempDelta[MoveCount - 1].x;
	deltaY = TempDelta[MoveCount - 1].y;
	MoveCount--;

	Corner1.x -= deltaX;
	Corner2.x -= deltaX;

	Corner1.y -= deltaY;
	Corner2.y -= deltaY;
}

bool CRectangle::IsValidMove()
{
	return !(Corner1.y < UI.ToolBarHeight || Corner1.y > UI.height - UI.StatusBarHeight ||
		Corner2.y < UI.ToolBarHeight || Corner2.y > UI.height - UI.StatusBarHeight);
}

void CRectangle::SetID(int id)
{
	ID = id;
}

void CRectangle::Save(ofstream& OutFile)
{
	OutFile << "Rectangle" << "\t" << ID << "\t"; //type and ID
	OutFile << Corner1.x << "\t" << Corner1.y << "\t" << Corner2.x << "\t" << Corner2.y << "\t"; //Coordinates
	OutFile < FigGfxInfo.DrawClr;
	OutFile << "\t";
	if (FigGfxInfo.isFilled)
	{
		OutFile < FigGfxInfo.FillClr;
		OutFile << "\n";
	}
	else
	{
		OutFile << "NO_FILL";
		OutFile << "\n";
	}
	//Drawing color and fill color 
}


void CRectangle::PrintInfo(Output* pOut)
{
	string info = "ID: " + to_string(ID) + ", Coordinates (" + to_string(Corner1.x) + ", " + to_string(Corner1.y) + "), ("
		+ to_string(Corner2.x) + ", " + to_string(Corner2.y) + ")";
	pOut->PrintMessage(info);
}




//==================================================================================//
//							PlayMode Management Functions							//
//==================================================================================//
void CRectangle::StartGame(Output* pOut, int P)	 //Print a proper message to start the game
{
	if (P == TO_PICK_BY_SHAPE)
		pOut->PrintMessage("Please Pick all RECTANGLES");
	else if(P == TO_PICK_BY_COLOR)
		pOut->PrintMessage("Please Pick all Figures with color: " + this->ChosenColorName());
	else if (P == TO_PICK_BY_BOTH)
		pOut->PrintMessage("Please Pick all RECTANGLES with color: " + this->ChosenColorName());
}
int CRectangle::GetFigureNumber()	//Get figure number
{
	return FigureNumber;
}
color CRectangle::GetFigureColor()	//Get figure color
{
	return FigGfxInfo.FillClr;
}
color CRectangle::GetDrawColor()
{
	return FigGfxInfo.DrawClr;
}
void CRectangle::HideFigure(bool b) //Hide\Unhide the figure
{
	isHidden = b;
}

bool CRectangle::FigisHidden()	//Know if figure is hidden or not
{
	return isHidden;
}

bool CRectangle::FigIsFilled()
{
	if (FigGfxInfo.isFilled)
		return true;
	else
		return false;
}



void CRectangle::Load(ifstream& InFile)
{
	InFile >> ID; //Read the ID
	InFile >> Corner1.x >> Corner1.y; //Read point 1
	InFile >> Corner2.x >> Corner2.y; //Read point 2
	InFile >> ReadDrawColor;
	FigGfxInfo.DrawClr = StringToColor(ReadDrawColor);
	InFile >> ReadFillColor;
	if (ReadFillColor.compare("NO_FILL"))
	{
		FigGfxInfo.isFilled = 1;
		FigGfxInfo.FillClr = StringToColor(ReadFillColor);
	}
	else
	{
		FigGfxInfo.isFilled = 0;
	}
	FigGfxInfo.BorderWidth = UI.PenWidth; 
	Selected = false; 
}
