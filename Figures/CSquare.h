#pragma once
#include "CFigure.h"
class CSquare :
	public CFigure
{
private:
	Point Center;
	Point TempCenter[5];  //to store the center before moving the figure && 5 is the max number of actions to undo
public:
	CSquare(Point, GfxInfo FigureGfxInfo);
	virtual void Draw(Output* pOut) const;
	virtual bool Isbelonging(Point P) const;
	virtual void Move(Point P);
	void UndoMove();
	virtual bool IsValid();
	void Save(ofstream& OutFile);
	void PrintInfo(Output* pOut);

//==================================================================================//
//							PlayMode Management Functions							//
//==================================================================================//
	virtual void StartGame(Output*, int);//Print message to start the game
	virtual int GetFigureNumber();  //Get figure number
	virtual color GetFigureColor(); //Get figure color
	virtual color GetDrawColor();   //Get draw color
	virtual void HideFigure(bool);  //Hide\Unhide the figure
	virtual bool FigisHidden(); //Know if figure is hidden or not
};


