#ifndef LOAD_H
#define LOAD_H

#include "Action.h"
#include "..\Figures\CFigure.h"  

class LoadAction: public Action
{
	string FileName;
	CFigure* CurrentFigure; 
	int ReadFigCount;
	string ReadDrawColor, ReadFillColor, ReadType;
public:
	LoadAction(ApplicationManager* pApp, bool muted);
	virtual void ReadActionParameters();
	//virtual void Execute();
	void Undo();
	virtual void Execute();

};
#endif