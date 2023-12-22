#include "PickByColorAction.h"

PickByColorAction::PickByColorAction(ApplicationManager* pApp) :Action(pApp)
{
ctrTrue = 0;
}

void PickByColorAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pIn->GetPointClicked(P1.x, P1.y);
}

void PickByColorAction::Execute()
{
	int TotalFig = 0;//Total Figures on screen with the property of the picked one(Figure Game which had been chosen randomly)
	int selected = 0;//Total Figures chosen by the kid
	Output* pOut = pManager->GetOutput();
	CFigure* PickedFigure = pManager->RandomColor(TotalFig);//to get the Figure Game Color

	// to redraw the figures if the kid wants to play again after finishing the game
	pManager->ResetPlayMode();
	pManager->UpdateInterface();

	PickedFigure->StartGame(pOut, TO_PICK_BY_COLOR);	// Start the game 

	while (ctrTrue != TotalFig)
	{

		ReadActionParameters();
		if ((P1.x >= UI.MenuItemWidth  && P1.x <= UI.MenuItemWidth * 2) && P1.y >= 0 && P1.y <= UI.ToolBarHeight)	//Game Reset condition
			break;
		if (pManager->GetFigure(P1))   //checks if the kid clicked on a figure and hide this figure
		{
			selected++;
			pManager->GetFigure(P1)->HideFigure(true);
			pOut->ClearDrawArea();

			//checks if the kid clicked on a  true figure 
			if (PickedFigure->GetFigureColor() == pManager->GetFigure(P1)->GetFigureColor())
			{
				ctrTrue++;
			}
			pOut->PrintMessage(" Number of Selected True Figures : " + to_string(ctrTrue) + ". Number of Selected False Figures :" + to_string(selected - ctrTrue));
			pManager->UpdateInterface();
		}

	}

	//Game Reset while playing
	if (((P1.x >= UI.MenuItemWidth  && P1.x <= UI.MenuItemWidth * 2) && P1.y >= 0 && P1.y <= UI.ToolBarHeight))
	{
		ctrTrue = 0;
		pManager->ResetPlayMode();
		pManager->UpdateInterface();

		Execute();
	}
	else
		pOut->PrintMessage("CONGRATUS!!GAME FINISHED !Number of Selected True Figures : " + to_string(ctrTrue) + ". Number of Selected False Figures :" + to_string(selected - ctrTrue));
}
