#include "StartRecordingAction.h"
#include "Action.h"
#include "..\ApplicationManager.h"

#include "..\GUI\Output.h"


StartRecordingAction::StartRecordingAction(ApplicationManager* pApp, bool muted) : Action(pApp)
{
	if (!muted)
	{
		PlaySound(TEXT("Sounds\\Click"), NULL, SND_SYNC);
	}
}

void StartRecordingAction::ReadActionParameters()
{

}

void StartRecordingAction::Execute()
{
	Output* pOut = pManager->GetOutput();

	//Checks if the program just started or if clear all has been executed
	if (pManager->Get_FigCount() != 0)
		pOut->PrintMessage("Can't record!");

	//Can't record the recording action itself!
	else if (pManager->GetIsRecording())
		pOut->PrintMessage("Can't record while recording already!");

	else
	{
		pOut->PrintMessage("Recording Started");
		//deletes any old recordings first 
		if (pManager->GetRecordsCount() != 0)
			pManager->ClearRecordingList();
		pManager->SetIsRecording(true);
	}

}

void StartRecordingAction::Undo()
{
}

void StartRecordingAction::Redo()
{
}

