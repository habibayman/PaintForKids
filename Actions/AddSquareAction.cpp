#include "AddSquareAction.h"
#include "..\Figures\CSquare.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"
AddSquareAction::AddSquareAction(ApplicationManager* pApp) :Action(pApp)
{
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

	SquareGfxInfo.isFilled = false;	//default is not filled
	//get drawing, filling colors and pen width from the interface
	SquareGfxInfo.DrawClr = pOut->getCrntDrawColor();
	SquareGfxInfo.FillClr = pOut->getCrntFillColor();

	pOut->ClearStatusBar();

}

void AddSquareAction::Execute()
{
	//if the recording isn't playing, read the action parameters first
	bool PlayingRecord = pManager->GetPlayingRecord();
	if (!PlayingRecord)
		ReadActionParameters();

	//Create a square with the parameters read from the user
	CSquare* S = new CSquare(P1, SquareGfxInfo);

	//Add the square to the list of figures
	pManager->AddFigure(S);

	//if the action is being recorded, add it to the RecordingLis
	if (Recording())
	{
		pManager->AddRecordedAction(this);
	}
}