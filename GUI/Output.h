#ifndef OUPTUT_H
#define OUPTUT_H
#include "Input.h"
#include <string>

class Output	//The application manager should have a pointer to this class
{
private:	
	window* pWind;	//Pointer to the Graphics Window

public:
	Output();		

	window* CreateWind(int, int, int , int) const; //creates the application window
	void CreateDrawToolBar() const;	//creates Draw mode toolbar & menu
	void CreateColorPalette() const; //creates Draw mode's color palette
	void CreatePlayToolBar() const;	//creates Play mode toolbar & menu
	void CreateStatusBar() const;	//create the status bar
	Input* CreateInput() const; //creates a pointer to the Input object	
	void ClearStatusBar() const; //Clears the status bar
	void ClearColorPalette() const; //Clears the color palette
	void ClearDrawArea() const;	//Clears the drawing area
	void ClearToolbar() const; //clears the draw mode's tool bar
	void PrintMessage(string msg) const;	//Print a message on Status bar
	color getCrntDrawColor() const;	//get current drawing color
	color getCrntFillColor() const;	//get current filling color
	int getCrntPenWidth() const; //get current pen width
	
	// -- Figures Drawing functions
	void DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected=false) const; //Draw a rectangle
	///Make similar functions for drawing all other figure types.                      //DONE!
	
	void DrawSquare(Point p, GfxInfo SqrGfxInfo, bool selected) const; //Draw a square
	void DrawTri(Point p1, Point p2, Point p3, GfxInfo TriGfxInfo, bool selected = false) const; //Draw a triangle
	void DrawHexagon(Point P, GfxInfo HexaGfxInfo, bool selected) const; //Draw a hexagon 
    void DrawCircle(Point P1, Point P2,  GfxInfo Circle, bool selected) const; //Draw a circle 

	buttonstate GetMouseState(const button btMouse, int& iX, int& iY); //get mouse state
	~Output();
};

#endif
