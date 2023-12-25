#pragma once
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include "Action.h"
class UndoAction : public Action
{
public:
	UndoAction(ApplicationManager* pApp, bool muted);

	virtual void ReadActionParameters();

	//Add Undo to the ApplicationManager
	virtual void Execute();
	void Undo();
	void Redo();
};

