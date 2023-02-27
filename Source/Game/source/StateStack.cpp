#include "StateStack.h"

void StateStack::CreateState(StateID aID, State* aState)
{
	myCachedStates[aID] = aState;
}

void StateStack::PushState(StateID aID)
{
	if (GetCurrentState() != nullptr)
	{
		GetCurrentState()->ExitState();
	}
	myStates.push_back(myCachedStates[aID]);
	myCachedStates[aID]->Init();
}

void StateStack::Pop()
{
	myStates.back()->Deactivate();
	myStates.pop_back();
}

State* StateStack::GetCurrentState()
{
	if (myStates.empty())
	{
		return nullptr;
	}

	return myStates.back();
}

void StateStack::RenderStateAtIndex(size_t aIndex)
{
	if (aIndex < 0) // basfallet
		return;
	// Rendera state under
	if (myStates[aIndex]->LetThroughRender() == true)
		RenderStateAtIndex(aIndex - 1);
	myStates[aIndex]->Render();
}
