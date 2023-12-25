#include "CFigure.h"

CFigure::CFigure(GfxInfo FigureGfxInfo)
{
	FigGfxInfo = FigureGfxInfo;	//Default status is non-filled.
	Selected = false;
	FigGfxInfo.BorderWidth = UI.PenWidth;
	LastDrawColor = BLUE;
	ID = 0;
	MoveCount  = 0;
}

void CFigure::SetSelected(bool s)
{
	Selected = s;
}

CFigure::CFigure()
{}

bool CFigure::IsSelected() const
{
	return Selected;
}

/*void CFigure::SetFilled(bool f)
{
	FigGfxInfo.isFilled = f;
}
*/
void CFigure::ChngDrawClr(color Dclr)
{
	LastDrawColor = FigGfxInfo.DrawClr;
	FigGfxInfo.DrawClr = Dclr;
}

void CFigure::ChngFillClr(color Fclr)
{
	FigGfxInfo.isFilled = true;

	FigGfxInfo.FillClr = Fclr;
	
}

void CFigure::SetFilled(bool f)
{
	FigGfxInfo.isFilled = f;
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
