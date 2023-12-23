#include "StopRecordingAction.h"
#include "Action.h"
#include "..\ApplicationManager.h"

#include "..\GUI\Output.h"

StopRecordingAction::StopRecordingAction(ApplicationManager* pApp) : Action(pApp)
{

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
