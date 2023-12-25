#pragma once
#include "Action.h"

class PickByShapeAction :public Action
{
	Point P1;
	int ctrTrue;  //counter of true selected figure

public:
	PickByShapeAction(ApplicationManager* pApp, bool muted);

	//Reads parameters required for action to execute (code depends on action type)
	virtual void ReadActionParameters();

	//Execute action (code depends on action type)
	virtual void Execute();

	void Undo();

	
};

