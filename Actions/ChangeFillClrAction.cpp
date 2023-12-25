#include "ChangeFillClrAction.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include "..\Figures\CFigure.h"

ChangeFillClrAction::ChangeFillClrAction(ApplicationManager* pApp) :Action(pApp)
{
	LastColoredFigure = NULL;
	CurrentClr = NULL;
}

void ChangeFillClrAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	
	pOut->PrintMessage("Choose color to fill the shape");
	pOut->CreateColorPalette();
	ColorSelected = pIn->GetColor();
}

void ChangeFillClrAction::Execute()
{
	// Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();


	if (pManager->GetLastSelected())
	{
		LastColoredFigure = pManager->GetLastSelected();
		CurrentClr = LastColoredFigure->GetFigureColor();

		bool PlayingRecord = pManager->GetPlayingRecord();
		
		if (!PlayingRecord)
		{
			ReadActionParameters();
		}

			switch (ColorSelected)
			{
			case COLOR_GREEN:
				pOut->PrintMessage("The shape is filled with green color");
				pManager->GetLastSelected()->ChngFillClr(GREEN);
				UI.FillColor = GREEN;
				break;
			case COLOR_RED:
				pOut->PrintMessage("The shape is filled with red color");
				pManager->GetLastSelected()->ChngFillClr(RED);
				UI.FillColor = RED;
				break;
			case COLOR_ORANGE:
				pOut->PrintMessage("The shape is filled with orange color");
				pManager->GetLastSelected()->ChngFillClr(ORANGE);
				UI.FillColor = ORANGE;
				break;
			case COLOR_YELLOW:
				pOut->PrintMessage("The shape is filled with yellow color");
				pManager->GetLastSelected()->ChngFillClr(YELLOW);
				UI.FillColor = YELLOW;
				break;
			case COLOR_BLUE:
				pOut->PrintMessage("The shape is filled with blue color");
				pManager->GetLastSelected()->ChngFillClr(BLUE);
				UI.FillColor = BLUE;
				break;
			case COLOR_BLACK:
				pOut->PrintMessage("The shape is filled with black color");
				pManager->GetLastSelected()->ChngFillClr(BLACK);
				UI.FillColor = BLACK;
				break;
			}

		pOut->ClearColorPalette();
		pManager->AddtoUndo(this);

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

void ChangeFillClrAction::Undo()
{
	LastColoredFigure->ChngFillClr(CurrentClr);
	pManager->RemovefromUndo();
}
