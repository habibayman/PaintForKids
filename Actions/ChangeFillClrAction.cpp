#include "ChangeFillClrAction.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include "..\Figures\CFigure.h"

ChangeFillClrAction::ChangeFillClrAction(ApplicationManager* pApp, bool muted) :Action(pApp)
{
	Output* pOut = pManager->GetOutput();
	LastColoredFigure = NULL;
	LastClr = pOut->getCrntFillColor();
	CurrentClr = NULL;
	if (!muted)
	{
		PlaySound(TEXT("Sounds\\Click"), NULL, SND_SYNC);
	}
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
		LastClr = LastColoredFigure->GetFigureColor();

		bool PlayingRecord = pManager->GetPlayingRecord();
		
		if (!PlayingRecord)
		{
			ReadActionParameters();
		}

			switch (ColorSelected)
			{
			case COLOR_GREEN:
				pOut->PrintMessage("The shape is filled with green color");
				CurrentClr = GREEN;
				LastColoredFigure->ChngFillClr(CurrentClr);
				pOut->setCrntFillColor(CurrentClr);
				pOut->SetFilled(true);
				pManager->AddtoUndo(this);
				break;
			case COLOR_RED:
				pOut->PrintMessage("The shape is filled with red color");
				CurrentClr = RED;
				LastColoredFigure->ChngFillClr(CurrentClr);
				pOut->setCrntFillColor(CurrentClr);
				pOut->SetFilled(true);
				pManager->AddtoUndo(this);
				break;
			case COLOR_ORANGE:
				pOut->PrintMessage("The shape is filled with orange color");
				CurrentClr = ORANGE;
				LastColoredFigure->ChngFillClr(CurrentClr);
				pOut->setCrntFillColor(CurrentClr);
				pOut->SetFilled(true);
				pManager->AddtoUndo(this);
				break;
			case COLOR_YELLOW:
				pOut->PrintMessage("The shape is filled with yellow color");
				CurrentClr = YELLOW;
				LastColoredFigure->ChngFillClr(CurrentClr);
				pOut->setCrntFillColor(CurrentClr);
				pOut->SetFilled(true);
				pManager->AddtoUndo(this);
				break;
			case COLOR_BLUE:
				pOut->PrintMessage("The shape is filled with blue color");
				CurrentClr = BLUE;
				LastColoredFigure->ChngFillClr(CurrentClr);
				pOut->setCrntFillColor(CurrentClr);
				pOut->SetFilled(true);
				pManager->AddtoUndo(this);
				break;
			case COLOR_BLACK:
				pOut->PrintMessage("The shape is filled with black color");
				CurrentClr = BLACK;
				LastColoredFigure->ChngFillClr(CurrentClr);
				pOut->setCrntFillColor(CurrentClr);
				pOut->SetFilled(true);
				pManager->AddtoUndo(this);
				break;
			case NO_COLOR:
				pOut->PrintMessage("Click on the color pallete");
				CurrentClr = LastClr;
			}
		//	pManager->AddtoUndo(this);
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

void ChangeFillClrAction::Undo()
{
	Output* pOut = pManager->GetOutput();

	LastColoredFigure->ChngFillClr(LastClr);
	pOut->setCrntFillColor(LastClr);
	
	if (LastClr == UI.BkGrndColor)
	{
		LastColoredFigure->SetFilled(false);
		pOut->ClearDrawArea();
	}
	
	pManager->AddtoRedo(this);
	pManager->RemovefromUndo();
}

void ChangeFillClrAction::Redo()
{
	Output* pOut = pManager->GetOutput();

	LastColoredFigure->ChngFillClr(CurrentClr);
	pOut->setCrntFillColor(CurrentClr);

	pManager->AddtoUndo(this);
	pManager->RemovefromRedo();
}
