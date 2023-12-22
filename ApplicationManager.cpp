#include "ApplicationManager.h"
#include "Actions\AddRectAction.h"
#include "Actions\AddSquareAction.h"
#include "Actions\AddTriAction.h"
#include "Actions\AddHexaAction.h"
#include "Actions\AddCircleAction.h"
#include "Actions\SelectFigureAction.h"
#include "Actions\SwitchToPlayAction.h"
#include "Actions\MoveFigureAction.h"

//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();

	FigCount = 0;
	LastSelectedFig = NULL;

	//Create an array of figure pointers and set them to NULL		
	for (int i = 0; i < MaxFigCount; i++)
		FigList[i] = NULL;
}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
ActionType ApplicationManager::GetUserAction() const
{
	//Ask the input to get the action from the user.
	return pIn->GetUserAction();
}
////////////////////////////////////////////////////////////////////////////////////
//Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType)
{
	Action* pAct = NULL;

	//According to Action Type, create the corresponding action object
	switch (ActType)
	{
	case DRAW_RECT:
		pAct = new AddRectAction(this);
		break;
	case DRAW_SQUARE:
		pAct = new AddSquareAction(this);
		break;
	case DRAW_HEXA:
		pAct = new AddHexaAction(this);
		break;
	case DRAW_TRIANGLE:
		pAct = new AddTriAction(this);
		break;
	case DRAW_CIRCLE:
		pAct = new AddCircleAction(this);
		break;
	case SELECT_FIGURE:
		pAct = new SelectFigureAction(this);
		break;
	case MOVE_FIGURE:
		pAct = new MoveFigureAction(this);
		break;
	case TO_PLAY:
		pAct = new SwitchToPlayAction(this);
		break;
	case TO_PICK_BY_SHAPE:
		pAct = new PickByShapeAction(this);
		break;
	case TO_PICK_BY_COLOR:
		pAct = new PickByColorAction(this);
		break;
	case EXIT:
		///create ExitAction here

		break;

	case STATUS:	//a click on the status bar ==> no action
		return;
	}

	//Execute the created action
	if (pAct != NULL)
	{
		pAct->Execute();//Execute
		delete pAct;	//You may need to change this line depending to your implementation
		pAct = NULL;
	}
}
//==================================================================================//
//						Figures Management Functions								//
//==================================================================================//

//Add a figure to the list of figures
void ApplicationManager::AddFigure(CFigure* pFig)
{
	if (FigCount < MaxFigCount)
		FigList[FigCount++] = pFig;
}

////////////////////////////////////////////////////////////////////////////////////
CFigure* ApplicationManager::GetFigure(Point P) const
{
	//If a figure is found return a pointer to it.
	//if this point (x,y) does not belong to any figure return NULL
	for (int i = FigCount - 1; i >= 0; i--)
	{
		if (FigList[i]->Isbelonging(P))
		{
			return FigList[i];
		}
	}
	return NULL;
	//Add your code here to search for a figure given a point x,y	
	//Remember that ApplicationManager only calls functions do NOT implement it.
}
//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Function to set pointer to the last selected figure
void ApplicationManager::SetLastSelected(CFigure* pFig)
{
	LastSelectedFig = pFig;
}
//return the  last selected figure
CFigure* ApplicationManager::GetLastSelected()
{
	return LastSelectedFig;
}
//==================================================================================//
//							PlayMode Management Functions							//
//==================================================================================//
int ApplicationManager::RandomFigure(int& TotalFig)
{
	TotalFig = 0;
	int type = rand() % FigCount;
	(FigList[type])->StartGame(pOut);

	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->GetFigureNumber() == FigList[type]->GetFigureNumber())
			TotalFig++;
	}
	
	return FigList[type]->GetFigureNumber();	
}
color ApplicationManager::RandomColor(int& TotalFig)
{
	TotalFig = 0;
	int type = rand() % FigCount;
	(FigList[type])->GetFigureColor();

	{
		if((FigList[type])->GetFigureColor()==BLACK)
		{
			for (int i = 0; i < FigCount; i++)
			{
				if ((FigList[i])->GetFigureColor() == BLACK)
					TotalFig++;
			}
			pOut->PrintMessage("Please Pick all black figures");
			return BLACK;
		}
		if ((FigList[type])->GetFigureColor() == YELLOW)
		{
			for (int i = 0; i < FigCount; i++)
			{
				if ((FigList[i])->GetFigureColor() == YELLOW)
					TotalFig++;
			}
			pOut->PrintMessage("Please Pick all yellow figures");

			return YELLOW;
		}

		if ((FigList[type])->GetFigureColor() == ORANGE)
		{
			for (int i = 0; i < FigCount; i++)
			{
				if ((FigList[i])->GetFigureColor() == ORANGE)
					TotalFig++;
			}
			pOut->PrintMessage("Please Pick all orange figures");

			return ORANGE;
		}
		if ((FigList[type])->GetFigureColor() == RED)
		{
			for (int i = 0; i < FigCount; i++)
			{
				if ((FigList[i])->GetFigureColor() == RED)
					TotalFig++;
			}
			pOut->PrintMessage("Please Pick all red figures");

			return RED;
		}
		if ((FigList[type])->GetFigureColor() == GREEN)
		{
			for (int i = 0; i < FigCount; i++)
			{
				if ((FigList[i])->GetFigureColor() == GREEN)
					TotalFig++;
			}
			pOut->PrintMessage("Please Pick all green figures");

			return GREEN;
		}
		if ((FigList[type])->GetFigureColor() == BLUE)
		{
			for (int i = 0; i < FigCount; i++)
			{
				if ((FigList[i])->GetFigureColor() == BLUE)
					TotalFig++;
			}
			pOut->PrintMessage("Please Pick all blue figures");

			return BLUE;
		}

	}
}
void ApplicationManager::ResetPlayMode()
{
	for (int i = 0; i < FigCount; i++)
	{
		FigList[i]->HideFigure(false);
	}
}





//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{
	for (int i = 0; (i < FigCount); i++)
		if (FigList[i]->FigisHidden() != true)
			FigList[i]->Draw(pOut);	//Call Draw function (virtual member fn)
}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the input
Input* ApplicationManager::GetInput() const
{
	return pIn;
}
//Return a pointer to the output
Output* ApplicationManager::GetOutput() const
{
	return pOut;
}
////////////////////////////////////////////////////////////////////////////////////
//Destructor
ApplicationManager::~ApplicationManager()
{
	for (int i = 0; i < FigCount; i++)
		delete FigList[i];
	delete pIn;
	delete pOut;

}
