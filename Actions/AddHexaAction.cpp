#include "AddHexaAction.h"
#include "..\Figures\CHexagon.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"
AddHexaAction::AddHexaAction(ApplicationManager* pApp, bool muted) : Action(pApp)
{
	if (!muted)
	{
		PlaySound(TEXT("Sounds\\HexagonSound"), NULL, SND_SYNC);
	}
}

void AddHexaAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Hexagon: Click at the center point");

	//Read center point and store in point P1
	pIn->GetPointClicked(P1.x, P1.y);
	pIn->Hexagon_Validation(P1, pOut);

	HexaGfxInfo.isFilled = false;	//default is not filled
	//get drawing, filling colors and pen width from the interface
	HexaGfxInfo.DrawClr = pOut->getCrntDrawColor();
	HexaGfxInfo.FillClr = pOut->getCrntFillColor();

	pOut->ClearStatusBar();

}

void AddHexaAction::Execute()
{

	//This action needs to read some parameters first
	ReadActionParameters();

	//Create a square with the parameters read from the user
	CHexagon* H = new CHexagon(P1, HexaGfxInfo);

	//Add the action to Undo list
	pManager->AddtoUndo(this);

	//Add the square to the list of figures
	pManager->AddFigure(H);
}


void AddHexaAction::Undo()
{
	pManager->DeleteLastFigure();
	pManager->RemovefromUndo();
}