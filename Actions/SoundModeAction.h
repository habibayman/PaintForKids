#ifndef SOUND_H
#define SOUND_H
#include "Action.h"

class SoundModeAction : public Action
{
	bool* muted; 
public:
	SoundModeAction(ApplicationManager* pApp, bool* muted);
	virtual void ReadActionParameters();
	virtual void Execute();
	void Undo();
	void Redo();
};
#endif
