#pragma once
#include "Action.h"
class MoveByDragAction :
    public Action
{
private:
	Point P;
public:
	MoveByDragAction(ApplicationManager* pApp);

	//Read the point's parameters
	virtual void ReadActionParameters();

	//Add SelectFigureAction to the ApplicationManager
	virtual void Execute();
	void Undo();
	void Redo();

};

