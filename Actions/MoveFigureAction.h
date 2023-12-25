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

	//Add MoveAction to the ApplicationManager
	virtual void Execute();

	//Undo Action
	void Undo();

	//Redo Action
	void Redo();
};