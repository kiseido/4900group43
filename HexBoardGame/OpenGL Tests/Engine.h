#pragma once

#include "ECS.h"
#include "Transform.h"
#include "Graphics.h"
#include "Board.h"

#include <queue>
#include <list>

namespace ECS {
	namespace Engine {

		template <typename ComponentT>
		class ComponentContainer {
		private:
		public:
			std::unordered_map<EntityID, int> EntityMap;
			std::unordered_map<int, EntityID> ComponentMap;
			std::vector<ComponentT> Components;
			std::queue<int> Unassigned;

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
					int pos;

					if (Unassigned.size() > 0)
					{
						pos = Unassigned.front();
						Unassigned.pop();
					}
					else
						pos = Components.size();

					EntityMap.insert_or_assign(id, pos);
					ComponentMap.insert_or_assign(pos, id);

					Components.push_back(component);
				}
				else
					Components.at(index->second) = component;
			}
			void removeComponent(const EntityID& id) {
				auto index = EntityMap.find(id);

				if (index == EntityMap.end())
					return;

				Unassigned.push(index->second);

				ComponentMap.erase(index->first);
				EntityMap.erase(index);
			}
			inline ComponentT* operator[](const EntityID&) {
				return getComponent(EntityID);
			}
		};

		struct EngineState {
			enum GameStatus {
				Paused,
				Board,
				Combat
			};
			
			// Time this state represents once completed
			TimeStamp WorldTime;

			TeamAffiliation PlayerTurn;

			GameStatus status;

			std::list<EntityID> EntityIDs;


            //-------Containers:
            //Mask:
			ComponentContainer<ComponentMask> ComponentMasks;

            //Stats
			ComponentContainer<Health> Healths;
			ComponentContainer<Damage> Damages;
			ComponentContainer<Power> Powers;

            //Board
            ComponentContainer<Transform> BoardTransforms;
            ComponentContainer<Model> BoardModels;
			ComponentContainer<BoardPosition> BoardPositions;
            ComponentContainer<BoardPiece> BoardPieces;
            ComponentContainer<BoardMovement> BoardMovements;

            //Combat
            ComponentContainer<Transform> CombatTransforms;
			ComponentContainer<Momentum> Momentums;
			ComponentContainer<Momentum> RotationalMomentums;
			ComponentContainer<Model> CombatModels;
			ComponentContainer<CollisionBody> CombatCollisionBodies;
			ComponentContainer<CombatSpeed> CombatSpeeds;

			ComponentContainer<TeamAffiliation> Teams;

			ComponentContainer<AIStatus> AI;

			ComponentContainer<TerrainType> TerrainTypes;

			Entity NewEntity(ComponentMask);
			Entity getEntity(EntityID);
			void removeEntity(EntityID);
			void setEntityComponents(EntityID, ComponentMask);
		};



		class EngineStateManager {
		private:
			std::unordered_map<int, EngineState> Moments;
			int historyCutoff;
			int currentMoment;
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