#include "AddCircleAction.h"
#include"Action.h"
#include "UndoAction.h"
#include "..\Figures\CCircle.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

AddCircleAction::AddCircleAction(ApplicationManager* pApp, bool muted) :Action(pApp)
{
	if (!muted)
	{
		PlaySound(TEXT("Sounds\\CircleSound"), NULL, SND_SYNC); 
	}
}

void AddCircleAction::ReadActionParameters()
{

	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Circle: Click at the first point");

	//Read 1st corner and store in point P1
	pIn->GetPointClicked(P1.x, P1.y);

	pOut->PrintMessage("New Circle: Click at the second point");

	//Read 2nd corner and store in point P2
	pIn->GetPointClicked(P2.x, P2.y);
	pIn->Circle_Validation(P1, P2, CircleGfxInfo, pOut);

	CircleGfxInfo.isFilled = pOut->GetFilled();	//set the figure filled/unfilled
	//get drawing, filling colors and pen width from the interface
	CircleGfxInfo.DrawClr = pOut->getCrntDrawColor();
	CircleGfxInfo.FillClr = pOut->getCrntFillColor();

	pOut->ClearStatusBar();

}

void AddCircleAction::Execute()
{
	//if the recording isn't playing, read the action parameters first
	bool PlayingRecord = pManager->GetPlayingRecord();
	if (!PlayingRecord)
		ReadActionParameters();

	//Create a circle with the parameters read from the user
	CCircle* C = new CCircle(P1, P2, CircleGfxInfo);

	//Add the Action to Undo list
	pManager->AddtoUndo(this);

	//Add the circle to the list of figures
	pManager->AddFigure(C);

	//if the action is being recorded, add it to the RecordingList
	if (Recording())
	{
		pManager->AddRecordedAction(this);
	}
}

void AddCircleAction::Undo()
{
	pManager->AddtoRedo(this);
	DeletedFigure = pManager->DeleteLastFigure();
	pManager->RemovefromUndo();
}

void AddCircleAction::Redo()
{
	pManager->AddFigure(DeletedFigure);
	pManager->AddtoUndo(this);
	pManager->RemovefromRedo();
}
