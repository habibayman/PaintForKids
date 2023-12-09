#include "CRectangle.h"

CRectangle::CRectangle(Point P1, Point P2, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	Corner1 = P1;
	Corner2 = P2;
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
		if (P.x <= x1 + FigGfxInfo.BorderWidth ||          // if the click is at the borders select the rectangle
			P.x >= x2 - FigGfxInfo.BorderWidth ||
			P.y <= y1 + FigGfxInfo.BorderWidth ||
			P.y >= y2 - FigGfxInfo.BorderWidth)
		{
			return true;
		}
		//TODO: if the figure is filled return true
		return false;
	}
	return false;
}