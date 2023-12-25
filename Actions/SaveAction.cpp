#include "SaveAction.h"

#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include <fstream>
using namespace std;

SaveAction::SaveAction(ApplicationManager* pApp, bool muted): Action(pApp)
{
	if (!muted)
	{
		PlaySound(TEXT("Sounds\\Click"), NULL, SND_SYNC);
	}
}

void SaveAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput(); 
	pOut->PrintMessage("Saving your Art!, Name your file: ");
	FileName = pIn->GetSrting(pOut) + ".txt";

	pOut->ClearStatusBar();
}

void SaveAction::Execute()
{
	ReadActionParameters();
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput(); 
	Input* pIn = pManager->GetInput(); 
	ofstream OutFile(FileName);
	OutFile < pOut->getCrntDrawColor() ;
	OutFile << "\t";
	OutFile < pOut->getCrntFillColor() ; 
	OutFile << "\n";
	OutFile << pManager->Get_FigCount() << "\n";
	pManager->SaveAll(OutFile);
	OutFile.close();
	pOut->PrintMessage("File saved successfully!");
}

void SaveAction::Undo()
{
}
