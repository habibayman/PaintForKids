#pragma once
#include "CFigure.h"
class CHexagon :
	public CFigure
{
private:
	Point Center;
public:
	CHexagon(Point, GfxInfo FigureGfxInfo);
	virtual void Draw(Output* pOut) const;
	virtual bool Isbelonging(Point P) const;
};


