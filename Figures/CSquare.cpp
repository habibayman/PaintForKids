#include "CSquare.h"
#include <fstream>

CSquare::CSquare(Point P1, GfxInfo FigureGfxInfo) : CFigure(FigureGfxInfo)
{
	Center = P1;
	ID++;
	FigureNumber = 2;
}

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
		if (P.x <= Center.x - UI.SQUARE_LENGTH / 2 + FigGfxInfo.BorderWidth ||
			P.x >= Center.x + UI.SQUARE_LENGTH / 2 - FigGfxInfo.BorderWidth ||
			P.y <= Center.y - UI.SQUARE_LENGTH / 2 + FigGfxInfo.BorderWidth ||
			P.y >= Center.y + UI.SQUARE_LENGTH / 2 - FigGfxInfo.BorderWidth)
		{
			return true;
		}
		//TODO: if figure is filled return true
		return false;
	}
	return false;
}

void CSquare::Move(Point P)
{
	Center = P;
}

bool CSquare::IsValidMove()
{
	return !(Center.y < (UI.wy + UI.ToolBarHeight + UI.SQUARE_LENGTH / 2) ||
		Center.y > UI.height - UI.StatusBarHeight - UI.wy ||
		Center.y > UI.height - (UI.wy + UI.StatusBarHeight + UI.SQUARE_LENGTH / 2) ||
		Center.x < (UI.wx + UI.SQUARE_LENGTH / 2) ||
		Center.x > UI.width - UI.SQUARE_LENGTH / 2 - (3 * UI.wx));
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
void CSquare::HideFigure(bool b) //Hide\Unhide the figure
{
	isHidden = b;
}

bool CSquare::FigisHidden()	//Know if figure is hidden or not
{
	return isHidden;
}
