#include "CTriangle.h"

CTriangle::CTriangle(Point P1, Point P2, Point P3, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	Corner1 = P1;
	Corner2 = P2;
	Corner3 = P3;
	FigureNumber = 3;

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
	//calculate length of three sides

	float l12 = sqrt(pow(Corner1.x - Corner2.x, 2) + pow(Corner1.y - Corner2.y, 2));
	float l13 = sqrt(pow(Corner1.x - Corner3.x, 2) + pow(Corner1.y - Corner3.y, 2));
	float l23 = sqrt(pow(Corner2.x - Corner3.x, 2) + pow(Corner2.y - Corner3.y, 2));

	//calculate length between each vertex and the point

	float P1P = sqrt(pow(Corner1.x - P.x, 2) + pow(Corner1.y - P.y, 2));
	float P2P = sqrt(pow(Corner2.x - P.x, 2) + pow(Corner2.y - P.y, 2));
	float P3P = sqrt(pow(Corner3.x - P.x, 2) + pow(Corner3.y - P.y, 2));

	//Calculate the area of the total triangle and subtriangles
	double TotalArea = CalculateTriArea(Corner1, Corner2, Corner3);
	double A1 = CalculateTriArea(P, Corner1, Corner2);
	double A2 = CalculateTriArea(P, Corner1, Corner3);
	double A3 = CalculateTriArea(P, Corner2, Corner3);

	// Check if the sum of the areas of the sub-triangles is equal to the total area
	if (fabs((P1P + P2P) - l12) < 0.1 ||
		fabs((P1P + P3P) - l13) < 0.1 ||
		fabs((P2P + P3P) - l23) < 0.1)
	{
		return true;
	}

	/*if (TotalArea == (A1 + A2 + A3))
	{
		// TODO: if figure is filled return true
	}
	*/
	return false;
}

void CTriangle::Move(Point P)
{
	Point Center;
	Center.x = (Corner1.x + Corner2.x + Corner3.x) / 3;
	Center.y = (Corner1.y + Corner2.y + Corner3.y) / 3;

	int deltaX = P.x - Center.x;
	int deltaY = P.y - Center.y;

	Corner1.x += deltaX;
	Corner2.x += deltaX;
	Corner3.x += deltaX;

	Corner1.y += deltaY;
	Corner2.y += deltaY;
	Corner3.y += deltaY;
}

bool CTriangle:: IsValid()
{
	return !(Corner1.y < UI.ToolBarHeight || Corner1.y > UI.height - UI.StatusBarHeight ||
		Corner2.y < UI.ToolBarHeight || Corner2.y > UI.height - UI.StatusBarHeight ||
		Corner3.y < UI.ToolBarHeight || Corner3.y > UI.height - UI.StatusBarHeight);
}

//==================================================================================//
//							PlayMode Management Functions							//
//==================================================================================//
void CTriangle::StartGame(Output* pOut)
{
	pOut->PrintMessage("Please Pick all Triangles");

}
int CTriangle::GetFigureNumber()
{
	return FigureNumber;
}
color CTriangle::GetFigureColor()
{
	return FigGfxInfo.FillClr;
}
void CTriangle::HideFigure(bool b)
{
	isHidden = b;

}

bool CTriangle::FigisHidden()
{
	return isHidden;
}
