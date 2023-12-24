#include "Action.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

bool Action::Recording()
{
	Output* pOut = pManager->GetOutput();

	//only record action if RecordsCount is less than Maximum recording Capacity
	if (pManager->GetRecordsCount() <  pManager->GetMaxRecordingCount()  && pManager->GetIsRecording() == true && !pManager->GetPlayingRecord())
		return true;

	if (pManager->GetRecordsCount() == pManager->GetMaxRecordingCount() && pManager->GetIsRecording() == true)
	{
		pManager->SetIsRecording(false);
		pOut->PrintMessage("Recording Stopped; Reached maximum capacity of recorded actions(20)");
		return false;
	}

	//any other case return false
	return false;
}