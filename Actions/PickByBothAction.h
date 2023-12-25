#pragma once
#include "Action.h"
#include "..\ApplicationManager.h"
#include"..\Figures\CFigure.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"


class PickByBothAction : public Action
{
	Point P1;
	int ctrTrue; //counter of true selected figure
public:
	PickByBothAction(ApplicationManager* pApp, bool muted);

	//Reads parameters required for action to execute (code depends on action type)
	virtual void ReadActionParameters();

	//Execute action (code depends on action type)
	virtual void Execute();

	void Undo();
};

