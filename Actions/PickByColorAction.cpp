#include "PickByColorAction.h"

PickByColorAction::PickByColorAction(ApplicationManager* pApp, bool muted) :Action(pApp)
{
    ctrTrue = 0;
	if (!muted)
	{
		PlaySound(TEXT("Sounds\\Click"), NULL, SND_SYNC);
	}
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


	if (PickedFigure == NULL)
	{
		pOut->PrintMessage("No filled figures on screen,choose another game");
	}
	else
	{
		// to redraw the figures if the kid wants to play again after finishing the game
		pManager->ResetPlayMode();
		pManager->UpdateInterface();

		PickedFigure->StartGame(pOut, TO_PICK_BY_COLOR);	// Start the game 

		while (ctrTrue != TotalFig)
		{

			ReadActionParameters();
			if ((P1.x >= UI.MenuItemWidth && P1.x <= UI.MenuItemWidth * 2) && P1.y >= 0 && P1.y <= UI.ToolBarHeight)	//Game Reset condition
				break;
			if (pManager->GetFigure(P1) && pManager->GetFigure(P1)->FigisHidden() == false)   //checks if the kid clicked on a figure and hide this figure
			{
				selected++;
				pManager->GetFigure(P1)->HideFigure(true);
				pOut->ClearDrawArea();

				//checks if the kid clicked on a  true figure 
				if (PickedFigure->GetFigureColor() == pManager->GetFigure(P1)->GetFigureColor()&& pManager->GetFigure(P1)->FigIsFilled())
				{
					ctrTrue++;
				}
				pOut->PrintMessage("True picks : " + to_string(ctrTrue) + " vs. False picks :" + to_string(selected - ctrTrue));
				pManager->UpdateInterface();
			}

		}

		//Game Reset while playing
		if (((P1.x >= UI.MenuItemWidth && P1.x <= UI.MenuItemWidth * 2) && P1.y >= 0 && P1.y <= UI.ToolBarHeight))
		{
			ctrTrue = 0;
			pManager->ResetPlayMode();
			pManager->UpdateInterface();

			Execute();
		}
		else
		{
			pOut->PrintMessage("CONGRATS!!GAME FINISHED ! Number of true picks : " + to_string(ctrTrue) + " vs. Number of false picks :" + to_string(selected - ctrTrue));
			PlaySound(TEXT("Sounds\\ApplauseSound"), NULL, SND_SYNC); 
		}
	}
}

void PickByColorAction::Undo() {}
void PickByColorAction::Redo() {}

