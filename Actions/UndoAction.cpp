#include "UndoAction.h"
#include "Action.h"


UndoAction::UndoAction(ApplicationManager* pApp) : Action(pApp)
{}

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
	//	pManager->AddtoRedo(action);
	}
	else                                                //if there is no action
	{
		pOut->PrintMessage("No more actions to undo");
	}
	
}


void UndoAction::Undo() {}
void UndoAction::Redo() {}
