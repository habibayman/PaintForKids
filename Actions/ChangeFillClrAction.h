#pragma once
#include "Action.h"
#include "..\Figures\CFigure.h"
class ChangeFillClrAction :public Action
{
private:
	color  CurrentClr;
	CFigure* LastColoredFigure;
public:
	ChangeFillClrAction(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	//add change drawclr to app manager
	virtual void Execute();

	//Undo action
	void Undo();

	//Redo action
	void Redo();

};
