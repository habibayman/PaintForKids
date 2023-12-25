#include "ApplicationManager.h"
#include "Actions\AddRectAction.h"
#include "Actions\AddSquareAction.h"
#include "Actions\AddTriAction.h"
#include "Actions\AddHexaAction.h"
#include "Actions\AddCircleAction.h"
#include "Actions\ClearAction.h" 
#include "Actions\DeleteAction.h" 
#include "Actions\LoadAction.h"
#include "Actions\SaveAction.h"
#include "Actions\SelectFigureAction.h"
#include "Actions\SoundModeAction.h"  
#include "Actions\SwitchToPlayAction.h"
#include "Actions\MoveFigureAction.h"\
#include "Actions\MoveByDragAction.h"\
#include "Actions\MoveFigureAction.h"
#include "Actions\UndoAction.h"
#include "Actions\ChangeDrawClrAction.h"
#include "Actions\ChangeFillClrAction.h"
#include "Actions\MoveFigureAction.h"
#include <Windows.h>
#include "MMSystem.h"
//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();

	FigCount = 0;
	UndoCount = 0;
	LastSelectedFig = NULL;
	LastAction = NULL;

	//Create an array of figure pointers and set them to NULL		
	for (int i = 0; i < MaxFigCount; i++)
		FigList[i] = NULL;
	for (int i = 0; i < 5; i++)
		Undoarr[i] = NULL;

	//Sound is played by default
	muted = false;
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
		pAct = new AddRectAction(this, muted);
		break;
	case DRAW_SQUARE:
		pAct = new AddSquareAction(this, muted);
		break;
	case DRAW_HEXA:
		pAct = new AddHexaAction(this, muted);
		break;
	case DRAW_TRIANGLE:
		pAct = new AddTriAction(this,muted); 
		break;
	case DRAW_CIRCLE:
		pAct = new AddCircleAction(this, muted); 
		break;
	case SELECT_FIGURE:
		pAct = new SelectFigureAction(this, muted); 
		break;
	case MOVE_FIGURE:
		pAct = new MoveFigureAction(this, muted);
		break;
	case MOVE_BY_DRAGGING:
		pAct = new MoveByDragAction(this);
		break;
	case SAVE_FIGURE:
		pAct = new SaveAction(this, muted);
		break;
	case TO_LOAD:
		pAct = new LoadAction(this, muted);
		break;
	case TO_PLAY:
		pAct = new SwitchToPlayAction(this, muted);
		break;
	case TO_CLEAR:
		pAct = new ClearAction(this, muted); 
		break;
	case TO_DELETE:
		pAct = new DeleteAction(this, muted);
		break;
	case TO_PICK_BY_SHAPE:
		pAct = new PickByShapeAction(this);
		break;
	case TO_PICK_BY_COLOR:
		pAct = new PickByColorAction(this);
		break;
	case SOUND_MODE:
		pAct = new SoundModeAction(this, &muted);
		break;
	case TO_PICK_BY_BOTH:
		pAct = new PickByBothAction(this);
		break;
	case TO_UNDO:
		pAct = new UndoAction(this);
		break;
	case DRAW_COLOR:
		pAct = new ChangeDrawClrAction(this);
		break;
	case FILL_COLOR:
		pAct = new ChangeFillClrAction(this);
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
		//delete pAct;	//You may need to change this line depending to your implementation
		pAct = NULL;
	}
}
//==================================================================================//
//						Figures Management Functions						   //
//==================================================================================//

//Add a figure to the list of figures
void ApplicationManager::AddFigure(CFigure* pFig)
{
	if (FigCount < MaxFigCount)
	{
		FigList[FigCount++] = pFig;
		FigList[FigCount - 1]->SetID(FigCount);
	}
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
	//return LastSelectedFig;
	bool found = false;
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->IsSelected())
		{
			found = true;
			return FigList[i];
			break;
		}
	} 
	if (!found)
		return NULL;
	return NULL;
}

void ApplicationManager::SaveAll(ofstream& OutFile)
{

	for (int i = 0; i < FigCount; i++)
		FigList[i]->Save(OutFile);
}

int ApplicationManager::Get_FigCount() const
{
	return FigCount;
}

void ApplicationManager::ClearAll()
{
	for (int i = 0; i < FigCount; i++)
	{
		delete FigList[i];
	}
	FigCount = 0;
}

