#include "ChangeDrawClrAction.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include "..\Figures\CFigure.h"

ChangeDrawClrAction::ChangeDrawClrAction(ApplicationManager* pApp) :Action(pApp)
{
	LastColoredFigure = NULL;
	CurrentClr = UI.DrawColor;
}

void ChangeDrawClrAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Choose drawing color from the pallete");
}

void ChangeDrawClrAction::Execute()
{
	// Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	ColorType ColorSelected;

	if (pManager->GetLastSelected())
	{
		LastColoredFigure = pManager->GetLastSelected();
		CurrentClr = LastColoredFigure->GetDrawColor();

			pOut->CreateColorPalette();
			ColorSelected = pIn->GetColor();
			switch (ColorSelected)
			{
			case COLOR_GREEN:
				pOut->PrintMessage("Drawing color is now the green color");
				LastColoredFigure->ChngDrawClr(GREEN);
				pOut->setCrntDrawColor(GREEN);
				break;
			case COLOR_RED:
				pOut->PrintMessage("Drawing color is now the red color");
				LastColoredFigure->ChngDrawClr(RED);
				pOut->setCrntDrawColor(RED);
				break;
			case COLOR_ORANGE:
				pOut->PrintMessage("Drawing color is now the orange color");
				LastColoredFigure->ChngDrawClr(ORANGE);
				pOut->setCrntDrawColor(ORANGE);
				break;
			case COLOR_YELLOW:
				pOut->PrintMessage("Drawing color is now the yellow color");
				LastColoredFigure->ChngDrawClr(YELLOW);
				pOut->setCrntDrawColor(YELLOW);
				break;
			case COLOR_BLUE:
				pOut->PrintMessage("Drawing color is now the blue color");
				LastColoredFigure->ChngDrawClr(BLUE);
				pOut->setCrntDrawColor(BLUE);
				break;
			case COLOR_BLACK:
				pOut->PrintMessage("Drawing color is now the black color");
				LastColoredFigure->ChngDrawClr(BLACK);
				pOut->setCrntDrawColor(BLACK);
				break;
			}
		pOut->ClearColorPalette();
		pOut->SetFilled(false);
		pManager->AddtoUndo(this);
	}
	else
	{
		pOut->PrintMessage("Please select a figure first");
	}
}

void ChangeDrawClrAction::Undo()
{
	LastColoredFigure->ChngDrawClr(CurrentClr);
	pManager->AddtoRedo(this);
	pManager->RemovefromUndo();
}

void ChangeDrawClrAction::Redo()
{

}

