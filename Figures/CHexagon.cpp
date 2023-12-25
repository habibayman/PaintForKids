#include "CHexagon.h"
#include <fstream>
#include <string>
using namespace std;

CHexagon::CHexagon(Point P1, GfxInfo FigureGfxInfo) : CFigure(FigureGfxInfo)
{
	Center = P1;
	ID++;
	FigureNumber = 4;
	for (int i = 0; i < 5; i++)
	{
		TempCenter[i].x = 0;
		TempCenter[i].y = 0;
	}
}

CHexagon::CHexagon()
{
}

void CHexagon::Draw(Output* pOut) const
{
	pOut->DrawHexagon(Center, FigGfxInfo, Selected);

}

bool CHexagon::Isbelonging(Point P) const
{
	/*
	1- distance from center to any point on the border = dist1 = (sqrt(3) * r) / (sqrt(3) * cos(t) + sin(t))
	2- distance from center to any point = dist2 = sqrt(pow(Center.x - P.x, 2) + pow(Center.y - P.y, 2))
	3- dist1 and dist2 have the same slope, so if dist2 <= dist1, the point belongs to the hexagon
	r = length && t = atan(slope of the line from center to any point on the border)
    */

	double slope = (P.y - Center.y) / (double)(P.x - Center.x);
	double angle = fabs(atan(slope));
	double dist1 = (sqrt(3) * UI.HEXAGON_LENGTH) / (sqrt(3) * cos(angle) + sin(angle));
	double dist2 = sqrt(pow(Center.x - P.x, 2) + pow(Center.y - P.y, 2));

	if (dist2 <= dist1)
	{
		return true;
	}
		return false;
	return true;
	
}

void CHexagon::Move(Point P)
{
    TempCenter[MoveCount++] = Center;
	Center = P;
}

void CHexagon::UndoMove()
{
	Center = TempCenter[MoveCount - 1];
	MoveCount--;
}

bool CHexagon::IsValid()
{
	return !(Center.y < UI.wy + UI.ToolBarHeight + sqrt(3) / 2 * UI.HEXAGON_LENGTH ||
		UI.height - Center.y < UI.HEXAGON_LENGTH + UI.StatusBarHeight + UI.wy ||
		Center.x < UI.wx + UI.HEXAGON_LENGTH ||
		UI.width - Center.x < UI.HEXAGON_LENGTH + 3 * UI.wx);
}

void CHexagon::Save(ofstream& OutFile)
{
	OutFile << "Hexagon" << "\t" << ID << "\t"; //type and ID 
	OutFile << Center.x << "\t" << Center.y << "\t"; //Coordinates
	OutFile < FigGfxInfo.DrawClr;
	OutFile << "\t";
	if (FigGfxInfo.isFilled)
	{
		OutFile < FigGfxInfo.FillClr;
	}
	else
	{
		OutFile << "NO_FILL" << "\n";
	}
	//Drawing color and fill color 
}

void CHexagon::PrintInfo(Output* pOut)
{
	string info = "ID: " + to_string(ID) + ", Center (" + to_string(Center.x) + ", " + to_string(Center.y) + "), " +
		"Length: " + to_string((int)UI.HEXAGON_LENGTH);
	pOut->PrintMessage(info);
}


//==================================================================================//
//							PlayMode Management Functions							//
//==================================================================================//
void CHexagon::StartGame(Output* pOut, int P)	 //Print a proper message to start the game
{
	if (P == TO_PICK_BY_SHAPE)
		pOut->PrintMessage("Please Pick all HEXAGONS");
	else if (P == TO_PICK_BY_COLOR)
		pOut->PrintMessage("Please Pick all Figures with color: " + this->ChosenColorName());
	else if (P == TO_PICK_BY_BOTH)
		pOut->PrintMessage("Please Pick all HEXAGONS with color: " + this->ChosenColorName());

}
int CHexagon::GetFigureNumber()	//Get figure number
{
	return FigureNumber;
}
color CHexagon::GetFigureColor()	//Get figure color
{
	return FigGfxInfo.FillClr;
}
color CHexagon::GetDrawColor()
{
	return FigGfxInfo.DrawClr;
}
void CHexagon::HideFigure(bool b) //Hide\Unhide the figure
{
	isHidden = b;
}

bool CHexagon::FigisHidden()	//Know if figure is hidden or not
{
	return isHidden;
}
void CHexagon::Load(ifstream& InFile)
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

