#include "SelectFigureAction.h"
#include "..\Figures\CRectangle.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

SelectFigureAction::SelectFigureAction(ApplicationManager* pApp, bool muted) :Action(pApp)
{
if (!muted)
	{
		PlaySound(TEXT("Sounds\\Click"), NULL, SND_SYNC);
	}
}

void SelectFigureAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();


	pOut->PrintMessage("Select a shape, click on it");

	//Read the point clicked
	pIn->GetPointClicked(P1.x, P1.y);

	pOut->ClearStatusBar();
}

void SelectFigureAction::Execute()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	//if the recording isn't playing, read the action parameters first
	bool PlayingRecord = pManager->GetPlayingRecord();

	if (!PlayingRecord)
		ReadActionParameters();

	CFigure* newSelected = pManager->GetFigure(P1);
	CFigure* selected = pManager->GetLastSelected();

	if (!newSelected)
	{
		if (!selected)
		{
			return;
		}

		selected->SetSelected(false);
		selected = nullptr;

		if (Recording())
		{
			pManager->AddRecordedAction(this);
		}

		return;
	}

	newSelected->SetSelected(true);
	//newSelected->ChngDrawClr(UI.HighlightColor);
	pManager->SetLastSelected(newSelected);

	if (selected)
	{
		selected->SetSelected(false);
	}

	//if the action is being recorded, add it to the RecordingList
	if (Recording())
	{
		pManager->AddRecordedAction(this);
	}

}

void SelectFigureAction::Undo()
{
}
