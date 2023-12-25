#pragma once
#include "CFigure.h"
class CTriangle :
	public CFigure
{
private:
	Point Corner1;
	Point Corner2;
	Point Corner3;
	Point TempDelta[5];
	int deltaX;
	int deltaY;
	string ReadDrawColor, ReadFillColor;

public:
	CTriangle(Point, Point, Point, GfxInfo FigureGfxInfo);
	CTriangle(); 
	virtual void Draw(Output* pOut) const;
	double CalculateTriArea(Point P1, Point P2, Point P3) const;
	virtual bool Isbelonging(Point P) const;
	virtual void Move(Point P);
	void UndoMove();
	virtual bool IsValid();
	virtual void SetID(int);
	void Save(ofstream& OutFile);
	void PrintInfo(Output* pOut);

	void Load(ifstream& InFile); 
//==================================================================================//
//							PlayMode Management Functions							//
//==================================================================================//
	virtual void StartGame(Output*, int);//Print message to start the game
	virtual int GetFigureNumber();  //Get figure number
	virtual color GetFigureColor(); //Get figure color
	virtual color GetDrawColor(); //Get figure color
	virtual void HideFigure(bool);  //Hide\Unhide the figure
	virtual bool FigisHidden(); //Know if figure is hidden or not
	virtual bool FigIsFilled();

};
