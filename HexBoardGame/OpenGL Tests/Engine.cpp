#include "ECS.h"

namespace ECS {
	const EngineState & EngineStateManager::getPreviousState() const
	{
		TODOe
	}
	EngineState & EngineStateManager::NewState()
	{
		TODOe
	}

	EngineStateManager::EngineStateManager()
	{
		//TODO
	}

	Entity EngineState::NewEntity(ComponentMask)
	{
		TODOe
	}
	Entity EngineState::getEntity(EntityID)
	{
		TODOe
	}
	void EngineState::setEntityComponents(ComponentMask)
	{
		//TODO
	}

	EngineState * EngineStateManager::getState(int state)
	{
		auto s = Moments.find(state);
		if (s != Moments.end())
			return &s->second;
		else
			return nullptr;
	}
}