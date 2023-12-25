#ifndef SWITCHTOPLAYCTION_H
#define SWITCHTOPLAYACTION_H

#include "Action.h"
class SwitchToPlayAction :
	public Action
{
public:
	SwitchToPlayAction(ApplicationManager* pApp, bool muted);

	//Read 
	virtual void ReadActionParameters();

	//Add SwitchToPLayAction to ApplicationManager
	virtual void Execute();

	void Undo();

};

#endif