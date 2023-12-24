#include "ClearAction.h"

#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include <string>

ClearAction::ClearAction(ApplicationManager* pApp): Action(pApp)
{}

void ClearAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMessage("Are you sure you want to clear all? this will delete all your work (y/n): ");
	checker = pIn->GetSrting(pOut);

	pOut->ClearStatusBar();
}

void ClearAction::Execute()
{
	ReadActionParameters(); 
	if (checker == "y" || checker == "Y")
	{
		Output* pOut = pManager->GetOutput();
		pOut->ClearDrawArea();
		pManager->ClearAll();
		pOut->PrintMessage("All cleared!");
	}
}

void ClearAction::Undo()
{
}

