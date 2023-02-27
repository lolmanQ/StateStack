#pragma once
#include "State.h"
#include "StateEnum.h"
#include <vector>
#include <map>

class StateStack
{
private:
	std::map<StateID, State*> myCachedStates;

public:
	void CreateState(StateID aID, State* aState);

	void PushState(StateID aID);
	void Pop();
	
	size_t size() const { return myStates.size(); };

	State* GetCurrentState();

	void RenderStateAtIndex(size_t aIndex);

	std::vector<State*> myStates;

};

