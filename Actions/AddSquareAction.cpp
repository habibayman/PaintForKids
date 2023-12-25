#include "AddSquareAction.h"
#include "..\Figures\CSquare.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"
AddSquareAction::AddSquareAction(ApplicationManager* pApp, bool muted) :Action(pApp)
{
	if (!muted)
	{
		PlaySound(TEXT("Sounds\\SquareSound"), NULL, SND_SYNC);
	}
}

void AddSquareAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Square: Click at the center point");

	//Read center point and store in point P1
	pIn->GetPointClicked(P1.x, P1.y);
	pIn->Square_Validation(P1, pOut);

	SquareGfxInfo.isFilled = pOut->GetFilled();	//set the figure filled/unfilled
	//get drawing, filling colors and pen width from the interface
	SquareGfxInfo.DrawClr = pOut->getCrntDrawColor();
	SquareGfxInfo.FillClr = pOut->getCrntFillColor();

	pOut->ClearStatusBar();

}

void AddSquareAction::Execute()
{
	//This action needs to read some parameters first
	ReadActionParameters();

	//Create a square with the parameters read from the user
	CSquare* S = new CSquare(P1, SquareGfxInfo);

	//Add the action to Undo list
	pManager->AddtoUndo(this);

	//Add the square to the list of figures
	pManager->AddFigure(S);

}


void AddSquareAction::Undo()
{
	pManager->AddtoRedo(this);
	DeletedFigure = pManager->DeleteLastFigure();
	pManager->RemovefromUndo();
}

void AddSquareAction::Redo()
{
	pManager->AddFigure(DeletedFigure);
}