void ApplicationManager::Delete(CFigure* pFig)
{
	int selected_index;
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i] == pFig)
		{
			selected_index = i;
			for (int j = selected_index; j < FigCount - 1; j++)
			{
				swap(FigList[j], FigList[j + 1]);
			}
			delete FigList[FigCount];
			FigCount--;
		}
	}
	UpdateInterface();
}


void ApplicationManager::DeleteLastFigure()
{
	if (FigCount > 0)
	{
		//	return 	FigList[FigCount - 1];
		FigList[FigCount - 1] = FigList[MaxFigCount - 1];
		//	delete FigList[FigCount - 1];
		FigList[MaxFigCount - 1] = NULL;
		FigCount--;
		pOut->ClearDrawArea();
		UpdateInterface();
	}
}

//Check that Undoarr only has 5 actions
void ApplicationManager::AddtoUndo(Action* action)
{
	if (action)                                         // if there is  action done 
	{
		if (UndoCount < 5)                                          // if there is less than 5 actions in undoarr
		{
			Undoarr[UndoCount++] = action;                          // add the last action to the array
		}
		else                                                        // else if the UndoCount is max, delete the first action in the array
		{
			for (int i = 0; i < 4; i++)
			{
				Undoarr[i] = Undoarr[i + 1];
			}
			UndoCount = 4;
			Undoarr[UndoCount++] = action;
		}
	}
}

void ApplicationManager::RemovefromUndo()
{
	if (UndoCount > 0)
	{
		UndoCount--;
	}
	else
		UndoCount = 0;
}

//function that returns the last action to undo it 
Action* ApplicationManager::GetLastActiontoUndo()
{
	if (UndoCount > 0)  // Last action is the Undo 
	{
		LastAction = Undoarr[UndoCount - 1];
		return LastAction;
	}
	return NULL;
}

//==================================================================================//
//							PlayMode Management Functions							//
//==================================================================================//
CFigure* ApplicationManager::RandomFigure(int& TotalFig)
{
	TotalFig = 0;	//initialize number of total  existing figures with the property of the picked one(Figure Game which will be chosen randomly)
	int type = rand() % FigCount;	//choose a random index in FigList array
	


	//counts number of existing figures with same property as the Figure of the Game
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->GetFigureNumber() == FigList[type]->GetFigureNumber())
			TotalFig++;
	}
	
	return FigList[type];		//Return number of the Figure chosen randomly
}
CFigure* ApplicationManager::RandomColor(int& TotalFig)
{
	TotalFig = 0;	//initialize number of total  existing figures with the property of the picked one(Figure Game which will be chosen randomly)
	bool ValidGame = 0;
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->FigIsFilled())
		{
			ValidGame = 1;
			break;
		}
	}
	if (ValidGame ==0)
	{
		return NULL;
	}
	int type = rand() % FigCount;	//choose a random index in FigList array
	while (FigList[type]->FigIsFilled() == 0) 
	{
		type = rand() % FigCount;
	}
	//counts number of existing figures with same property as the Figure of the Game
			for (int i = 0; i < FigCount; i++)
			{
				if ((FigList[i])->GetFigureColor() == (FigList[type])->GetFigureColor()
					&& FigList[i]->FigIsFilled())
					TotalFig++;
			}
			return FigList[type];	//Return  color of the Figure chosen randomly
}
CFigure* ApplicationManager::RandomColoredFigure(int& TotalFig)
{
	TotalFig = 0;	//initialize number of total  existing figures with the property of the picked one(Figure Game which will be chosen randomly)
	bool ValidGame = 0;
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->FigIsFilled())
		{
			ValidGame = 1;
			break;
		}
	}
	if (ValidGame == 0)
	{
		return NULL;
	}
	int type = rand() % FigCount;	//choose a random index in FigList array
	while (FigList[type]->FigIsFilled() == 0)
	{
		type = rand() % FigCount;
	}
	for (int i = 0; i < FigCount; i++)
	{
		if ((FigList[i])->GetFigureColor() == (FigList[type])->GetFigureColor()&&
			( FigList[i]->GetFigureNumber() == FigList[type]->GetFigureNumber())
			&& FigList[i]->FigIsFilled())
			TotalFig++;
	}
	return FigList[type];	//Return the color of the Figure chosen randomly
}
void ApplicationManager::ResetPlayMode()
{
	for (int i = 0; i < FigCount; i++)
	{
		FigList[i]->HideFigure(false);	//Unhide all the figures
	}
}



//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{
	for (int i = 0; (i < FigCount); i++)
		if (FigList[i]->FigisHidden() != true) // to make sure not to draw a hidden figure
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
