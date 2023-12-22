#include "CHexagon.h"

CHexagon::CHexagon(Point P1, GfxInfo FigureGfxInfo) : CFigure(FigureGfxInfo)
{
	Center = P1;
	FigureNumber = 4;
}

void CHexagon::Draw(Output* pOut) const
{
	pOut->DrawHexagon(Center, FigGfxInfo, Selected);

}

bool CHexagon::Isbelonging(Point P) const
{
	/*
	1- distance from center to any point on the border = dist1 = (sqrt(3) * r) / (sqrt(3) * cos(t) + sin(t))
	2- distance from center to any point = dist2 =  double dist2 = sqrt(pow(Center.x - P.x, 2) + pow(Center.y - P.y, 2))
	3- dist1 and dist2 has the same slope, so if dist2 <= dist1, the point belongs to the hexagon
	r = length && t = atan(slope of the line from center to any point on the border)
	*/
	double slope = (P.y - Center.y) / (double)(P.x - Center.x);
	double dist1 = (sqrt(3) * UI.HEXAGON_LENGTH) / ((sqrt(3) * cos(atan(slope))) + sin(atan(slope)));
	double dist2 = sqrt(pow(Center.x - P.x, 2) + pow(Center.y - P.y, 2));

	if (dist2 <= dist1)
	{
		if (dist2 >= dist1 - FigGfxInfo.BorderWidth - 0.01)  //check that the point is on the borders
		{
			return true;
		}
		//TODO: if figure is filled return true
		return false;
	}
	return false;
}

void CHexagon::Move(Point P)
{
	Center = P;
}

bool CHexagon::IsValid()
{
	return !(Center.y < UI.wy + UI.ToolBarHeight + sqrt(3) / 2 * UI.HEXAGON_LENGTH ||
		UI.height - Center.y < UI.HEXAGON_LENGTH + UI.StatusBarHeight + UI.wy ||
		Center.x < UI.wx + UI.HEXAGON_LENGTH ||
		UI.width - Center.x < UI.HEXAGON_LENGTH + 3 * UI.wx);
}


//==================================================================================//
//							PlayMode Management Functions							//
//==================================================================================//
void CHexagon::StartGame(Output* pOut)
{
	pOut->PrintMessage("Please Pick all Hexagons");

}

int CHexagon::GetFigureNumber()
{
	return FigureNumber;
}

color CHexagon::GetFigureColor()
{
	return FigGfxInfo.FillClr;
}

void CHexagon::HideFigure(bool b)
{
	isHidden = b;

}

bool CHexagon::FigisHidden()
{
	return isHidden;
}
