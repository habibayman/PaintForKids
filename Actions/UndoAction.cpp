#include "UndoAction.h"
#include "Action.h"


UndoAction::UndoAction(ApplicationManager* pApp, bool muted) : Action(pApp)
{
	if (!muted)
	{
		PlaySound(TEXT("Sounds\\Click"), NULL, SND_SYNC);
	}
}

void UndoAction::ReadActionParameters()
{}

void UndoAction::Execute()
{
	Output* pOut = pManager->GetOutput();

	pOut->PrintMessage("Undo last action");

	Action* action = pManager->GetLastActiontoUndo();
	//Undo the last action in the undo list
	if (action)
	{
		action->Undo();
		//pManager->AddtoRedo(action);
	}
	else                                                //if there is no action
	{
		pOut->PrintMessage("No more actions to undo");
	}
	

	//if the action is being recorded, add it to the RecordingList
	if (Recording())
	{
		pManager->AddRecordedAction(this);
	}
}


void UndoAction::Undo() {}
void UndoAction::Redo() {}
