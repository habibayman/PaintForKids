#ifndef CLEAR_H
#define CLEAR_H

#include "Action.h"

class ClearAction : public Action
{
	string checker;
public:
	ClearAction(ApplicationManager* pApp); 
	virtual void ReadActionParameters();
	virtual void Execute();
};
#endif
