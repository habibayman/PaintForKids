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
	//This action needs to read some parameters first
	ReadActionParameters();

	if (pManager->GetFigure(P1))
	{
		if (pManager->GetLastSelected())  //If there is a figure selected return true
		{
			if (pManager->GetLastSelected() == pManager->GetFigure(P1)) //if the last figure selected is the figure that I want to select, unselect it
			{
				pManager->GetFigure(P1)->SetSelected(false);
				pManager->SetLastSelected(NULL);
			}
			else                                                     // else if the last figure selected is not the figure I want to select
			{
				pManager->GetLastSelected()->SetSelected(false);     //unselect the figure that is selected
				pManager->GetFigure(P1)->SetSelected(true);          //select the figure that I want to select
				pManager->SetLastSelected(pManager->GetFigure(P1));  //set it as the last selected figure
				//pManager->GetFigure(P1)->PrintInfo(pOut);            // print info of the selected figure
			}
		}
		else                                                        //if no figure is being already selected
		{
			pManager->GetFigure(P1)->SetSelected(true);             //select the figure I want to select
			pManager->SetLastSelected(pManager->GetFigure(P1));     //set it as the last selected figure
			//pManager->GetFigure(P1)->PrintInfo(pOut);               // print info of the selected figure
		}

	}
	else
	{
		if (pManager->GetLastSelected() != NULL)
		{
			pManager->GetLastSelected()->SetSelected(false);
			pManager->SetLastSelected(NULL);
		}
	}
}


