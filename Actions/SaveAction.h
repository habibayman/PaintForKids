#ifndef SAVE_H
#define SAVE_H

#include "Action.h"

class SaveAction: public Action
{
	string FileName;
public:
	SaveAction(ApplicationManager* pApp, bool muted);
	virtual void ReadActionParameters();
	virtual void Execute();
};
#endif
