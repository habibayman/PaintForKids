#include "ChangeFillClrAction.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include "..\Figures\CFigure.h"

ChangeFillClrAction::ChangeFillClrAction(ApplicationManager* pApp) :Action(pApp)
{
	LastColoredFigure = NULL;
	CurrentClr = UI.FillColor;
}

void ChangeFillClrAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Choose color to fill the shape");
}

void ChangeFillClrAction::Execute()
{
	// Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	ColorType ColorSelected;

	if (pManager->GetLastSelected())
	{
		LastColoredFigure = pManager->GetLastSelected();
		CurrentClr = LastColoredFigure->GetFigureColor();

			pOut->CreateColorPalette();
			ColorSelected = pIn->GetColor();
			switch (ColorSelected)
			{
			case COLOR_GREEN:
				pOut->PrintMessage("The shape is filled with green color");
				LastColoredFigure->ChngFillClr(GREEN);
				pOut->setCrntFillColor(GREEN);
				break;
			case COLOR_RED:
				pOut->PrintMessage("The shape is filled with red color");
				LastColoredFigure->ChngFillClr(RED);
				pOut->setCrntFillColor(RED);
				break;
			case COLOR_ORANGE:
				pOut->PrintMessage("The shape is filled with orange color");
				LastColoredFigure->ChngFillClr(ORANGE);
				pOut->setCrntFillColor(ORANGE);
				break;
			case COLOR_YELLOW:
				pOut->PrintMessage("The shape is filled with yellow color");
				LastColoredFigure->ChngFillClr(YELLOW);
				pOut->setCrntFillColor(YELLOW);
				break;
			case COLOR_BLUE:
				pOut->PrintMessage("The shape is filled with blue color");
				LastColoredFigure->ChngFillClr(BLUE);
				pOut->setCrntFillColor(BLUE);
				break;
			case COLOR_BLACK:
				pOut->PrintMessage("The shape is filled with black color");
				LastColoredFigure->ChngFillClr(BLACK);
				pOut->setCrntFillColor(BLACK);
				break;
			}
		pOut->ClearColorPalette();
		pOut->SetFilled(true);
		pManager->AddtoUndo(this);
	}
	else
	{
		pOut->PrintMessage("Please select a figure first");
	}
}

void ChangeFillClrAction::Undo()
{
	Output* pOut = pManager->GetOutput();
	LastColoredFigure->ChngFillClr(CurrentClr);
	pOut->SetFilled(true);
	pManager->AddtoRedo(this);
	pManager->RemovefromUndo();
}

void ChangeFillClrAction::Redo()
{
}
