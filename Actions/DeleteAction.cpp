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
	
	//if the recording isn't playing, read the action parameters first
	//bool PlayingRecord = pManager->GetPlayingRecord();

	ToBeDeleted = pManager->GetLastSelected();
	
	//trying something
	ToBeDeleted->SetSelected(true);
	/*pManager->UpdateInterface();*/

	if (ToBeDeleted)
	{
		pManager->Delete(ToBeDeleted); 
		pOut->ClearDrawArea(); 
		pManager->UpdateInterface();

	}

	else
	{
		pOut->PrintMessage("Please select a figure first to delete it");
	}

	pManager->AddtoUndo(this);
}

void DeleteAction::Undo()
{
	pManager->AddFigure(ToBeDeleted);
	pManager->RemovefromUndo();


	//if the action is being recorded, add it to the RecordingList
	if (Recording())
	{
		pManager->AddRecordedAction(this);
	}

}

