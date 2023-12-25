#include "ChangeDrawClrAction.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include "..\Figures\CFigure.h"

ChangeDrawClrAction::ChangeDrawClrAction(ApplicationManager* pApp) :Action(pApp)
{
	LastColoredFigure = NULL;
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
		CurrentClr = LastColoredFigure->GetDrawColor();

			switch (ColorSelected)
			{
			case COLOR_GREEN:
				pOut->PrintMessage("Drawing color is now the green color");
				pManager->GetLastSelected()->ChngDrawClr(GREEN);
				UI.DrawColor = GREEN;
				break;
			case COLOR_RED:
				pOut->PrintMessage("Drawing color is now the red color");
				pManager->GetLastSelected()->ChngDrawClr(RED);
				UI.DrawColor = RED;
				break;
			case COLOR_ORANGE:
				pOut->PrintMessage("Drawing color is now the orange color");
				pManager->GetLastSelected()->ChngDrawClr(ORANGE);
				UI.DrawColor = ORANGE;
				break;
			case COLOR_YELLOW:
				pOut->PrintMessage("Drawing color is now the yellow color");
				pManager->GetLastSelected()->ChngDrawClr(YELLOW);
				UI.DrawColor = YELLOW;
				break;
			case COLOR_BLUE:
				pOut->PrintMessage("Drawing color is now the blue color");
				pManager->GetLastSelected()->ChngDrawClr(BLUE);
				UI.DrawColor = BLUE;
				break;
			case COLOR_BLACK:
				pOut->PrintMessage("Drawing color is now the black color");
				pManager->GetLastSelected()->ChngDrawClr(BLACK);
				UI.DrawColor = BLACK;
				break;
			}

		pOut->ClearColorPalette();
		pManager->AddtoUndo(this);

		//if the action is being recorded, add it to the RecordingList
		//if (Recording())
		//{
		//	pManager->AddRecordedAction(this);
		//}
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
	LastColoredFigure->ChngDrawClr(CurrentClr);
	pManager->RemovefromUndo();
}

