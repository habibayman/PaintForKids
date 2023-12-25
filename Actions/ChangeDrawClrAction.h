#pragma once
#include "Action.h"
#include "..\Figures\CFigure.h"
class ChangeDrawClrAction :public Action
{
private:
	CFigure *LastColoredFigure;
	color CurrentClr;
	ColorType ColorSelected;

public:
	ChangeDrawClrAction(ApplicationManager* pApp, bool muted);

	virtual void ReadActionParameters();

	//Add drawClr to the app manager
	virtual void Execute();

	void Undo();

};

