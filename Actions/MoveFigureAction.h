#pragma once
#include "Action.h"
#include "..\Figures\CFigure.h"

class MoveFigureAction : public Action
{
private:
	Point P;
public:
	MoveFigureAction(ApplicationManager* pApp);

	//Read the point's parameters
	virtual void ReadActionParameters();

	//Add SelectFigureAction to the ApplicationManager
	virtual void Execute();
};