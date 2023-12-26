#ifndef CLEAR_H
#define CLEAR_H

#include "Action.h"

class ClearAction : public Action
{
	string checker;
public:
	ClearAction(ApplicationManager* pApp, bool muted); 
	virtual void ReadActionParameters();
	virtual void Execute();
	void Undo();
	void Redo();
};
#endif
