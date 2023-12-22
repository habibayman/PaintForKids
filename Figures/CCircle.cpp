#include "CCircle.h"

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

//==================================================================================//
//							PlayMode Management Functions							//
//==================================================================================//
void CCircle::StartGame(Output* pOut)
{
	pOut->PrintMessage("Please Pick all Circles");
}
int CCircle::GetFigureNumber()
{
	return FigureNumber;
}
void CCircle::HideFigure(bool b)
{
	isHidden = b;
}

bool CCircle::FigisHidden()
{
	return isHidden;
}
