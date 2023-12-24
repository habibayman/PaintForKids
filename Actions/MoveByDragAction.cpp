#include "MoveByDragAction.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"



MoveByDragAction::MoveByDragAction(ApplicationManager* pApp) : Action(pApp)
{}

void MoveByDragAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("Move a shape by dragging, Click a point inside the shape ");

	//Read the point clicked
	pIn->GetPointClicked(P.x, P.y);
	pOut->ClearStatusBar();
}

void MoveByDragAction::Execute()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	CFigure* SelectedFig = pManager->GetLastSelected();

	if (SelectedFig)	//checks if there is a selected figure
	{
		ReadActionParameters();
		if (SelectedFig->Isbelonging(P))	//checks that point is inside the figure
		{
			//Loop to handle dragging action
			while (pOut->GetMouseState(LEFT_BUTTON, P.x, P.y) == BUTTON_UP)
			{
				pOut->ClearDrawArea();
				SelectedFig->Move(P);
				if ((SelectedFig->IsValid()))	//checks that point P is inside drawing area 
				{
					pManager->UpdateInterface();
					pOut->PrintMessage("Press the button if you want to drag the shape here");
				}
				else
				{
					pOut->PrintMessage("Invalid Area to drag in , Please move the cursor to any other area");
					SelectedFig->HideFigure(true);	//make sure not to draw in tool bar and status bar
					pManager->UpdateInterface();

				}
				Sleep(200);
				SelectedFig->HideFigure(false);	// to be drawn again in valid areas "look at UpdateInterface function"
				pOut->ClearStatusBar();
			}
		}
		else
		{

			pOut->PrintMessage("Please choose a point inside the figure");
			pOut->ClearStatusBar();

			Execute();
		}
		pOut->ClearDrawArea();
	}
	else
	{
		pOut->PrintMessage("Please select a shape to move it by dragging first");
	}
}
