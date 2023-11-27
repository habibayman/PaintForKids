#include "GUI\Input.h"
#include "GUI\Output.h"

//This is a test code to test the Input and Output classes

int main()
{
	int x,y;

	//Create Input and Output objects to test
	Output *pOut = new Output();
	Input *pIn = pOut->CreateInput();

	//Starting the test
	pOut->PrintMessage("This demo is to test input and output classes, Click anywhere to start the test");
	pIn->GetPointClicked(x,y);	//Wait for any click


	///////////////////////////////////////////////////////////////////////////////////
	// TEST 1:	
	//			Create The FULL Tool bar, the drawing area and the status bar	
	//			This has already been done through the constrcutor of class Output
	///////////////////////////////////////////////////////////////////////////////////

	pOut->PrintMessage("TEST1: Drawing Tool bar and Status bar, Click anywhere to continue");
	pIn->GetPointClicked(x,y);	//Wait for any click

	
	///////////////////////////////////////////////////////////////////////////////////
	// TEST 2:	
	//			Drawing all the Figures with all possible states: 
	//			Non-filled, Filled, and highlighted in both cases			
	///////////////////////////////////////////////////////////////////////////////////
	
	pOut->PrintMessage("TEST2: Now we will show that Output class can draw any figure in any state, Click anywhere to continue");
	pIn->GetPointClicked(x,y);	//Wait for any click

	GfxInfo gfxInfo;//to be used with draw function of the class Ouput
	Point P1, P2, P3;

	/// 2.1- Rectangle Test ///
	/// =================== 
	pOut->PrintMessage("Drawing a Rectangle, filled/non-filled and Highlighted filled/non-filled,  Click to continue");
	pIn->GetPointClicked(x,y);	//Wait for any click
	
	// 2.1.1 - Drawing non-filled rectangle
	pOut->PrintMessage("Drawing a Rectangle ==> non-filled,  Click two points");
	pIn->GetPointClicked(P1.x, P1.y);
	pIn->GetPointClicked(P2.x, P2.y);
	pIn->Rect_Validation(P1, P2, pOut, pIn);

	gfxInfo.BorderWdth = 5;
	gfxInfo.DrawClr = BLACK;	//any color for border
	gfxInfo.isFilled = false;	//Figure is NOT filled
	pOut->DrawRect(P1, P2, gfxInfo, false);

	// 2.1.2 - Drawing highlighted non-filled rectangle
	pOut->PrintMessage("Drawing a Rectangle ==> Highlighted non-filled, Click to Highlight");
	pIn->GetPointClicked(x,y);	//Wait for any click
	pOut->DrawRect(P1, P2, gfxInfo, true);


	// 2.1.3 - Drawing a filled rectangle
	pOut->PrintMessage("Drawing a Rectangle ==> filled,  Click two points");
	pIn->GetPointClicked(P1.x, P1.y);
	pIn->GetPointClicked(P2.x, P2.y);
	pIn->Rect_Validation(P1, P2, pOut, pIn);

	gfxInfo.BorderWdth = 6;
	gfxInfo.DrawClr = BLUE;	//any color for border
	gfxInfo.FillClr = GREEN;//any color for filling
	gfxInfo.isFilled = true;//Figure is filled
	pOut->DrawRect(P1, P2, gfxInfo, false);


	// 2.1.4 - Drawing a highlighted filled rectangle
	pOut->PrintMessage("Drawing a Rectangle ==> Highlighted filled, Click to Highlight");
	pIn->GetPointClicked(x,y);	//Wait for any click
	pOut->DrawRect(P1, P2, gfxInfo, true);



	pOut->PrintMessage("Drawing a Rectangle Test ==> OK,  Click anywhere to continue");
	pIn->GetPointClicked(x,y);	//Wait for any click
	pOut->ClearDrawArea();

	/// 2.2- Square Test ///
	/// ============== 
	pOut->PrintMessage("Drawing a Square, normal and Highlighted, Click to continue");
	pIn->GetPointClicked(x, y);	//Wait for any click

	// 2.1.1 - Drawing non-filled square
	pOut->PrintMessage("Drawing a Square ==> non-filled,  Click one point");
	pIn->GetPointClicked(P1.x, P1.y);
	pIn->Square_Validation(P1, pOut, pIn);

	gfxInfo.BorderWdth = 5;
	gfxInfo.DrawClr = BLACK;	//any color for border
	gfxInfo.isFilled = false;	//Figure is NOT filled
	pOut->DrawSquare(P1, gfxInfo, false);

	// 2.1.2 - Drawing highlighted non-filled square
	pOut->PrintMessage("Drawing a Square ==> Highlighted non-filled, Click to Highlight");
	pIn->GetPointClicked(x, y);	//Wait for any click
	pOut->DrawSquare(P1, gfxInfo, true);


	// 2.1.3 - Drawing a filled square
	pOut->PrintMessage("Drawing a Square ==> filled,  Click one Point");
	pIn->GetPointClicked(P1.x, P1.y);
	pIn->Square_Validation(P1, pOut, pIn);

	gfxInfo.BorderWdth = 6;
	gfxInfo.DrawClr = BLUE;	//any color for border
	gfxInfo.FillClr = GREEN;//any color for filling
	gfxInfo.isFilled = true;//Figure is filled
	pOut->DrawSquare(P1, gfxInfo, false);


	// 2.1.4 - Drawing a highlighted filled square
	pOut->PrintMessage("Drawing a Square ==> Highlighted filled, Click to Highlight");
	pIn->GetPointClicked(x, y);	//Wait for any click
	pOut->DrawSquare(P1, gfxInfo, true);


	pOut->PrintMessage("Drawing a Square Test ==> OK,  Click anywhere to continue");
	pIn->GetPointClicked(x, y);	//Wait for any click
	pOut->ClearDrawArea();

	/// 2.3- Triangle Test ///
	/// =================== 
	pOut->PrintMessage("Drawing a Triangle, filled/non-filled and Highlighted filled/non-filled,  Click to continue");
	pIn->GetPointClicked(x,y);	//Wait for any click
	///TODO: Add code to draw Triangle in all possible states
	//begin here


	// 2.3.1 - Drawing non-filled triangle
	pOut->PrintMessage("Drawing a triangle ==> non-filled,  Click three points");
	pIn->GetPointClicked(P1.x, P1.y);
	pIn->Triangle_Input_Valid(P1, pOut, pIn); 
	pIn->GetPointClicked(P2.x, P2.y);
	pIn->Triangle_Input_Valid(P2, pOut, pIn);
	pIn->GetPointClicked(P3.x, P3.y);
    pIn->Triangle_Input_Valid(P3, pOut, pIn);

	//A check on every point to not draw on the bars
	//P1 = pIn->Triangle_Input_Valid(P1, pOut);
	//P2 = pIn->Triangle_Input_Valid(P2, pOut);
	//P3 = pIn->Triangle_Input_Valid(P3, pOut); 

	gfxInfo.BorderWdth = 5;
	gfxInfo.DrawClr = BLACK;	//any color for border
	gfxInfo.isFilled = false;	//Figure is NOT filled
	pOut->DrawTri(P1, P2, P3, gfxInfo, false);

	// 2.3.2 - Drawing highlighted non-filled triangle
	pOut->PrintMessage("Drawing a Triangle ==> Highlighted non-filled, Click to Highlight");
	pIn->GetPointClicked(x, y);	//Wait for any click
	pOut->DrawTri(P1, P2, P3, gfxInfo, true);

	// 2.3.3 - Drawing a filled triangle
	pOut->PrintMessage("Drawing a triangle ==> filled,  Click three points");
	pIn->GetPointClicked(P1.x, P1.y);
	pIn->Triangle_Input_Valid(P1, pOut, pIn);
	pIn->GetPointClicked(P2.x, P2.y);
	pIn->Triangle_Input_Valid(P2, pOut, pIn); 
	pIn->GetPointClicked(P3.x, P3.y);
	pIn->Triangle_Input_Valid(P3, pOut, pIn); 

	gfxInfo.BorderWdth = 6;
	gfxInfo.DrawClr = LIGHTGOLDENRODYELLOW;	//any color for border
	gfxInfo.FillClr = RED;//any color for filling
	gfxInfo.isFilled = true;//Figure is filled
	pOut->DrawTri(P1, P2, P3, gfxInfo, false);

	// 2.3.4 - Drawing a highlighted filled rectangle
	pOut->PrintMessage("Drawing a triangle ==> Highlighted filled, Click to Highlight");
	pIn->GetPointClicked(x, y);	//Wait for any click
	pOut->DrawTri(P1, P2, P3, gfxInfo, true);

	//end here
	pOut->PrintMessage("Drawing a Triangle Test ==> OK,  Click anywhere to continue");
	pIn->GetPointClicked(x,y);	//Wait for any click
	pOut->ClearDrawArea();
	
	/// 2.4- Hexagon Test ///
	/// =================== 

	Point P4;

	pOut->PrintMessage("Drawing a Hexagon, filled/non-filled and Highlighted filled/non-filled,  Click to continue");
	pIn->GetPointClicked(x, y);	//Wait for any click


	// 2.4.1 - Drawing non-filled hexagon
	pOut->PrintMessage("Drawing a Hexagon ==> non-filled,  Click on a point");
	pIn->GetPointClicked(P4.x, P4.y);	//Wait for any click
	pIn->CheckHexagonPoint(P4, pOut);
	
	gfxInfo.BorderWdth = 5;
	gfxInfo.DrawClr = BLACK;	//any color for border
	gfxInfo.isFilled = false;	//Figure is NOT filled
	pOut->DrawHexagon(P4, gfxInfo, false);


	// 2.4.2 - Drawing highlighted and non-filled hexagon 
	pOut->PrintMessage("Drawing a Hexagon ==> Highlighted non-filled, Click to Highlight");
	pIn->GetPointClicked(x, y);	//Wait for any click
	pOut->DrawHexagon(P4, gfxInfo, true);

	// 2.4.3 - Drawing a filled hexagon 
	pOut->PrintMessage("Drawing a Hexagon ==> filled,  Click on a point");
	pIn->GetPointClicked(P4.x, P4.y);
	pIn->CheckHexagonPoint(P4, pOut);

	gfxInfo.BorderWdth = 6;
	gfxInfo.DrawClr = BLUE;	//any color for border
	gfxInfo.FillClr = GREEN;//any color for filling
	gfxInfo.isFilled = true;//Figure is filled
	pOut->DrawHexagon(P4, gfxInfo, false);

	// 2.4.4 - Drawing a highlighted filled hexagon 
	pOut->PrintMessage("Drawing a hexagon ==> Highlighted filled, Click to Highlight");
	pIn->GetPointClicked(x, y);	//Wait for any click
	pOut->DrawHexagon(P4, gfxInfo, true);

	//end of hexagon test

	pOut->PrintMessage("Drawing a Hexagon Test ==> OK,  Click anywhere to continue");
	pIn->GetPointClicked(x, y);	//Wait for any click
	pOut->ClearDrawArea();

	
	/// 2.5- Circle Test ///
	/// =================== 
	pOut->PrintMessage("Drawing an Circle, filled/non-filled and Highlighted filled/non-filled,  Click to continue");
	pIn->GetPointClicked(x,y);	//Wait for any click
	pOut->PrintMessage("Drawing a circle ==> filled,  Click two points");

	///TODO: Add code to draw Circle in all possible states
	pIn->GetPointClicked(P1.x, P1.y);	//Wait for any click

	pIn->GetPointClicked(P2.x, P2.y);	//Wait for any 
	pIn->pointValidity(P1, P2, gfxInfo, pOut, pIn);

	gfxInfo.BorderWdth = 5;
	gfxInfo.DrawClr = BLACK;	//any color for border
	gfxInfo.isFilled = false;	//Figure is NOT filled

	pOut->DrawCircle(P1, P2, gfxInfo, false);
	// 2.1.2 - Drawing highlighted non-filled circle
	pOut->PrintMessage("Drawing a Circle ==> Highlighted non-filled, Click to Highlight");
	pIn->GetPointClicked(x, y);	//Wait for any click
	pOut->DrawCircle(P1, P2, gfxInfo, true);


	// 2.1.3 - Drawing a filled circle
	pOut->PrintMessage("Drawing a Circle ==> filled,  Click two points");
	pIn->GetPointClicked(P1.x, P1.y);
	pIn->GetPointClicked(P2.x, P2.y);
	pIn->pointValidity(P1, P2, gfxInfo, pOut, pIn);


	gfxInfo.BorderWdth = 6;
	gfxInfo.DrawClr = BLUE;	//any color for border
	gfxInfo.FillClr = GREEN;//any color for filling
	gfxInfo.isFilled = true;//Figure is filled
	pOut->DrawCircle(P1, P2, gfxInfo, false);


	// 2.1.4 - Drawing a highlighted filled circle
	pOut->PrintMessage("Drawing a Circle ==> Highlighted filled, Click to Highlight");
	pIn->GetPointClicked(x, y);	//Wait for any click
	pOut->DrawCircle(P1, P2, gfxInfo, true);


	pOut->PrintMessage("Drawing a Circle Test ==> OK,  Click anywhere to continue");
	pIn->GetPointClicked(x,y);	//Wait for any click
	pOut->ClearDrawArea();
	
	///////////////////////////////////////////////////////////////////////////////////
	// TEST 3: 
	//			Input Class: Read strings from the user
	///////////////////////////////////////////////////////////////////////////////////
	pOut->PrintMessage("TEST3: Now Time to test class Input, Click anywhere to continue");
	pIn->GetPointClicked(x,y);	//Wait for any click
	
	pOut->PrintMessage("Testing Input ability to read strings");

	///TODO: Add code here to 
	// 1- Read a string from the user on the status bar
	// 2- After reading the string clear the status bar
	// 3- print on the status bar "You Entered" then print the string
	string s = pIn->GetSrting(pOut);
	pOut->ClearStatusBar();
	pOut->PrintMessage("You Entered the following :  " + s + " ....Click anywhere to continue ");
	pIn->GetPointClicked(x, y);	//Wait for any click

	pOut->ClearDrawArea();
	
	///////////////////////////////////////////////////////////////////////////////////
	// TEST 4: 
	//			Input Class : Check for the user action
	///////////////////////////////////////////////////////////////////////////////////
	pOut->PrintMessage("TEST4: Testing Input ability to detect User Action, click anywhere");

	ActionType ActType;
	ColorType ColorSelected;
	
	///TODO:  
	//You must add a case for each action (both Draw mode and Play mode actions)
	//Add cases for the missing actions below
	do
	{
		ActType = pIn->GetUserAction();
		pOut->ClearColorPalette();

		switch (ActType)
		{
		case TO_PLAY:
			pOut->PrintMessage("Action: Switch to Play Mode, creating Design tool bar");
			pOut->ClearToolbar();
			pOut->CreatePlayToolBar();
			break;

		case SELECT_FIGURE:
			pOut->PrintMessage("Action: Select a Figure , Click on the figure");
			break;

		case TO_UNDO:
			pOut->PrintMessage("Action: UNDO ");
			break;

		case TO_REDO:
			pOut->PrintMessage("Action: REDO ");
			break;

		case SAVE_FIGURE:
			pOut->PrintMessage("Action:Window is Saved");
			break;

		case DRAW_RECT:
			pOut->PrintMessage("Action: Draw a Rectangle , Click anywhere");
			break;
		
		case DRAW_SQUARE:
			pOut->PrintMessage("Action: Draw a square , Click anywhere");
			break;
		
		case DRAW_TRIANGLE:
			pOut->PrintMessage("Action: Draw a Triangle , Click anywhere");
			break;
		
		case DRAW_HEXA:
			pOut->PrintMessage("Action: Draw a Hexagon , Click anywhere");
			break;
		
		case DRAW_CIRCLE:
			pOut->PrintMessage("Action: Draw a Circle , Click anywhere");
			break;
		
		case MOVE_FIGURE :
			pOut->PrintMessage("Action: Move a Figure , Click anywhere");
			break;
		
		case PLAY_RECORDING :
			pOut->PrintMessage("Action: Start Playing the Recording , Click anywhere");
			break;
		
		case START_RECORDING:
			pOut->PrintMessage("Action: Start Recording , Click anywhere");
			break;

		case STOP_RECORDING:
		pOut->PrintMessage("Action: Stop Recording, Click anywhere");
		break;

		case TO_LOAD:
		pOut->PrintMessage("Action: load graph");
		break;




		case TO_COLOR:
			pOut->PrintMessage("Action: a click on color palette");
			pOut->CreateColorPalette();

			do {
			ColorSelected = pIn->GetColor();

			switch (ColorSelected)
			{
			case COLOR_GREEN:
				pOut->PrintMessage("Action: a click on green color");
				break;
			case COLOR_RED:
				pOut->PrintMessage("Action: a click on red color");
				break;
			case COLOR_ORANGE:
				pOut->PrintMessage("Action: a click on orange color");
				break;
			case COLOR_YELLOW:
				pOut->PrintMessage("Action: a click on yellow color");
				break;
			case COLOR_BLUE:
				pOut->PrintMessage("Action: a click on blue color");
				break;
			case COLOR_BLACK:
				pOut->PrintMessage("Action: a click on black color");
				break;
			}

			   } while (ColorSelected != NO_COLOR);

		 pOut->PrintMessage("Action: No color selected");
		 //clearing color icons
		 pOut->ClearColorPalette();
		 break;

		case TO_CLEAR:
			   pOut->PrintMessage("Action: CLear window");
			   break;

		case TO_DELETE:
			   pOut->PrintMessage("Action: delete figure");
			   break;
		
		case STATUS:
				pOut->PrintMessage("Action: a click on the Status Bar, Click anywhere");
				break;
 
		case DRAWING_AREA:
				pOut->PrintMessage("Action: a click on the Drawing Area, Click anywhere");
				break;

		case EMPTY:
				pOut->PrintMessage("Action: a click on empty area in the Design Tool Bar, Click anywhere");
				break;
		
		//Play mode cases
		case TO_DRAW:
			pOut->PrintMessage("Action: Switch to Draw Mode, creating Design tool bar"); 
			pOut->CreateDrawToolBar(); 
			break;

		case TO_PICK_BY_COLOR:
			pOut->PrintMessage("Action: you chose to pick by color, Click anywhere");
			break;
		
		case TO_PICK_BY_SHAPE:
			pOut->PrintMessage("Action: you chose to pick by shape, Click anywhere");
			break;

		case TO_PICK_BY_BOTH:
			pOut->PrintMessage("Action: you chose to pick by both, Click anywhere");
			break;


		///TODO: Add more cases for the other action types


		case EXIT:				
				break;
		}
	}while(ActType != EXIT);


	/// Exiting
	pOut->PrintMessage("Action: EXIT, test is finished, click anywhere to exit");
	pIn->GetPointClicked(x,y);


	delete pIn;
	delete pOut;	
	return 0;
}


