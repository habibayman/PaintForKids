#include "UndoAction.h"
#include "Action.h"

//int UndoAction::UndoCount = 0;
//Action* UndoAction::Undoarr[5];

UndoAction::UndoAction(ApplicationManager* pApp) : Action(pApp)
{}

void UndoAction::ReadActionParameters()
{}

void UndoAction::Execute()
{
	Output* pOut = pManager->GetOutput();

	pOut->PrintMessage("Undo Icon");

	Action* action = pManager->GetLastActiontoUndo();
	//Undo the last action in the undo list
	if (action)
	{
		action->Undo();
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
