#ifndef CRECT_H
#define CRECT_H

#include "CFigure.h"

class CRectangle : public CFigure
{
private:
	Point Corner1;
	Point Corner2;
public:
	CRectangle(Point, Point, GfxInfo FigureGfxInfo);
	virtual void Draw(Output* pOut) const;
	virtual bool Isbelonging(Point P) const;
	virtual void Move(Point P);
	virtual bool IsValid();
	void Save(ofstream& OutFile);
	
	//virtual void PrintInfo(Output* pOut);
//==================================================================================//
//							PlayMode Management Functions							//
//==================================================================================//
	virtual void StartGame(Output*, int);	//Print message to start the game
	virtual int GetFigureNumber();  //Get figure number
	virtual color GetFigureColor(); //Get figure color
	virtual void HideFigure(bool);  //Hide\Unhide the figure
	virtual bool FigisHidden(); //Know if figure is hidden or not
};

#endif