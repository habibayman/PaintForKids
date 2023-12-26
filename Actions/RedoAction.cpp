#include "RedoAction.h"

RedoAction::RedoAction(ApplicationManager* pApp):Action(pApp)
{}

void RedoAction::ReadActionParameters() {}

void RedoAction::Execute() 
{
	Output* pOut = pManager->GetOutput();

	pOut->PrintMessage("Redo last action");
	Action* action = pManager->GetLastActiontoRedo();
	//Undo the last action in the undo list
	if (action)
	{
		action->Redo();
	}
	else                                                //if there is no action
	{
		pOut->PrintMessage("No more actions to redo, undo an action first");
	}

	//if the action is being recorded, add it to the RecordingList
	if (Recording())
	{
		pManager->AddRecordedAction(this);
	}
}

void RedoAction::Undo() {}
void RedoAction::Redo() {}
