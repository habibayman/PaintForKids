#pragma once
#include "CFigure.h"
class CCircle :
    public CFigure
{
private:
    Point Center;
    Point CirclePoint;
public:
    CCircle(Point, Point, GfxInfo FigureGfxInfo);
    virtual void Draw(Output* pOut) const;
    virtual bool Isbelonging(Point P) const;
    virtual void Move(Point P);
    virtual bool IsValid();
//==================================================================================//
//							PlayMode Management Functions							//
//==================================================================================//
    virtual void StartGame(Output*, int);   //Print message to start the game
    virtual int GetFigureNumber();  //Get figure number
    virtual color GetFigureColor(); //Get figure color
    virtual void HideFigure(bool);  //Hide\Unhide the figure
    virtual bool FigisHidden(); //Know if figure is hidden or not
};

