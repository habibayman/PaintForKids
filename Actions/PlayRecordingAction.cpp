#include "PlayRecordingAction.h"
#include "Action.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

PlayRecordingAction::PlayRecordingAction(ApplicationManager* pApp, bool muted) : Action(pApp)
{
	if (!muted)
	{
		PlaySound(TEXT("Sounds\\Click"), NULL, SND_SYNC);
	}
}

void PlayRecordingAction::ReadActionParameters()
{}

void PlayRecordingAction::Execute()
{
	Output* pOut = pManager->GetOutput();

	if (pManager->GetIsRecording())
		pOut->PrintMessage("Can't play the recording while recording!");
	
	else if (pManager->GetRecordsCount() == 0)
		pOut->PrintMessage("No recorded actions to play!");

	else
	{
		pOut->PrintMessage("Playing the recording");

		//Perform clear all Action first 

		pManager->ClearAll(); //clears FigList and Sets FigCount to zero
		pManager->ClearUndoList(); //clears undo list 
		pOut->ClearDrawArea();
		pManager->SetLastSelected(NULL);
		pManager->SetPlayingRecord(true);
	
		for (int i = 0; i < pManager->GetRecordsCount(); i++)
		{
			pManager->PlayRecording(i);
			//sleeps 1 second between each two operations
			if (i % 2 == 0)
				_sleep(1000);
			pOut->ClearDrawArea();
			pManager->UpdateInterface();
		}
	}

	//after playing the recording reset the play recording state to false
	pManager->SetPlayingRecord(false);
	pOut->ClearStatusBar();

}

void PlayRecordingAction::Undo()
{
}

void PlayRecordingAction::Redo() {}
