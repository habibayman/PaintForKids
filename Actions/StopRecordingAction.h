#ifndef STOPRECORDINGACTION_H
#define STOPRECORDINGACTION_H

#include "Action.h"

class StopRecordingAction : public Action
{
public:
	StopRecordingAction(ApplicationManager* pApp, bool muted);
	virtual void ReadActionParameters();
	virtual void Execute();
	void Undo();
	void Redo();
};


#endif 