#include "CSquare.h"

CSquare::CSquare(Point P1, GfxInfo FigureGfxInfo) : CFigure(FigureGfxInfo)
{
	Center = P1;
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

bool CSquare::IsValid()
{
	return !(Center.y < (UI.wy + UI.ToolBarHeight + UI.SQUARE_LENGTH / 2) ||
		Center.y > UI.height - UI.StatusBarHeight - UI.wy ||
		Center.y > UI.height - (UI.wy + UI.StatusBarHeight + UI.SQUARE_LENGTH / 2) ||
		Center.x < (UI.wx + UI.SQUARE_LENGTH / 2) ||
		Center.x > UI.width - UI.SQUARE_LENGTH / 2 - (3 * UI.wx));
}


//==================================================================================//
//							PlayMode Management Functions							//
//==================================================================================//
void CSquare::StartGame(Output* pOut)
{
	pOut->PrintMessage("Please Pick all Squares");

}

int CSquare::GetFigureNumber()
{
	return FigureNumber;
}

void CSquare::HideFigure(bool b)
{
	isHidden = b;

}

bool CSquare::FigisHidden()
{
	return isHidden;
}
