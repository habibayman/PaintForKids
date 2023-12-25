#pragma once
#include "Action.h"
#include "..\Figures\CFigure.h"

class MoveFigureAction : public Action
{
private:
	Point P;   
	CFigure* SelectedFig;
public:
	MoveFigureAction(ApplicationManager* pApp, bool muted);

	//Read the point's parameters
	virtual void ReadActionParameters();

	//Add SelectFigureAction to the ApplicationManager
	virtual void Execute();

	void Undo();
};