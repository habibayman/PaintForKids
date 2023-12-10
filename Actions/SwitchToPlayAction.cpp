#include "SwitchToPlayAction.h"
#include "Action.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"


SwitchToPlayAction::SwitchToPlayAction(ApplicationManager* pApp) : Action(pApp)
{
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

	ReadActionParameters();

	//Switching to Play Mode
	UI.InterfaceMode = MODE_PLAY;
	pOut->CreatePlayToolBar();
}