#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "DEFS.h"
#include "Figures\CFigure.h"
#include "GUI\input.h"
#include "GUI\output.h"
#include"Figures/CRectangle.h"
#include"Figures/CCircle.h"
#include"Figures/CHexagon.h"
#include"Figures/CSquare.h"
#include"Figures/CTriangle.h"
#include"Actions/PickByShapeAction.h"
#include"Actions/PickByColorAction.h"
#include"Actions/PickByBothAction.h"
//Main class that manages everything in the application.
class Action;

class ApplicationManager
{
	enum { MaxFigCount = 200 };	//Max no of figures

private:
	int FigCount;		//Actual number of figures
	int UndoCount;

	CFigure* FigList[MaxFigCount];	//List of all figures (Array of pointers)
	CFigure* LastSelectedFig; //Pointer to the selected figure

	Action* Undoarr[5];
	Action* LastAction;

	//Pointers to Input and Output classes
	Input* pIn;
	Output* pOut;

public:
	ApplicationManager();
	~ApplicationManager();

	// -- Action-Related Functions
	//Reads the input command from the user and returns the corresponding action type
	ActionType GetUserAction() const;
	void ExecuteAction(ActionType); //Creates an action and executes it

	// -- Figures Management Functions
	void AddFigure(CFigure* pFig);          //Adds a new figure to the FigList
	void DeleteLastFigure();                //deletes last figure from figlist 
	CFigure* GetFigure(Point P) const;      //Search for a figure given a point inside the figure
	void SetLastSelected(CFigure* pFig);    //set the last selected figure
	CFigure* GetLastSelected();             //get the last selected figure
	void SaveAll(ofstream& OutFile);        //calls Save(..) for each figure in the FigList
	int Get_FigCount() const;               //Returns the number of figures
	void ClearAll();                        //deletes all the drawn figures from the array
	void Delete(CFigure* pFig);             //Deletes the selected -if any- firure
	void AddtoUndo(Action* action);
	void RemovefromUndo();
	Action* GetLastActiontoUndo();

	// -- PlayMode Management Functions
	CFigure* RandomFigure(int& TotalFig);	//choose a random figure to start the same
	CFigure* RandomColor(int& TotalFig);	//choose a random color to start the same
	CFigure* RandomColoredFigure(int& TotalFig);	//choose a random  colored figure to start the same
	void ResetPlayMode();	//Reset the game

	// -- Interface Management Functions
	Input* GetInput() const; //Return pointer to the input
	Output* GetOutput() const; //Return pointer to the output
	void UpdateInterface() const;	//Redraws all the drawing window

};

#endif