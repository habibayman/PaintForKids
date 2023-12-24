#pragma once
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include "Action.h"
class UndoAction : public Action
{
private:
	//static int UndoCount;
	// static Action* Undoarr[5];
public:
	UndoAction(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	//Add Undo and Redo to the ApplicationManager
	virtual void Execute();

	//void AddtoUndo(Action* action);

	void Undo();
	//void AddtoUndoList();
};

