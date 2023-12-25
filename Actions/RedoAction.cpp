#include "RedoAction.h"

RedoAction::RedoAction(ApplicationManager* pApp):Action(pApp)
{}

void RedoAction::ReadActionParameters() {}

void RedoAction::Execute() 
{
	Output* pOut = pManager->GetOutput();

	Action* action = pManager->GetLastActiontoRedo();
	//Undo the last action in the undo list
	if (action)
	{
		action->Redo();
	}
	else                                                //if there is no action
	{
		pOut->PrintMessage("No more actions to undo");
	}
}

void RedoAction::Undo() {}
void RedoAction::Redo() {}
