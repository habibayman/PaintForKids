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
#include "Actions\MoveFigureAction.h"
#include "Actions\UndoAction.h"
#include "Actions\RedoAction.h"
#include "Actions\MoveByDragAction.h"
#include "Actions\ChangeDrawClrAction.h"
#include "Actions\ChangeFillClrAction.h"
#include "Actions\UndoAction.h"
#include "Actions\ChangeDrawClrAction.h"
#include "Actions\ChangeFillClrAction.h"
#include "Actions\PlayRecordingAction.h"
#include "Actions\StartRecordingAction.h"
#include "Actions\StopRecordingAction.h"
#include "Actions\SwitchToPlayAction.h"
#include "Actions\SwitchToDrawAction.h"


#include <Windows.h>
#include "MMSystem.h"
//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();

	FigCount = 0;
	UndoCount = RedoCount = 0;
	RedoStatus = false;
	LastSelectedFig = NULL;
	LastAction = NULL;

	//Create an array of figure pointers and set them to NULL		
	for (int i = 0; i < MaxFigCount; i++)
		FigList[i] = NULL;
	for (int i = 0; i < MaxUndoRedoCount; i++)

	//Create an array of figure pointers and set them to NULL		
	for (int i = 0; i < MaxFigCount; i++)
		FigList[i] = NULL;

	RecordsCount = 0;
	IsRecording = false;
	PlayingRecord = false;

	//Create an array of Action pointers and set them to NULL
	for (int j = 0; j < MaxRecordingCount; j++)
		RecordingList[j] = NULL;

	for (int i = 0; i < 5; i++)
		Undoarr[i] = NULL;
	for (int i = 0; i < MaxUndoRedoCount; i++)
		Redoarr[i] = NULL;


	RecordsCount = 0;
	IsRecording = false;
	PlayingRecord = false;

	//Create an array of Action pointers and set them to NULL
	for (int j = 0; j < MaxRecordingCount; j++)
		RecordingList[j] = NULL;

	for (int i = 0; i < 5; i++)
		Undoarr[i] = NULL;

	//Sound is played by default
	muted = false;
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
		pAct = new MoveByDragAction(this, muted);
		break;
	case SAVE_FIGURE:
		pAct = new SaveAction(this, muted);
		break;
	case START_RECORDING:
		pAct = new StartRecordingAction(this, muted);
		break;
	case PLAY_RECORDING:
		pAct = new PlayRecordingAction(this, muted);
		break;
	case STOP_RECORDING:
		pAct = new StopRecordingAction(this, muted);
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
		pAct = new PickByShapeAction(this, muted);
		break;
	case TO_PICK_BY_COLOR:
		pAct = new PickByColorAction(this, muted);
		break;
	case SOUND_MODE:
		pAct = new SoundModeAction(this, &muted);
		break;
	case TO_PICK_BY_BOTH:
		pAct = new PickByBothAction(this, muted);
		break;
	case TO_UNDO:
		pAct = new UndoAction(this, muted);
		break;
	case TO_REDO:
		pAct = new RedoAction(this);
		break;
	case DRAW_COLOR:
		pAct = new ChangeDrawClrAction(this, muted);
		break;
	case FILL_COLOR:
		pAct = new ChangeFillClrAction(this, muted);
		break;
	case TO_DRAW:
		pAct = new SwitchToDrawAction(this, muted);
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
		pAct = NULL;
	}
}
//==================================================================================//
//						Figures Management Functions						   //
//==================================================================================//

//Add a figure to the list of figures
void ApplicationManager::AddFigure(CFigure* pFig, bool ToSaveID)
{
	if (FigCount < MaxFigCount)
	{
		FigList[FigCount++] = pFig;
		//To create unique consecutive IDs, excecpt when loading, we don't want to override the original IDs
		if (ToSaveID) 
		{
			FigList[FigCount - 1]->SetID(FigCount);
		}
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
		FigList[i] = NULL;
	}
	FigCount = 0;

	if (!IsRecording)
	{
		for (int i = 0; i < RedoCount - 1; i++)
		{
			Redoarr[i] = NULL;
		}
		RedoCount = 0;

		for (int i = 0; i < UndoCount - 1; i++)
		{
			Undoarr[i] = NULL;
		}
		UndoCount = 0;
		pOut->SetFilled(false);
	}
	else
	{
		IsRecording = false;
		pOut->PrintMessage("Recording was stopped");
	}

	//default draw/color mode for the shapes
	pOut->setCrntDrawColor(BLUE);
	pOut->setCrntFillColor(WHITE);
	pOut->SetFilled(false);
}

