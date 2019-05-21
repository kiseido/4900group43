#pragma once

#include "Common.h"

#include "Components.h"

#include "Entity.h"
#include "Engine.h"
#include "Systems.h"

namespace ECS {
	
	//typedef uint16_t ComponentMask;

	class Random {
	public:
		static void setSeed(int);
		static int getInt();
	};


	using namespace ECS::Engine;
	using namespace ECS::Systems;


	class Game {
		enum GameType {
			Undecided,
			SinglePlayer,
			MultiPlayer
		};

		GameType gameType;
		EngineStateManager TimeLine;

		PausedSystemsPack pausedLogic;
		BoardSystemsPack boardLogic;
		CombatSystemsPack combatLogic;

		RTPhysics rtPhysics;
		BoardRenderer boardRenderer;
		CombatRenderer combatRenderer;

		bool playing;
	public:
		Game();
		~Game();
		// generate next world state
		// @param amount of time to advance worldstate by
		// @return current board time
		TimeStamp advanceTime(TimeStamp);
		void GameLoop();
		void ShowSplash();
		void RequestGameType();
		void Setup();
	};
}
