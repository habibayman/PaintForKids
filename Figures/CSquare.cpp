#include "CSquare.h"
#include <fstream>

CSquare::CSquare(Point P1, GfxInfo FigureGfxInfo) : CFigure(FigureGfxInfo)
{
	Center = P1;
	FigureNumber = 2;
	MoveCount = 0;
	for (int i = 0; i < 5; i++)
	{
		TempCenter[i].x = 0;
		TempCenter[i].y = 0;
	}
}

CSquare::CSquare()
{}

void CSquare::Draw(Output* pOut) const
{
	pOut->DrawSquare(Center, FigGfxInfo, Selected);
}


bool CSquare::Isbelonging(Point P) const
{
	if (P.x >= Center.x - UI.SQUARE_LENGTH / 2 &&
		P.x <= Center.x + UI.SQUARE_LENGTH / 2 &&
		P.y >= Center.y - UI.SQUARE_LENGTH / 2 &&
		P.y <= Center.y + UI.SQUARE_LENGTH / 2)
	{
		return true;
	}
	return false;
}

void CSquare::Move(Point P)
{
	TempCenter[MoveCount++] = Center;
	Center = P;
}

void CSquare::UndoMove()
{
	Center = TempCenter[MoveCount - 1];
	MoveCount--;
}


bool CSquare::IsValidMove()
{
	return !(Center.y < (UI.wy + UI.ToolBarHeight + UI.SQUARE_LENGTH / 2) ||
		Center.y > UI.height - UI.StatusBarHeight - UI.wy ||
		Center.y > UI.height - (UI.wy + UI.StatusBarHeight + UI.SQUARE_LENGTH / 2) ||
		Center.x < (UI.wx + UI.SQUARE_LENGTH / 2) ||
		Center.x > UI.width - UI.SQUARE_LENGTH / 2 - (3 * UI.wx));
}

void CSquare::SetID(int id)
{
	ID = id;
}

void CSquare::Save(ofstream& OutFile)
{
	OutFile << "Square" << "\t" << ID << "\t"; //type and ID 
	OutFile << Center.x << "\t"  << Center.y << "\t"; //Coordinates
	OutFile < FigGfxInfo.DrawClr;
	OutFile << "\t";
	if (FigGfxInfo.isFilled)
	{
		OutFile < FigGfxInfo.FillClr ;
	}
	else
	{
		OutFile << "NO_FILL" << "\n";
	}
	//Drawing color and fill color 
}

void CSquare::PrintInfo(Output* pOut)
{
	string info = "ID: " + to_string(ID) + ", Center (" + to_string(Center.x) + ", " + to_string(Center.y) + "), " +
		"Length: " + to_string((int)UI.SQUARE_LENGTH);
	pOut->PrintMessage(info);
}



//==================================================================================//
//							PlayMode Management Functions							//
//==================================================================================//
void CSquare::StartGame(Output* pOut, int P)	 //Print a proper message to start the game
{
	if (P == TO_PICK_BY_SHAPE)
		pOut->PrintMessage("Please Pick all SQUARES");
	else if (P == TO_PICK_BY_COLOR)
		pOut->PrintMessage("Please Pick all Figures with color: " + this->ChosenColorName());
	else if (P == TO_PICK_BY_BOTH)
		pOut->PrintMessage("Please Pick all SQUARES with color: " + this->ChosenColorName());
}
int CSquare::GetFigureNumber()	//Get figure number
{
	return FigureNumber;
}
color CSquare::GetFigureColor()	//Get figure color
{
	return FigGfxInfo.FillClr;
}
color CSquare::GetDrawColor()
{
	return FigGfxInfo.DrawClr;
}
void CSquare::HideFigure(bool b) //Hide\Unhide the figure
{
	isHidden = b;
}

bool CSquare::FigisHidden()	//Know if figure is hidden or not
{
	return isHidden;
}
bool CSquare::FigIsFilled()
{
	if (FigGfxInfo.isFilled)
		return true;
	else
		return false;
}
void CSquare::Load(ifstream& InFile) 
{
	InFile >> ID; //Read the ID
	InFile >> Center.x >> Center.y; //Read the center point
	//set FigGfxInfo data
	InFile >> ReadDrawColor;
	FigGfxInfo.DrawClr = StringToColor(ReadDrawColor);
	InFile >> ReadFillColor;
	if (ReadFillColor.compare("NO_FILL"))
	{
		FigGfxInfo.isFilled = 1;
		FigGfxInfo.FillClr = StringToColor(ReadFillColor);
	}
	else
	{
		FigGfxInfo.isFilled = 0;
	}
	FigGfxInfo.BorderWidth = UI.PenWidth;
	Selected = false;
}

