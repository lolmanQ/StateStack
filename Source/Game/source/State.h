#pragma once

class StateStackProxy;

class State
{
public:
	explicit State(StateStackProxy& aStateStackProxy) : myStateStackProxy(aStateStackProxy) {}
	
	virtual ~State() = default;

	virtual void Init() = 0;
	
	virtual bool Update() = 0;
	virtual void Render() = 0;

	virtual void ExitState() = 0;

	virtual void Deactivate() = 0;

	virtual bool LetThroughRender() = 0;

protected:
	StateStackProxy& myStateStackProxy;
};

