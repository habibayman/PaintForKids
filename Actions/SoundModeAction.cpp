#include "SoundModeAction.h"

SoundModeAction::SoundModeAction(ApplicationManager* pApp, bool* pmuted) : Action(pApp) 
{
	muted = pmuted;
}

void SoundModeAction::ReadActionParameters()
{
	//No needed parameters for this action
}

void SoundModeAction::Execute()
{
	if (*muted)
	{
		*muted = false;
	}
	else
	{
		*muted = true;
	}
}
