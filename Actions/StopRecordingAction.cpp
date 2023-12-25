#include "StopRecordingAction.h"
#include "Action.h"
#include "..\ApplicationManager.h"

#include "..\GUI\Output.h"

StopRecordingAction::StopRecordingAction(ApplicationManager* pApp, bool muted) : Action(pApp)
{
	if (!muted)
	{
		PlaySound(TEXT("Sounds\\Click"), NULL, SND_SYNC);
	}
}

void StopRecordingAction::ReadActionParameters()
{

}

void StopRecordingAction::Execute()
{
	Output* pOut = pManager->GetOutput();

	if (pManager->GetIsRecording())
	{
		pManager->SetIsRecording(false);
		pOut->PrintMessage("Recording was stopped");
	}

	else 
	{
		pOut->PrintMessage("No recording to stop!");
	}
}

void StopRecordingAction::Undo()
{

}
