#include "ECS.h"

namespace ECS {

	const EngineState & EngineStateManager::getPreviousState() const
	{
		return Moments.at(currentMoment-1);
	}
	EngineState & EngineStateManager::NewState()
	{
		currentMoment++;
		Moments._Insert_or_assign(currentMoment, EngineState());
		return Moments.at(currentMoment);
	}

	EngineStateManager::EngineStateManager()
	{
		currentMoment = 0;
		historyCutoff = 0;
		LastFinishedState = 0;
		//TODO
	}

	Entity EngineState::NewEntity(ComponentMask mask)
	{
		EntityID newID = Entity::NEXTID++;

		setEntityComponents(newID, mask);

		return getEntity(newID);
		TODOe
	}
	Entity EngineState::getEntity(EntityID id)
	{
		Entity e;
		e.id = id;

		ComponentMask* pMask = ComponentMasks.getComponent(id);

		if (pMask == nullptr) {
			throw std::logic_error("Entity does not exist");
		}

		ComponentMask mask = *pMask;

		e.boardVisual = (mask & BoardVisual_m) ? BoardVisuals.getComponent(id) : nullptr;
		e.boardCollisionBody = (mask & BoardCollisionBody_m) ? BoardCollisionBodies.getComponent(id) : nullptr;
		e.boardPosition = (mask & BoardPosition_m) ? BoardPositions.getComponent(id) : nullptr;

		e.realTimeVisual = (mask & RealTimeVisual_m) ? RealTimeVisuals.getComponent(id) : nullptr;
		e.realTimePosition = (mask & RealTimePosition_m) ? RealTimePositions.getComponent(id) : nullptr;
		e.realTimeMomentum = (mask & RealTimeMomentum_m) ? Momentums.getComponent(id) : nullptr;
		e.realTimeRotation = (mask & RealTimeRotation_m) ? Rotations.getComponent(id) : nullptr;
		e.realTimeRotationalMomentum = (mask & RotationalMomentum_m) ? RotationalMomentums.getComponent(id) : nullptr;
		e.realTimeCollisionBody = (mask & RealTimeCollisionBody_m) ? RealTimeCollisionBodies.getComponent(id) : nullptr;

		e.health = (mask & Health_m) ? Healths.getComponent(id) : nullptr;
		e.damage = (mask & Damage_m) ? Damages.getComponent(id) : nullptr;
		e.power = (mask & Power_m) ? Powers.getComponent(id) : nullptr;

		e.boardSpeed = (mask & BoardSpeed_m) ? BoardSpeeds.getComponent(id) : nullptr;
		e.realTimeSpeed = (mask & RealtimeSpeed_m) ? RealtimeSpeeds.getComponent(id) : nullptr;

		e.team = (mask & TeamAffiliation_m) ? Teams.getComponent(id) : nullptr;

		e.terrainType = (mask & TerrainType_m) ? TerrainTypes.getComponent(id) : nullptr;

		return e;
	}
	void EngineState::setEntityComponents(EntityID id, ComponentMask mask)
	{
		ComponentMask* poldMask = ComponentMasks.getComponent(id);

		ComponentMask oldMask = None_m;

		ComponentMask addMask = mask;
		ComponentMask removeMask = ComponentMask::None_m;

		if (poldMask != nullptr) {
			oldMask = *poldMask;

			addMask = (ComponentMask) (oldMask ^ (oldMask & mask));
			removeMask = (ComponentMask) (mask ^ (oldMask & addMask));
		}

		

		if (addMask != None_m) {
#define addMaskCheck(MASK) mask & MASK && (oldMask & MASK) == None_m

			if (addMaskCheck(BoardVisual_m)) {
				BoardVisuals.setComponent(id, Unassigned_v);
			}
			if (addMaskCheck(BoardCollisionBody_m)) {
				BoardCollisionBodies.setComponent(id, DefaultCol);
			}
			if (addMaskCheck(BoardPosition_m)) {
				BoardPositions.setComponent(id, DefaultPos);
			}
			if (addMaskCheck(RealTimeVisual_m)) {
				RealTimeVisuals.setComponent(id, Unassigned_v);
			}
			if (addMaskCheck(RealTimePosition_m)) {
				RealTimePositions.setComponent(id, DefaultPos);
			}
			if (addMaskCheck(RealTimeMomentum_m)) {
				Momentums.setComponent(id, DefaultMom);
			}
			if (addMaskCheck(RealTimeRotation_m)) {
				Rotations.setComponent(id, DefaultRot);
			}
			if (addMaskCheck(RotationalMomentum_m)) {
				RotationalMomentums.setComponent(id, DefaultRot);
			}
			if (addMaskCheck(RealTimeCollisionBody_m)) {
				RealTimeCollisionBodies.setComponent(id, DefaultCol);
			}
			if (addMaskCheck(Health_m)) {
				Healths.setComponent(id, DefaultHealth);
			}
			if (addMaskCheck(Damage_m)) {
				Damages.setComponent(id, DefaultHealth);
			}
			if (addMaskCheck(Power_m)) {
				Powers.setComponent(id, DefaultHealth);
			}
			if (addMaskCheck(BoardSpeed_m)) {
				BoardSpeeds.setComponent(id, DefaultSpeed);
			}
			if (addMaskCheck(RealtimeSpeed_m)) {
				RealtimeSpeeds.setComponent(id, DefaultSpeed);
			}
			if (addMaskCheck(TeamAffiliation_m)) {
				Teams.setComponent(id, Neutral);
			}
			if (addMaskCheck(TerrainType_m)) {
				TerrainTypes.setComponent(id, Storm);
			}

#undef addMaskCheck
		}
		if (removeMask != None_m) {
#define removeMaskCheck(MASK) (removeMask & MASK) != None_m

			if (removeMaskCheck(BoardVisual_m)) {
				BoardVisuals.removeComponent(id);
			}
			if (removeMaskCheck(BoardCollisionBody_m)) {
				BoardCollisionBodies.removeComponent(id);
			}
			if (removeMaskCheck(BoardPosition_m)) {
				BoardPositions.removeComponent(id);
			}
			if (removeMaskCheck(RealTimeVisual_m)) {
				RealTimeVisuals.removeComponent(id);
			}
			if (removeMaskCheck(RealTimePosition_m)) {
				RealTimePositions.removeComponent(id);
			}
			if (removeMaskCheck(RealTimeMomentum_m)) {
				Momentums.removeComponent(id);
			}
			if (removeMaskCheck(RealTimeRotation_m)) {
				Rotations.removeComponent(id);
			}
			if (removeMaskCheck(RotationalMomentum_m)) {
				RotationalMomentums.removeComponent(id);
			}
			if (removeMaskCheck(RealTimeCollisionBody_m)) {
				RealTimeCollisionBodies.removeComponent(id);
			}
			if (removeMaskCheck(Health_m)) {
				Healths.removeComponent(id);
			}
			if (removeMaskCheck(Damage_m)) {
				Damages.removeComponent(id);
			}
			if (removeMaskCheck(Power_m)) {
				Powers.removeComponent(id);
			}
			if (removeMaskCheck(BoardSpeed_m)) {
				BoardSpeeds.removeComponent(id);
			}
			if (removeMaskCheck(RealtimeSpeed_m)) {
				RealtimeSpeeds.removeComponent(id);
			}
			if (removeMaskCheck(TeamAffiliation_m)) {
				Teams.removeComponent(id);
			}
			if (removeMaskCheck(TerrainType_m)) {
				TerrainTypes.removeComponent(id);
			}

#undef removeMaskCheck
		}

		ComponentMasks.setComponent(id, mask);
	}

	EngineState * EngineStateManager::getState(int stateDelta)
	{
		auto s = Moments.find(currentMoment - stateDelta);
		if (s != Moments.end())
			return &s->second;
		else
			return nullptr;
	}
}