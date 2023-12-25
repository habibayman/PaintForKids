#pragma once
#include "CFigure.h"
class CCircle :
    public CFigure
{
private:
    Point Center;
    Point CirclePoint;
    Point TempDelta[5];
    int deltaX;
    int deltaY;
    string ReadDrawColor, ReadFillColor;
public:
    CCircle(Point, Point, GfxInfo FigureGfxInfo);
    CCircle();
    virtual void Draw(Output* pOut) const;
    virtual bool Isbelonging(Point P) const;
    virtual void Move(Point P);
    virtual bool IsValidMove();
    void UndoMove();
   
    virtual void SetID(int);
    void Save(ofstream& OutFile);
    void PrintInfo(Output* pOut);
 
    void Load(ifstream& InFile);
//==================================================================================//
//							PlayMode Management Functions							//
//==================================================================================//
    virtual void StartGame(Output*, int);   //Print message to start the game
    virtual int GetFigureNumber();  //Get figure number
    virtual color GetFigureColor(); //Get figure color
    virtual color GetDrawColor();   //Get Draw color
    virtual void HideFigure(bool);  //Hide\Unhide the figure
    virtual bool FigisHidden(); //Know if figure is hidden or not
    virtual bool FigIsFilled();
};

