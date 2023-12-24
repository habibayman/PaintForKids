#include "CCircle.h"
#include <fstream>

CCircle::CCircle(Point P1, Point P2, GfxInfo FigureGfxInfo) : CFigure(FigureGfxInfo)
{
	Center = P1;
	CirclePoint = P2;
	ID++;
	FigureNumber = 5;
	deltaX = deltaY = 0;
	for (int i = 0; i < 5; i++)
	{
		TempDelta[i].x = deltaX;
		TempDelta[i].y = deltaY;
	}
}

CCircle::CCircle()
{
}

void CCircle::Draw(Output* pOut) const
{
	pOut->DrawCircle(Center, CirclePoint, FigGfxInfo, Selected);
}


bool CCircle::Isbelonging(Point P) const
{
	double CircleRadius = sqrt(pow(Center.x - CirclePoint.x, 2) + pow(Center.y - CirclePoint.y, 2));  // radius of the circle 
	double r = sqrt(pow(Center.x - P.x, 2) + pow(Center.y - P.y, 2));  // radius at the point

	//if the radius at the point <= the radius of the circle then the point belongs to the circle
	if (r <= CircleRadius)
	{
		return true;
	}
	return false;
}

void CCircle::Move(Point P)
{
    deltaX = P.x - Center.x;
	deltaY = P.y - Center.y;

	//store delta to undo
	TempDelta[MoveCount].x = deltaX;
	TempDelta[MoveCount++].y = deltaY;

	Center = P;

	CirclePoint.x += deltaX;
	CirclePoint.y += deltaY;
}

void CCircle::UndoMove()
{
	deltaX = TempDelta[MoveCount - 1].x;
	deltaY = TempDelta[MoveCount - 1].y;
	MoveCount--;

	Center.x -= deltaX;
	Center.y -= deltaY;

	CirclePoint.x -= deltaX;
	CirclePoint.y -= deltaY;
}

bool CCircle::IsValid()
{
	// radius of Circle 
	double CircleRadius = sqrt(pow(Center.x - CirclePoint.x, 2) + pow(Center.y - CirclePoint.y, 2));  
	return !(abs(Center.x - UI.wx) < CircleRadius ||
		abs(Center.x - UI.width) < CircleRadius ||
		abs(Center.y - (UI.ToolBarHeight)) < CircleRadius ||
		abs(Center.y - ((UI.height) - UI.StatusBarHeight)) < CircleRadius);
}

void CCircle::Save(ofstream& OutFile)
{
	OutFile << "Circle" << "\t" << ID << "\t"; //type and ID
	OutFile << Center.x << "\t" << Center.y << "\t" << CirclePoint.x << "\t" << CirclePoint.y << "\t"; //Coordinates
	OutFile < FigGfxInfo.DrawClr;
	OutFile << "\t";
	if (FigGfxInfo.isFilled)
	{
		OutFile < FigGfxInfo.FillClr;
	}
	else
	{
		OutFile << "NO_FILL" << "\n";
	}
	//Drawing color and fill color 
}
void CCircle::Load(ifstream& InFile)
{
	InFile >> ID; //Read the ID
	InFile >> Center.x >> Center.y; //Read the center point
	InFile >> CirclePoint.x >> CirclePoint.y; //Read the circle point
	//set FigGfxInfo data
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

void CCircle::PrintInfo(Output* pOut)
{
	string info = "ID: " + to_string(ID) + ", Center (" + to_string(Center.x) + ", " + to_string(Center.y) + "), " +
		"Radius: " + to_string(sqrt(pow(Center.x - CirclePoint.x, 2) + pow(Center.y - CirclePoint.y, 2)));
	pOut->PrintMessage(info);
}


//==================================================================================//
//							PlayMode Management Functions							//
//==================================================================================//
void CCircle::StartGame(Output* pOut, int P)	 //Print a proper message to start the game
{
	if (P == TO_PICK_BY_SHAPE)
		pOut->PrintMessage("Please Pick all CIRCLES");
	else if (P == TO_PICK_BY_COLOR)
		pOut->PrintMessage("Please Pick all Figures with color: " + this->ChosenColorName());
	else if (P == TO_PICK_BY_BOTH)
		pOut->PrintMessage("Please Pick all CIRCLES with color: " + this->ChosenColorName());
}
int CCircle::GetFigureNumber()	//Get figure number
{
	return FigureNumber;
}
color CCircle::GetFigureColor()	//Get figure color
{
	return FigGfxInfo.FillClr;
}
color CCircle::GetDrawColor()
{
	return FigGfxInfo.DrawClr;
}
void CCircle::HideFigure(bool b) //Hide\Unhide the figure
{
	isHidden = b;
}


bool CCircle::FigisHidden()	//Know if figure is hidden or not
{	return isHidden;
}

