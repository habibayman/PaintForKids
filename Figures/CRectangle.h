#ifndef CRECT_H
#define CRECT_H

#include "CFigure.h"

class CRectangle : public CFigure
{
private:
	Point Corner1;
	Point Corner2;
	Point TempDelta[5];
	int deltaX;
	int deltaY;
	string ReadDrawColor, ReadFillColor;
public:
	CRectangle(Point, Point, GfxInfo FigureGfxInfo);
	CRectangle();
	virtual void Draw(Output* pOut) const;
	virtual bool Isbelonging(Point P) const;
	virtual void Move(Point P);
	void UndoMove();
	virtual bool IsValid();
	virtual void SetID(int);
	void Save(ofstream& OutFile);
	void PrintInfo(Output* pOut);

	void Load(ifstream& InFile);
	
	//virtual void PrintInfo(Output* pOut);
//==================================================================================//
//							PlayMode Management Functions							//
//==================================================================================//
	virtual void StartGame(Output*, int);	//Print message to start the game
	virtual int GetFigureNumber();  //Get figure number
	virtual color GetFigureColor(); //Get figure color
	virtual color GetDrawColor();   //Get draw color
	virtual void HideFigure(bool);  //Hide\Unhide the figure
	virtual bool FigisHidden(); //Know if figure is hidden or not
};

#endif