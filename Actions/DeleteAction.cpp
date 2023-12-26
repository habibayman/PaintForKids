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

	//pManager->AddtoUndo(this);
	//backup = ToBeDeleted; ///////////////////
	
	//trying something
	pOut->ClearDrawArea();
	pManager->UpdateInterface();

	if (ToBeDeleted)
	{
	//	backup = ToBeDeleted;
		pManager->Delete(ToBeDeleted);
	//	ToBeDeleted->SetSelected(false);
	    pOut->ClearDrawArea(); 
		pManager->UpdateInterface();
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
	//if (backup != NULL)
	//{
	//	ToBeDeleted = backup;
	//	pManager->AddFigure(ToBeDeleted);
	//	backup = NULL;
	//	pManager->AddtoRedo(this);
	//	pManager->RemovefromUndo();
	//}
	pManager->AddFigure(ToBeDeleted);
	pManager->RemovefromUndo();


}

void DeleteAction::Redo()
{
	//if(ToBeDeleted != NULL)
	//{
	//	Output* pOut = pManager->GetOutput();
	//	backup = ToBeDeleted;
	//	pManager->Delete(ToBeDeleted);
	//	ToBeDeleted = NULL;
	//	pManager->AddtoUndo(this);
	//	pOut->ClearDrawArea();
	//	pManager->RemovefromRedo();
	//}
}

DeleteAction::~DeleteAction()
{
	//if (backup != NULL)
	//	delete backup;
}

