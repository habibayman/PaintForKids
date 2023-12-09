#include "CCircle.h"

CCircle::CCircle(Point P1, Point P2, GfxInfo FigureGfxInfo) : CFigure(FigureGfxInfo)
{
	Center = P1;
	CirclePoint = P2;
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

