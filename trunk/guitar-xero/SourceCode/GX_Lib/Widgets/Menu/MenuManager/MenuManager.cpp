#include "MenuManager.hpp"

#include "Input.hpp"


// MenuManager
void MenuManager::SetHost(WidgetMenu* host)
{
	host_ = host;
}


// MenuManagerVertical
void MenuManagerVertical::ProcessActions()
{
	if(Input::input_->GetMode()!=EVENT)
	{
		host_->ActionExec();
		return;
	}

		// UP
	if(Actions::actions_->GetAction(UP))
	{
		Actions::actions_->SetAction(UP, false);
		host_->ActionPrev();
	}

		// DOWN
	else if(Actions::actions_->GetAction(DOWN))
	{
		Actions::actions_->SetAction(DOWN, false);
		host_->ActionNext();
	}

		// MORE / LESS / SELECT
	else if(Actions::actions_->GetAction(MORE) ||
		Actions::actions_->GetAction(LESS) ||
		Actions::actions_->GetAction(SELECT))
	{
		host_->ActionExec();

		Actions::actions_->SetAction(MORE, false);
		Actions::actions_->SetAction(SELECT, false);
	}

		// BACK / LESS
	if(Actions::actions_->GetAction(BACK) ||
		Actions::actions_->GetAction(LESS))
	{
		Actions::actions_->SetAction(BACK, false);
		Actions::actions_->SetAction(LESS, false);

		host_->ActionBack();
	}
}