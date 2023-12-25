#pragma once
#include "Action.h"
class AddHexaAction :
	public Action
{
private:
	Point P1; //Hexagon Center
	GfxInfo HexaGfxInfo;
	CFigure* DeletedFigure;
public:
	AddHexaAction(ApplicationManager* pApp, bool muted);

	//Reads Hexagon parameters
	virtual void ReadActionParameters();

	//Add Hexagon to the ApplicationManager
	virtual void Execute();


	//if AddHexaAction is the last action delete this hexagon
	void Undo();

	//redo the deleted hexagon
	void Redo();
};



