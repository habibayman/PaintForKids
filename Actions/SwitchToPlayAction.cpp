#include "SwitchToPlayAction.h"
#include "Action.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"


SwitchToPlayAction::SwitchToPlayAction(ApplicationManager* pApp, bool muted) : Action(pApp)
{
	if (!muted)
	{
		PlaySound(TEXT("Sounds\\Click"), NULL, SND_SYNC);
	}
}

void SwitchToPlayAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Switch to Play Mode");
}

void SwitchToPlayAction::Execute()
{
	//Get a Pointer  Output Interfaces
	Output* pOut = pManager->GetOutput();
	if (pManager->Get_FigCount() != 0)
	{
		ReadActionParameters();

		//Switching to Play Mode
		UI.InterfaceMode = MODE_PLAY;
		pOut->CreatePlayToolBar();
	}
	else
	{
		pOut->PrintMessage("Please draw some figures to switch to Play Mode");
	}
}
	

void SwitchToPlayAction::Undo()
{
}
