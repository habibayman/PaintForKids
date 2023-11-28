#ifndef INPUT_H 
#define INPUT_H

#include "..\DEFS.h"
#include "UI_Info.h" 
#include "..\CMUgraphicsLib\CMUgraphics.h"

class Output;   // forward declaration

class Input		//The application manager should have a pointer to this class
{
private:
	window *pWind;	//Pointer to the Graphics Window
public:
	Input(window *pW);		//Consturctor
	void GetPointClicked(int &x, int &y) const ;//Get coordinate where user clicks
	string GetSrting(Output* pO) const ;	 //Returns a string entered by the user

	ActionType GetUserAction() const; //Read the user click and map to an action
	ColorType GetColor() const; //Get the color the user clicks on

	//Shapes drawing area validation functions
	void Point_Validation(Point& P, Output* pOut); //Used for the triangle and rectangle
	void Hexagon_Validation(Point& P, Output* pO); //used for the hexagon
	void Circle_Validation(Point& P1, Point& P2, GfxInfo gfxInfo, Output* pO); // used for the circle
	void Square_Validation(Point& p1, Output* pO); //Used for the square
	void Repeatability_Validation(Point& p1, Point& p2, Output* pO); //Used for the triangle and rectangle
	~Input();
};

#endif