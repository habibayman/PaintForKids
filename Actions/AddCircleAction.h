#pragma once
#include "Action.h"
class AddCircleAction :
	public Action
{
private:

	Point P1;
	Point P2;
	GfxInfo CircleGfxInfo;
public:
	AddCircleAction(ApplicationManager* pApp, bool muted);

	//Reads circle parameters
	virtual void ReadActionParameters();

	//Add circle to the ApplicationManager
	virtual void Execute();

};


