#pragma once
#include "Action.h"
#include "..\Figures\CFigure.h"
class ChangeDrawClrAction :public Action
{
private:
	CFigure *LastColoredFigure;
	color LastClr;
	color CurrentClr;
	ColorType ColorSelected;

public:
	ChangeDrawClrAction(ApplicationManager* pApp, bool muted);

	virtual void ReadActionParameters();

	//Add drawClr to the app manager
	virtual void Execute();

	//Undo action
	void Undo();

	//Redo action
	void Redo();

};

