#include "LoadAction.h"

#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include <fstream>
#include <string>
using namespace std;

LoadAction::LoadAction(ApplicationManager* pApp): Action(pApp)
{}

void LoadAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMessage("Loading...., enter the name of your saved file: ");
	FileName = pIn->GetSrting(pOut) + ".txt";

	pOut->ClearDrawArea();
}
