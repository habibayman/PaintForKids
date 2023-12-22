#include "PickByShapeAction.h"
#include "..\ApplicationManager.h"
#include"..\Figures\CFigure.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

PickByShapeAction::PickByShapeAction(ApplicationManager* pApp) :Action(pApp)
{
	ctrTrue = 0;
}

void PickByShapeAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pIn->GetPointClicked(P1.x, P1.y);
}

void PickByShapeAction::Execute()
{
	int TotalFig = 0;
	int selected = 0; 
	Output* pOut = pManager->GetOutput();
	int PickedShapeNum = pManager->RandomFigure(TotalFig);
	pManager->ResetPlayMode();
	pManager->UpdateInterface();
	while (ctrTrue != TotalFig)
	{

		ReadActionParameters();
		if ((P1.x >= UI.MenuItemWidth * 2 && P1.x <= UI.MenuItemWidth * 3) && P1.y >= 0 && P1.y <= UI.ToolBarHeight)
			break;
		if (pManager->GetFigure(P1))
		{
			selected++;
			pManager->GetFigure(P1)->HideFigure(true);
			pOut->ClearDrawArea();

			if (PickedShapeNum == pManager->GetFigure(P1)->GetFigureNumber())
			{
				ctrTrue++;
			}
			pOut->PrintMessage(" No. Selected True Figures : " + to_string(ctrTrue)+" No. Selected False Figures :" + to_string(selected - ctrTrue));
			pManager->UpdateInterface();
		}

	}
	if (((P1.x >= UI.MenuItemWidth * 2 && P1.x <= UI.MenuItemWidth * 3) && P1.y >= 0 && P1.y <= UI.ToolBarHeight))
	{
		ctrTrue = 0;
		pManager->ResetPlayMode();
		pManager->UpdateInterface();

		Execute();
	}
	else
		pOut->PrintMessage("CONGRATUS!!GAME FINISHED ! No. Selected True Figures : " + to_string(ctrTrue) + " No. Selected False Figures :" + to_string(selected - ctrTrue));
}

