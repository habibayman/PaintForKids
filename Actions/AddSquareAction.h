#pragma once
#include "Action.h"
class AddSquareAction :
	public Action
{
private:
	Point P1; //Square Center
	GfxInfo SquareGfxInfo;
	CFigure* DeletedFigure;
public:
	AddSquareAction(ApplicationManager* pApp, bool muted);

	//Reads square parameters
	virtual void ReadActionParameters();

	//Add square to the ApplicationManager
	virtual void Execute();

	//if AddSquareAction is the last action delete this square
	void Undo();

	//Redo the deleted square
	void Redo();
};

