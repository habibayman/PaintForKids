#include "Action.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

bool Action::Recording()
{
	Output* pOut = pManager->GetOutput();

	//only record action if RecordsCount is less than Maximum recording Capacity
	if (pManager->GetRecordsCount() < pManager->GetMaxRecordingCount() && pManager->GetIsRecording() == true && !pManager->GetPlayingRecord())
	{
		if (pManager->GetRecordsCount() == pManager->GetMaxRecordingCount() - 1)
		{
			pOut->PrintMessage("Recording Stopped, Reached maximum capacity of recorded actions(20)");
			pManager->SetIsRecording(false);
			//return true to record last possible action and set IsRecording to false to not record any more actions
		}

		return true;
	}

	else
	{
		pManager->SetIsRecording(false);
		return false;
	}

}