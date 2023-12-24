#pragma once
#ifndef SELECT_FIGURE_ACTION_H
#define SELECT_FIGURE_ACTION_H

#include "Action.h"
#include "..\Figures\CFigure.h"

class SelectFigureAction : public Action
{
private:
	Point P1;
public:
	SelectFigureAction(ApplicationManager* pApp, bool muted);

	//Read the point's parameters
	virtual void ReadActionParameters();

	//Add SelectFigureAction to the ApplicationManager
	virtual void Execute();
};
#endif

