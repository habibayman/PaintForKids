#pragma once
#include "Action.h"
class PickByShapeAction :
    public Action
{
	Point P1;
	int ctrTrue;

	

public:


	PickByShapeAction(ApplicationManager* pApp);

	//Reads parameters required for action to execute (code depends on action type)
	virtual void ReadActionParameters();

	//Execute action (code depends on action type)
	virtual void Execute();

	
};

