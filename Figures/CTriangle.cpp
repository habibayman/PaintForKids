#include "CTriangle.h"
#include <fstream>

CTriangle::CTriangle(Point P1, Point P2, Point P3, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	Corner1 = P1;
	Corner2 = P2;
	Corner3 = P3;
	ID++;
	FigureNumber = 3;
	deltaX = deltaY = 0;
	for (int i = 0; i < 5; i++)
	{
		TempDelta[i].x = deltaX;
		TempDelta[i].y = deltaY;
	}
}

void CTriangle::Draw(Output* pOut) const
{
	pOut->DrawTri(Corner1, Corner2, Corner3, FigGfxInfo, Selected);
}

//Area of triangle with using coordinates is: A = (1/2) |x1(y2 − y3) + x2(y3 − y1) + x3(y1 − y2)|
double CTriangle::CalculateTriArea(Point P1, Point P2, Point P3) const
{
	return (0.5 * abs(P1.x * (P2.y - P3.y) + P2.x * (P3.y - P1.y) + P3.x * (P1.y - P2.y)));
}

bool CTriangle::Isbelonging(Point P) const
{
	//Calculate the area of the total triangle and subtriangles
	double TotalArea = CalculateTriArea(Corner1, Corner2, Corner3);
	double A1 = CalculateTriArea(P, Corner1, Corner2);
	double A2 = CalculateTriArea(P, Corner1, Corner3);
	double A3 = CalculateTriArea(P, Corner2, Corner3);

	// Check if the sum of the areas of the sub-triangles is equal to the total area
	if (TotalArea == (A1 + A2 + A3))
	{
		return true;
	}
	return false;
}

void CTriangle::Move(Point P)
{
	Point Center;
	Center.x = (Corner1.x + Corner2.x + Corner3.x) / 3;
	Center.y = (Corner1.y + Corner2.y + Corner3.y) / 3;

	deltaX = P.x - Center.x;
    deltaY = P.y - Center.y;

	//store delta to undo
	TempDelta[MoveCount].x = deltaX;
	TempDelta[MoveCount++].y = deltaY;

	Corner1.x += deltaX;
	Corner2.x += deltaX;
	Corner3.x += deltaX;

	Corner1.y += deltaY;
	Corner2.y += deltaY;
	Corner3.y += deltaY;
}

void CTriangle::UndoMove()
{
	deltaX = TempDelta[MoveCount - 1].x;
	deltaY = TempDelta[MoveCount - 1].y;
	MoveCount--;

	Corner1.x -= deltaX;
	Corner2.x -= deltaX;
	Corner3.x -= deltaX;

	Corner1.y -= deltaY;
	Corner2.y -= deltaY;
	Corner3.y -= deltaY;
}

bool CTriangle:: IsValid()
{
	return !(Corner1.y < UI.ToolBarHeight || Corner1.y > UI.height - UI.StatusBarHeight ||
		Corner2.y < UI.ToolBarHeight || Corner2.y > UI.height - UI.StatusBarHeight ||
		Corner3.y < UI.ToolBarHeight || Corner3.y > UI.height - UI.StatusBarHeight);
}

void CTriangle::Save(ofstream& OutFile)
{
	OutFile << "Triangle" << "\t" << ID << "\t"; //type and ID
	OutFile << Corner1.x << "\t" << Corner1.y << "\t" << Corner2.x << "\t" << Corner2.y << "\t" << Corner3.x << "\t" << Corner3.y << "\t"; //Coordinates
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

void CTriangle::PrintInfo(Output* pOut)
{
	string info = "ID: " + to_string(ID) + ", Coordinates (" + to_string(Corner1.x) + ", " + to_string(Corner1.y) + "), ("
		+ to_string(Corner2.x) + ", " + to_string(Corner2.y) + "), (" + to_string(Corner3.x) + ", " + to_string(Corner3.y) + ")";
	pOut->PrintMessage(info);
}


//==================================================================================//
//							PlayMode Management Functions							//
//==================================================================================//
void CTriangle::StartGame(Output* pOut, int P)	 //Print a proper message to start the game
{
	if(P == TO_PICK_BY_SHAPE)
		pOut->PrintMessage("Please Pick all TRIANGLES");
	else if(P == TO_PICK_BY_COLOR)
		pOut->PrintMessage("Please Pick all Figures with color: " + this->ChosenColorName());
	else if (P == TO_PICK_BY_BOTH)
		pOut->PrintMessage("Please Pick all TRIANGLES with color: " + this->ChosenColorName());
}

int CTriangle::GetFigureNumber()	//Get figure number
{
	return FigureNumber;
}
color CTriangle::GetFigureColor()	//Get figure color
{
	return FigGfxInfo.FillClr;
}
color CTriangle::GetDrawColor()
{
	return FigGfxInfo.DrawClr;
}
void CTriangle::HideFigure(bool b) //Hide\Unhide the figure
{
	isHidden = b;
}

bool CTriangle::FigisHidden()	//Know if figure is hidden or not
{
	return isHidden;
}
