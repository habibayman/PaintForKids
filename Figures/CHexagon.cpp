#include "CHexagon.h"

CHexagon::CHexagon(Point P1, GfxInfo FigureGfxInfo) : CFigure(FigureGfxInfo)
{
	Center = P1;

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
