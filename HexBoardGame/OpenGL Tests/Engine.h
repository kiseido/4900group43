#pragma once

#include "ECS.h"

namespace ECS {
	namespace Engine {

		template <typename ComponentT>
		class ComponentContainer {
		private:
		public:
			std::unordered_map<EntityID, int> EntityMap;
			std::unordered_map<int, EntityID> ComponentMap;
			std::vector<ComponentT> Components;
			ComponentT* getComponent(const EntityID& id) {
				auto index = EntityMap.find(id);

				if (index == EntityMap.end())
					return nullptr;
				else
					return &Components.at(index->second);
			}
			void setComponent(const EntityID& id, const ComponentT& component) {
				auto index = EntityMap.find(id);

				if (index == EntityMap.end()) {
					//TODO
					EntityMap.insert(id, Components.size());
					ComponentMap.insert(Components.size(),id);
					Components.push_back(component);
				}
				else
					Components.at(index->second) = component;
			}
			inline ComponentT* operator[](const EntityID&) {
				return getComponent(EntityID);
			}
		};

		struct EngineState {
			
			// Time this state represents once completed
			TimeStamp WorldTime;

			ComponentContainer<ComponentMask> ComponentMasks;

			ComponentContainer<Health> Healths;

			ComponentContainer<Visual> BoardVisuals;
			ComponentContainer<CollisionBody> BoardCollisionBodies;
			ComponentContainer<Position> BoardPositions;

			ComponentContainer<Position> RealTimePositions;
			ComponentContainer<Momentum> Momentums;
			ComponentContainer<Rotation> Rotations;
			ComponentContainer<Momentum> RotationalMomentums;
			ComponentContainer<Visual> RealTimeVisuals;
			ComponentContainer<CollisionBody> RealTimeCollisionBodies;

			Entity NewEntity(ComponentMask);
			Entity getEntity(EntityID);
			void setEntityComponents(ComponentMask);
		};



		class EngineStateManager {
		private:
			std::unordered_map<int, EngineState> Moments;
			int historyCutoff;

			int LastFinishedState;
		public:
			EngineStateManager();

			//Returns Engine state with 0 being the most recently completed state
			EngineState* getState(int);
			int getHistoryLength();
			const EngineState& getPreviousState() const;
			EngineState& NewState();
		};
	}
}