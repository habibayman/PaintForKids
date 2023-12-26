#pragma once
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include "Action.h"
class RedoAction : public Action
{
public:
    RedoAction(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	//Add Redo action to the ApplicationManager
	virtual void Execute();

	//Undo Action
	void Undo();

	//Redo Action
	void Redo();

};

