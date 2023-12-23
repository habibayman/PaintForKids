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
	virtual void Move(Point P);
	virtual bool IsValidMove();
	void Save(ofstream& OutFile);
//==================================================================================//
//							PlayMode Management Functions							//
//==================================================================================//
	virtual void StartGame(Output*, int);//Print message to start the game
	virtual int GetFigureNumber();  //Get figure number
	virtual color GetFigureColor(); //Get figure color
	virtual void HideFigure(bool);  //Hide\Unhide the figure
	virtual bool FigisHidden(); //Know if figure is hidden or not
};
