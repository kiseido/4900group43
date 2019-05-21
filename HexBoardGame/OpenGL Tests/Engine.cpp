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

		EntityIDs.push_back(newID);

		return getEntity(newID);
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

        ComponentMask* componentMask;

        e.health = (mask & Health_m) ? Healths.getComponent(id) : nullptr;
        e.damage = (mask & Damage_m) ? Damages.getComponent(id) : nullptr;
        e.power = (mask & Power_m) ? Powers.getComponent(id) : nullptr;

        e.boardTransform = (mask & BoardTransform_m) ? BoardTransforms.getComponent(id) : nullptr;
        e.boardModel = (mask & BoardModel_m) ? BoardModels.getComponent(id) : nullptr;
        e.boardPosition = (mask & BoardPosition_m) ? BoardPositions.getComponent(id) : nullptr;
        e.boardSpeed = (mask & BoardSpeed_m) ? BoardSpeeds.getComponent(id) : nullptr;

        e.combatTransform = (mask & CombatTransform_m) ? CombatTransforms.getComponent(id) : nullptr;
        e.momentum = (mask & Momentum_m) ? Momentums.getComponent(id) : nullptr;
        e.rotationalMomentum = (mask & RotationalMomentum_m) ? RotationalMomentums.getComponent(id) : nullptr;
        e.combatModel = (mask & CombatModel_m) ? CombatModels.getComponent(id) : nullptr;
        e.combatCollisionBody = (mask & CombatCollisionBody_m) ? CombatCollisionBodies.getComponent(id) : nullptr;
        e.combatSpeed = (mask & CombatSpeed_m) ? CombatSpeeds.getComponent(id) : nullptr;

        e.team = (mask & TeamAffiliation_m) ? Teams.getComponent(id) : nullptr;

        e.terrainType = (mask & TerrainType_m) ? TerrainTypes.getComponent(id) : nullptr;

		return e;
	}

	void Engine::EngineState::removeEntity(EntityID id)
	{
		setEntityComponents(id, ECS::ComponentMask::None_m);

		ComponentMasks.removeComponent(id);

        //EntityIDs.remove(id);

		for (auto it = EntityIDs.begin(); it != EntityIDs.end(); ++it) {
			if (*it == id) {
				EntityIDs.erase(it);
				break;
			}
		}

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

            if (addMaskCheck(Health_m)) {
                Healths.setComponent(id, 0);
            }
            if (addMaskCheck(Damage_m)) {
                Damages.setComponent(id, 0);
            }
            if (addMaskCheck(Power_m)) {
                Powers.setComponent(id, 0);
            }
            if (addMaskCheck(BoardTransform_m)) {
                BoardTransforms.setComponent(id, Transform{});
            }
            if (addMaskCheck(BoardModel_m)) {
                BoardModels.setComponent(id, Model{});
            }
			if (addMaskCheck(BoardPosition_m)) {
                BoardPositions.setComponent(id, BoardPosition{});
			}
            if (addMaskCheck(BoardTransform_m)) {
                BoardTransforms.setComponent(id, Transform{});
            }
			if (addMaskCheck(BoardSpeed_m)) {
				BoardSpeeds.setComponent(id, DefaultSpeed);
			}
            if (addMaskCheck(CombatTransform_m)) {
                CombatTransforms.setComponent(id, Transform{});
            }
			if (addMaskCheck(CombatModel_m)) {
				CombatModels.setComponent(id, Model{});
			}
			if (addMaskCheck(Momentum_m)) {
				Momentums.setComponent(id, DefaultMom);
			}
			if (addMaskCheck(RotationalMomentum_m)) {
				RotationalMomentums.setComponent(id, DefaultRot);
			}
			if (addMaskCheck(CombatCollisionBody_m)) {
				CombatCollisionBodies.setComponent(id, DefaultCol);
			}
			if (addMaskCheck(CombatSpeed_m)) {
				CombatSpeeds.setComponent(id, DefaultSpeed);
			}
			if (addMaskCheck(TeamAffiliation_m)) {
				Teams.setComponent(id, Neutral);
			}
            if (addMaskCheck(AiStatus_m)) {
                AI.setComponent(id, NoAI);
            }
			if (addMaskCheck(TerrainType_m)) {
				TerrainTypes.setComponent(id, Storm);
			}

#undef addMaskCheck
		}
		if (removeMask != None_m) {
#define removeMaskCheck(MASK) (removeMask & MASK) != None_m

            if (removeMaskCheck(Health_m)) {
                Healths.removeComponent(id);
            }
            if (removeMaskCheck(Damage_m)) {
                Damages.removeComponent(id);
            }
            if (removeMaskCheck(Power_m)) {
                Powers.removeComponent(id);
            }
            if (removeMaskCheck(BoardTransform_m)) {
                BoardTransforms.removeComponent(id);
            }
            if (removeMaskCheck(BoardModel_m)) {
                BoardModels.removeComponent(id);
            }
            if (removeMaskCheck(BoardPosition_m)) {
                BoardPositions.removeComponent(id);
            }
            if (removeMaskCheck(BoardTransform_m)) {
                BoardTransforms.removeComponent(id);
            }
            if (removeMaskCheck(BoardSpeed_m)) {
                BoardSpeeds.removeComponent(id);
            }
            if (removeMaskCheck(CombatTransform_m)) {
                CombatTransforms.removeComponent(id);
            }
            if (removeMaskCheck(CombatModel_m)) {
                CombatModels.removeComponent(id);
            }
            if (removeMaskCheck(Momentum_m)) {
                Momentums.removeComponent(id);
            }
            if (removeMaskCheck(RotationalMomentum_m)) {
                RotationalMomentums.removeComponent(id);
            }
            if (removeMaskCheck(CombatCollisionBody_m)) {
                CombatCollisionBodies.removeComponent(id);
            }
            if (removeMaskCheck(CombatSpeed_m)) {
                CombatSpeeds.removeComponent(id);
            }
            if (removeMaskCheck(TeamAffiliation_m)) {
                Teams.removeComponent(id);
            }
            if (removeMaskCheck(AiStatus_m)) {
                AI.removeComponent(id);
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