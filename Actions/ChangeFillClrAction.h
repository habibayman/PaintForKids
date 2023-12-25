#pragma once
#include "Action.h"
#include "..\Figures\CFigure.h"
class ChangeFillClrAction :public Action
{
private:
	color  CurrentClr;
	CFigure* LastColoredFigure;
	ColorType ColorSelected;

public:
	ChangeFillClrAction(ApplicationManager* pApp, bool muted);

	//Reads rectangle parameters
	virtual void ReadActionParameters();

	//Add rectangle to the ApplicationManager
	virtual void Execute();

	//if AddRectAction is the last action delete this rectangle
	void Undo();

};
