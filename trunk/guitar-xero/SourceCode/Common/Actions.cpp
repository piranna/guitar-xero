#include "Actions.hpp"

#include <stdlib.h>


Actions* Actions::actions_ = NULL;

void Actions::ResetActions()
// Set all actions to false
{
	for(int i=0; i<enumActions; i++)
		action_[i] = false;
}

void Actions::SetAction(tAction action, bool state)
// Set an action
{
	action_[action] = state;
}

bool Actions::GetAction(tAction action)
// Get an action state
{
	return action_[action];
}

Actions::Actions()
{
	if(!actions_)
	{
		actions_=this;

		ResetActions();
	}
}
