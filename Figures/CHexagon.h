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
	virtual void Move(Point P);
	virtual bool IsValid();
//==================================================================================//
//							PlayMode Management Functions							//
//==================================================================================//
	virtual string StartGame();
	virtual int GetFigureNumber();
	virtual color GetFigureColor();
	virtual void HideFigure(bool);
	virtual bool FigisHidden();

};


