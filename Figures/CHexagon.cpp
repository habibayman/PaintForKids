#include "CHexagon.h"
#include <fstream>
#include <string>
using namespace std;

CHexagon::CHexagon(Point P1, GfxInfo FigureGfxInfo) : CFigure(FigureGfxInfo)
{
	Center = P1;
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
	Point q2;
	q2.x = abs(P.x - Center.x);  //transform the point to quadrant 2
	q2.y = abs(P.y - Center.y);
	
	float horizontal = UI.HEXAGON_LENGTH * cos(atan(1) / 3.0);
	float vertical = UI.HEXAGON_LENGTH / 2;

	if (q2.x > horizontal || q2.y > vertical * 2)
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

void CHexagon::SetID(int id)
{
	ID = id;
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

