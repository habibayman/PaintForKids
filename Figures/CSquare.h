#pragma once
#include "CFigure.h"
class CSquare :
	public CFigure
{
private:
	Point Center;
public:
	CSquare(Point, GfxInfo FigureGfxInfo);
	virtual void Draw(Output* pOut) const;
	virtual bool Isbelonging(Point P) const;
	virtual void Move(Point P);
	virtual bool IsValid();
//==================================================================================//
//							PlayMode Management Functions							//
//==================================================================================//
	virtual void StartGame(Output* pOut);
	virtual int GetFigureNumber();
	virtual color GetFigureColor();
	virtual void HideFigure(bool);
	virtual bool FigisHidden();

};


