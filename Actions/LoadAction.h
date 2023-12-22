#ifndef LOAD_H
#define LOAD_H

#include "Action.h"

class LoadAction: public Action
{
	string FileName;
public:
	LoadAction(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	//virtual void Execute();

};
#endif