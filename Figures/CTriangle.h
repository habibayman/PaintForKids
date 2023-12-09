#pragma once
#include "CFigure.h"
class CTriangle :
	public CFigure
{
private:
	Point Corner1;
	Point Corner2;
	Point Corner3;

public:
	CTriangle(Point, Point, Point, GfxInfo FigureGfxInfo);
	virtual void Draw(Output* pOut) const;
	double CalculateTriArea(Point P1, Point P2, Point P3) const;
	virtual bool Isbelonging(Point P) const;
};
