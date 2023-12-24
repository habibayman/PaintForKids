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
	ToBeDeleted = pManager->GetLastSelected(); 
}

void DeleteAction::Execute()
{
	//Get a Pointer to the Output Interfaces
	Output* pOut = pManager->GetOutput(); 
	ReadActionParameters();
	if (ToBeDeleted)
	{
		pManager->Delete(ToBeDeleted); 
		pOut->ClearDrawArea(); 
	}
	else
	{
		pOut->PrintMessage("Please select a figure first to delete it");
	}
}
