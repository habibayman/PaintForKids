#include "CFigure.h"

CFigure::CFigure(GfxInfo FigureGfxInfo)
{
	FigGfxInfo = FigureGfxInfo;	//Default status is non-filled.
	Selected = false;
	FigGfxInfo.BorderWidth = UI.PenWidth;
	LastDrawColor = BLUE;
	LastFillColor = WHITE;
	ID = 0;
	MoveCount = 0;
}

void CFigure::SetSelected(bool s)
{
	Selected = s;
}

bool CFigure::IsSelected() const
{
	return Selected;
}

void CFigure::ChngDrawClr(color Dclr)
{
	LastDrawColor = FigGfxInfo.DrawClr;
	FigGfxInfo.DrawClr = Dclr;
}

void CFigure::ChngFillClr(color Fclr)
{
	FigGfxInfo.isFilled = true;
	LastFillColor = FigGfxInfo.FillClr;
	FigGfxInfo.FillClr = Fclr;
}

//==================================================================================//
//							PlayMode Management Functions							//
//==================================================================================//
string CFigure::ChosenColorName()
{
	if(this->GetFigureColor()==BLACK)
		return "BLACK";
	if (this->GetFigureColor() == YELLOW)
		return "YELLOW";
	if (this->GetFigureColor() == ORANGE)
		return "ORANGE";
	if (this->GetFigureColor() == RED)
		return "RED";
	if (this->GetFigureColor() == GREEN)
		return "GREEN";
	if (this->GetFigureColor() == BLUE)
		return "BLUE";
}
