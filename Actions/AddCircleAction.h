#pragma once
#include "Action.h"
class AddCircleAction :
	public Action
{
private:

	Point P1;
	Point P2;
	GfxInfo CircleGfxInfo;
	CFigure* DeletedFigure;
public:
	AddCircleAction(ApplicationManager* pApp, bool muted);

	//Reads circle parameters
	virtual void ReadActionParameters();

	//Add circle to the ApplicationManager
	virtual void Execute();

	//if AddCircleAction is the last action delete this circle
	void Undo();

	//redo the deleted circle
	void Redo();
};


