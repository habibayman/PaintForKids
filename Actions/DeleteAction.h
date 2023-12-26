#ifndef DELETE_H
#define DELETE_H

#include "Action.h"
#include "SelectFigureAction.h"

class DeleteAction: public Action
{
	CFigure* backup;
	CFigure* ToBeDeleted;
public:
	DeleteAction(ApplicationManager* pApp, bool muted);
	virtual void ReadActionParameters();
	virtual void Execute();
	void Undo();
	void Redo();
	~DeleteAction();
};
#endif
