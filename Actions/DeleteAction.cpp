#include "DeleteAction.h"

#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

DeleteAction::DeleteAction(ApplicationManager* pApp, bool muted): Action(pApp)
{
	if (!muted)
	{
		PlaySound(TEXT("Sounds\\Click"), NULL, SND_SYNC);
	}
}

void DeleteAction::ReadActionParameters() 
{
	
}

void DeleteAction::Execute()
{
	//Get a Pointer to the Output Interfaces
	Output* pOut = pManager->GetOutput(); 
	ToBeDeleted = pManager->GetLastSelected();

	if (ToBeDeleted)
	{
		pManager->Delete(ToBeDeleted);
		ToBeDeleted->SetSelected(false);
	    pOut->ClearDrawArea(); 
	}

	else
	{
		pOut->PrintMessage("Please select a figure first to delete it");
	}

	pManager->AddtoUndo(this);

	//if the action is being recorded, add it to the RecordingList
	if (Recording())
	{
		pManager->AddRecordedAction(this);
	}

}

void DeleteAction::Undo()
{
	pManager->AddFigure(ToBeDeleted);
	pManager->RemovefromUndo();
}

void DeleteAction::Redo()
{
	if(ToBeDeleted != NULL)
	{
	    Output* pOut = pManager->GetOutput();
	    pManager->Delete(ToBeDeleted);
	    pManager->AddtoUndo(this);
	    pOut->ClearDrawArea();
	    pManager->RemovefromRedo();
	}
}


