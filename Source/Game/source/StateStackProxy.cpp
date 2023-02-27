#include "stdafx.h"

#include "StateStackProxy.h"

#include "StateStack.h"
#include "MenuState.h"
#include "OptionState.h"
#include "InGameState.h"

StateStackProxy::StateStackProxy(StateStack& aStateStack) : myStateStack(aStateStack)
{
	
}

void StateStackProxy::Init()
{
	myStateStack.CreateState(StateID::Menu, new MenuState(*this));
	myStateStack.CreateState(StateID::Options, new OptionState(*this));
	myStateStack.CreateState(StateID::InGame, new InGameState(*this));
}

void StateStackProxy::PushState(StateID aID)
{
	myStateStack.PushState(aID);
}
