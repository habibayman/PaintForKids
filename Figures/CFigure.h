#ifndef CFIGURE_H
#define CFIGURE_H

#include "..\defs.h"
#include "..\GUI\Output.h"
#include <fstream>
using namespace std;

//Base class for all figures
class CFigure
{
protected:
    int ID;		//Each figure has an ID
	bool Selected;	//true if the figure is selected.
	GfxInfo FigGfxInfo;	//Figure graphis info
	//to be used in loading yet might be deleted 
	
	int MoveCount; //count no of moves
	
	/// Add more parameters if needed.
	//---PlayMode parameters
	bool isHidden = false;
	int FigureNumber;
	
	color LastDrawColor;
	color LastFillColor;

public:
	CFigure(GfxInfo FigureGfxInfo);
	virtual void SetID(int)=0;	//set fig ID
	CFigure(); 

	void SetSelected(bool s);	//select/unselect the figure
	bool IsSelected() const;	//check whether fig is selected

	virtual bool Isbelonging(Point P) const = 0;        //Checks if the point belongs to the figure
	virtual void Draw(Output* pOut) const = 0;		//Draw the figure

	void ChngDrawClr(color Dclr);	//changes the figure's drawing color
	void ChngFillClr(color Fclr);	//changes the figure's filling color


	virtual void Move(Point P) = 0; //Move the figure to new position
	virtual void UndoMove() = 0;        //Undo the figure to the old position

	//validation function for figure points
	virtual bool IsValidMove() = 0;

	///The following functions should be supported by the figure class
	///It should be overridden by each inherited figure
	///Decide the parameters that you should pass to each function	


	virtual void Save(ofstream &OutFile) = 0;	//Save the figure parameters to the file
	//virtual void Load(ifstream &Infile) = 0;	//Load the figure parameters to the file
	virtual void PrintInfo(Output* pOut) = 0;	//print all figure info on the status bar
	virtual void Load(ifstream &Infile) = 0;	//Load the figure parameters to the file
	//virtual void PrintInfo(Output* pOut) = 0;	//print all figure info on the status bar

	
//==================================================================================//
//							PlayMode Management Functions							//
//==================================================================================//
	virtual void StartGame(Output*,int) = 0;
	virtual int GetFigureNumber() = 0;
	virtual void HideFigure(bool) = 0;
	virtual bool FigisHidden()=0;
	virtual color GetFigureColor() = 0;
	virtual color GetDrawColor() = 0;
	string ChosenColorName();
	virtual bool FigIsFilled() = 0;

};

#endif