void ApplicationManager::Delete(CFigure* pFig)
{
	
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i] == pFig)
		{
			for (int j = i ; j < FigCount - 1; j++)
			{
				swap(FigList[j], FigList[j + 1]);
			}
			FigList[FigCount - 1] = NULL;
			FigCount--;
			break;
		}
	}
	UpdateInterface();
}


CFigure* ApplicationManager::DeleteLastFigure()
{
	if (FigCount > 0)
	{
		CFigure* DeletedFig = FigList[FigCount - 1];
		FigList[FigCount - 1] = FigList[MaxFigCount - 1];
		FigList[MaxFigCount - 1] = NULL;
		FigCount--;
		pOut->ClearDrawArea();
		UpdateInterface();
		return DeletedFig;
	}
}

//Check that Undoarr only has 5 actions
void ApplicationManager::AddtoUndo(Action* action)
{
	if (action) //if there is  action done 
	{
		if (UndoCount < MaxUndoRedoCount) //if there is less than 5 actions in undoarr
		{
			Undoarr[UndoCount++] = action; //add the last action to the array
		}
		else //else if the UndoCount is max, delete the first action in the array
		{
			for (int i = 0; i < MaxUndoRedoCount - 1; i++)
			{
				Undoarr[i] = Undoarr[i + 1];
			}
			UndoCount = 4;
			Undoarr[UndoCount++] = action;
		}
		RedoStatus = false;
	}
}

void ApplicationManager::AddtoRedo(Action* action)
{
	if (action) //if there is  action to redo 
	{
		if (RedoCount >= MaxUndoRedoCount) //if there is less than 5 actions in redoarr
		{
			for (int i = 0; i < MaxUndoRedoCount - 1; i++)
			{
				Redoarr[i] = Redoarr[i + 1];
			}
			RedoCount = 4;
		}
		Redoarr[RedoCount++] = action; //add the last action to the array
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
	RedoStatus = true;
}

void ApplicationManager::RemovefromRedo()
{
	if (RedoCount > 0)
	{
		RedoCount--;
	}
	else
		RedoCount = 0;
	RedoStatus = true;
}

Action* ApplicationManager::GetLastActiontoRedo()
{
	if (RedoCount > 0 && RedoStatus)
	{
		return Redoarr[RedoCount - 1];
	}
	return NULL;
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

void ApplicationManager::UnhideFigures()
{
	for (int i = 0; i < FigCount; i++)
		FigList[i]->HideFigure(false);
}


//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{
	for (int i = 0; (i < FigCount); i++)
		if (FigList[i]->FigisHidden() != true) // to make sure not to draw a hidden figure
			FigList[i]->Draw(pOut);	//Call Draw function (virtual member fn)
}

// Recording Functions
void ApplicationManager::SetIsRecording(bool IsRecording)
{
	this->IsRecording = IsRecording;
}
bool ApplicationManager::GetIsRecording() const
{
	return IsRecording;
}

void ApplicationManager::AddRecordedAction(Action* pRecordedAction)
{
	RecordingList[RecordsCount++] = pRecordedAction;
}

int ApplicationManager::GetRecordsCount() const
{
	return RecordsCount;
}

void ApplicationManager::PlayRecording(int RecordingNumber)
{
	RecordingList[RecordingNumber]->Execute();
	//updating drawing area after playing each action 
	pOut->ClearDrawArea();
	UpdateInterface();	
}

void ApplicationManager::SetPlayingRecord(bool IsPlaying)
{
	PlayingRecord = IsPlaying;
}

void ApplicationManager::ClearRecordingList()
{
	for (int j = 0; j < RecordsCount; j++)
	{
		RecordingList[j] = NULL;
		delete RecordingList[j];
	}

	RecordsCount = 0;
}

int ApplicationManager::GetMaxRecordingCount()
{
	return MaxRecordingCount;
}

bool ApplicationManager::GetPlayingRecord() const
{
	return PlayingRecord;
}

void ApplicationManager::ClearUndoList()
{
	for (int i = 0; i < MaxUndoRedoCount; i++)
	{
		Undoarr[i] = NULL;
	}
	UndoCount = 0;
}

void ApplicationManager::ClearRedoList()
{
	for (int i = 0; i < MaxUndoRedoCount; i++)
	{
		Redoarr[i] = NULL;
	}
	RedoCount = 0;
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

