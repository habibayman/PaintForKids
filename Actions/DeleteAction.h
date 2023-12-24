#ifndef DELETE_H
#define DELETE_H

#include "Action.h"
#include "SelectFigureAction.h"

class DeleteAction: public Action
{
	CFigure* ToBeDeleted;
public:
	DeleteAction(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	void Undo();
};
#endif
