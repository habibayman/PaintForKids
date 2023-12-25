#pragma once
#include "Action.h"
#include "..\Figures\CFigure.h"
class ChangeDrawClrAction :public Action
{
private:
	CFigure *LastColoredFigure;
	color CurrentClr;
public:
	ChangeDrawClrAction(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	//Add drawClr to the app manager
	virtual void Execute();

	//Undo action
	void Undo();

	//Redo action
	void Redo();

};

