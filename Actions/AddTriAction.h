#pragma once
#include "Action.h"
class AddTriAction :
	public Action
{
private:
	Point P1, P2, P3; //Rectangle Corners
	GfxInfo TriGfxInfo;
public:
	AddTriAction(ApplicationManager* pApp, bool muted);

	//Reads rectangle parameters
	virtual void ReadActionParameters();

	//Add rectangle to the ApplicationManager
	virtual void Execute();
};

