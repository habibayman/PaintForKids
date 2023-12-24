#include "CCircle.h"
#include <fstream>

CCircle::CCircle(Point P1, Point P2, GfxInfo FigureGfxInfo) : CFigure(FigureGfxInfo)
{
	Center = P1;
	CirclePoint = P2;
	FigureNumber = 5;

	
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
		if (r >= CircleRadius - FigGfxInfo.BorderWidth)
		{
			return true;
		}
		//TODO: if circle is filled return true
		return false;
	}
	return false;
}

void CCircle::Move(Point P)
{
	int deltaX = P.x - Center.x;
	int deltaY = P.y - Center.y;

	Center = P;

	CirclePoint.x += deltaX;
	CirclePoint.y += deltaY;
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

void CCircle::SetID(int id)
{
	ID = id;
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

//==================================================================================//
//							PlayMode Management Functions							//
//==================================================================================//
void CCircle :: StartGame(Output* pOut, int P)	 //Print a proper message to start the game
{
	if (P == TO_PICK_BY_SHAPE)
	pOut->PrintMessage ("Please Pick all CIRCLES");
	else if (P == TO_PICK_BY_COLOR)
	pOut->PrintMessage("Please Pick all Figures with color: "+ this->ChosenColorName());
	else if(P == TO_PICK_BY_BOTH)
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
void CCircle::HideFigure(bool b) //Hide\Unhide the figure
{
	isHidden = b;
}

bool CCircle::FigisHidden()	//Know if figure is hidden or not
{
	return isHidden;
}

