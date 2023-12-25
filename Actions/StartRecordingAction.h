#ifndef STARTRECORDINGACTION_H
#define STARTRECORDINGACTION_H

#include "Action.h"

class StartRecordingAction : public Action
{
public:
	StartRecordingAction(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	void Undo();
};

#endif