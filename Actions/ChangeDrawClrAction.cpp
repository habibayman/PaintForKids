#include "ChangeDrawClrAction.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include "..\Figures\CFigure.h"

ChangeDrawClrAction::ChangeDrawClrAction(ApplicationManager* pApp, bool muted) :Action(pApp)
{
	Output* pOut = pManager->GetOutput();
	LastColoredFigure = NULL;
	LastClr = pOut->getCrntDrawColor();

	if (!muted)
	{
		PlaySound(TEXT("Sounds\\Click"), NULL, SND_SYNC);
	}
}

void ChangeDrawClrAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	
	pOut->PrintMessage("Choose drawing color from the pallete");
	pOut->CreateColorPalette();
	ColorSelected = pIn->GetColor();
}

void ChangeDrawClrAction::Execute()
{
	// Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//if the recording isn't playing, read the action parameters first
	bool PlayingRecord = pManager->GetPlayingRecord();

	if (!PlayingRecord)
	{
		ReadActionParameters();
	}

	if (pManager->GetLastSelected())
	{
		LastColoredFigure = pManager->GetLastSelected();
		LastClr = LastColoredFigure->GetDrawColor();

			switch (ColorSelected)
			{
			case COLOR_GREEN:
				pOut->PrintMessage("Drawing color is now the green color");
				LastColoredFigure->ChngDrawClr(GREEN);
				pOut->setCrntDrawColor(GREEN);
				CurrentClr = GREEN;
				pManager->AddtoUndo(this);
				break;
			case COLOR_RED:
				pOut->PrintMessage("Drawing color is now the red color");
				LastColoredFigure->ChngDrawClr(RED);
				pOut->setCrntDrawColor(RED);
				CurrentClr = RED;
				pManager->AddtoUndo(this);
				break;
			case COLOR_ORANGE:
				pOut->PrintMessage("Drawing color is now the orange color");
				LastColoredFigure->ChngDrawClr(ORANGE);
				pOut->setCrntDrawColor(ORANGE);
				CurrentClr = ORANGE;
				pManager->AddtoUndo(this);
				break;
			case COLOR_YELLOW:
				pOut->PrintMessage("Drawing color is now the yellow color");
				LastColoredFigure->ChngDrawClr(YELLOW);
				pOut->setCrntDrawColor(YELLOW);
				CurrentClr = YELLOW;
				pManager->AddtoUndo(this);
				break;
			case COLOR_BLUE:
				pOut->PrintMessage("Drawing color is now the blue color");
				LastColoredFigure->ChngDrawClr(BLUE);
				pOut->setCrntDrawColor(BLUE);
				CurrentClr = BLUE;
				pManager->AddtoUndo(this);
				break;
			case COLOR_BLACK:
				pOut->PrintMessage("Drawing color is now the black color");
				LastColoredFigure->ChngDrawClr(BLACK);
				pOut->setCrntDrawColor(BLACK);
				CurrentClr = BLACK;
				pManager->AddtoUndo(this);
				break;
			}

		pOut->ClearColorPalette();
	}

	else
	{
		pOut->PrintMessage("Please select a figure first");
	}

	//if the action is being recorded, add it to the RecordingList
	if (Recording())
	{
		pManager->AddRecordedAction(this);
	}

}

void ChangeDrawClrAction::Undo()
{
	Output* pOut = pManager->GetOutput();

	LastColoredFigure->ChngDrawClr(LastClr);
	pOut->setCrntDrawColor(LastClr);

	pManager->AddtoRedo(this);
	pManager->RemovefromUndo();
}

void ChangeDrawClrAction::Redo()
{
	Output* pOut = pManager->GetOutput();

	LastColoredFigure->ChngDrawClr(CurrentClr);
	pOut->setCrntDrawColor(CurrentClr);

	pManager->AddtoUndo(this);
	pManager->RemovefromRedo();
}

