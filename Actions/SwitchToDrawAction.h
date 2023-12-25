#ifndef SWITCHTODRAWACTION_H
#define SWITCHTODRAWACTION_H

#include "Action.h"
class SwitchToDrawAction :
	public Action
{
public:
	SwitchToDrawAction(ApplicationManager* pApp, bool muted);

	//Read 
	virtual void ReadActionParameters();

	//Add SwitchToPLayAction to ApplicationManager
	virtual void Execute();

	void Undo();

};

#endif