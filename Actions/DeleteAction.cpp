#include "DeleteAction.h"

#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

DeleteAction::DeleteAction(ApplicationManager* pApp): Action(pApp)
{}

void DeleteAction::ReadActionParameters() 
{
	ToBeDeleted = pManager->GetLastSelected();
}

void DeleteAction::Execute()
{
	//Get a Pointer to the Output Interfaces
	Output* pOut = pManager->GetOutput(); 
	
	//if the recording isn't playing, read the action parameters first
	bool PlayingRecord = pManager->GetPlayingRecord();

	ReadActionParameters();

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


	//if the action is being recorded, add it to the RecordingList
	if (Recording())
	{
		pManager->AddRecordedAction(this);
	}

}

