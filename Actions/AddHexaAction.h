#pragma once
#include "Action.h"
class AddHexaAction :
	public Action
{
private:
	Point P1; //Hexagon Center
	GfxInfo HexaGfxInfo;
public:
	AddHexaAction(ApplicationManager* pApp);

	//Reads Hexagon parameters
	virtual void ReadActionParameters();

	//Add Hexagon to the ApplicationManager
	virtual void Execute();
};



