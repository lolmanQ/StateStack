#pragma once
#include "StateEnum.h"

class StateStack;

class StateStackProxy
{
public:
	explicit StateStackProxy(StateStack& aStateStack);

	void Init();
	
	void PushState(StateID aID);
	
private:
	StateStack& myStateStack;
};

