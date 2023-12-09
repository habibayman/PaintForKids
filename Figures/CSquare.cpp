#include "CSquare.h"

CSquare::CSquare(Point P1, GfxInfo FigureGfxInfo) : CFigure(FigureGfxInfo)
{
	Center = P1;
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
