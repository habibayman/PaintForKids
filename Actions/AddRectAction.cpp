
#include "AddRectAction.h"
#include "..\Figures\CRectangle.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

AddRectAction::AddRectAction(ApplicationManager * pApp, bool muted):Action(pApp)
{
	if (!muted)
	{
		PlaySound(TEXT("Sounds\\RectangleSound"), NULL, SND_SYNC);
	}
}

void AddRectAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Rectangle: Click at first corner");

	//Read 1st corner and store in point P1
	pIn->GetPointClicked(P1.x, P1.y);
	pIn->Point_Validation(P1, pOut);

	pOut->PrintMessage("New Rectangle: Click at second corner");

	//Read 2nd corner and store in point P2
	pIn->GetPointClicked(P2.x, P2.y);
	pIn->Repeatability_Validation(P1, P2, pOut);

		RectGfxInfo.isFilled = pOut->GetFilled();	//set the figure filled/unfilled
		//get drawing, filling colors and pen width from the interface
		RectGfxInfo.DrawClr = pOut->getCrntDrawColor();
		RectGfxInfo.FillClr = pOut->getCrntFillColor();
	RectGfxInfo.isFilled = false;	//default is not filled
	//get drawing, filling colors and pen width from the interface
	RectGfxInfo.DrawClr = pOut->getCrntDrawColor();
	RectGfxInfo.FillClr = pOut->getCrntFillColor();

	pOut->ClearStatusBar();

}

//Execute the action
void AddRectAction::Execute()
{
	//if the recording isn't playing, read the action parameters first
	bool PlayingRecord = pManager->GetPlayingRecord();
	if (!PlayingRecord)
		ReadActionParameters();

	//Create a rectangle with the parameters read from the user
	CRectangle* R = new CRectangle(P1, P2, RectGfxInfo);

	//Add the action to Undo list
	pManager->AddtoUndo(this);

	//Add the rectangle to the list of figures
	pManager->AddFigure(R);

	if (Recording())
	{
		pManager->AddRecordedAction(this);
	}
}


	void AddRectAction::Undo()
	{
		pManager->AddtoRedo(this);
		DeletedFigure = pManager->DeleteLastFigure();
		pManager->RemovefromUndo();
	}

	void AddRectAction::Redo()
	{
		pManager->AddFigure(DeletedFigure);
		pManager->AddtoUndo(this);
		pManager->RemovefromRedo();
	}
void AddRectAction::Undo()
{
	pManager->DeleteLastFigure();
	pManager->RemovefromUndo();
}
