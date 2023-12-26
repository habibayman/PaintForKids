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

	HexaGfxInfo.isFilled = pOut->GetFilled();	//set the figure filled/unfilled
	//get drawing, filling colors and pen width from the interface
	HexaGfxInfo.DrawClr = pOut->getCrntDrawColor();
	HexaGfxInfo.FillClr = pOut->getCrntFillColor();

	pOut->ClearStatusBar();

}

void AddHexaAction::Execute()
{
	//if the recording isn't playing, read the action parameters first
	bool PlayingRecord = pManager->GetPlayingRecord();
	if (!PlayingRecord)
		ReadActionParameters();

	//Create a hexagon with the parameters read from the user
	CHexagon* H = new CHexagon(P1, HexaGfxInfo);

	//Add a hexagon to the list of figures
	//Add the action to Undo list
	pManager->AddtoUndo(this);

	//Add the square to the list of figures
	pManager->AddFigure(H);

	//if the action is being recorded, add it to the RecordingList
	if (Recording())
	{
		pManager->AddRecordedAction(this);
	}

}


void AddHexaAction::Undo()
{
	pManager->AddtoRedo(this);
	DeletedFigure = pManager->DeleteLastFigure();
	pManager->RemovefromUndo();
}

void AddHexaAction::Redo()
{
	pManager->AddFigure(DeletedFigure);
	pManager->AddtoUndo(this);
	pManager->RemovefromRedo();
}
