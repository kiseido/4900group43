#pragma once

#include "Common.h"

#include "Components.h"

#include "Entity.h"
#include "Engine.h"
#include "Systems.h"

namespace ECS {
	
	// Random
	// Provides a deterministic random number generate that can be syncronized between game client and server
	class Random {
	public:
		static void setSeed(int);
		static int getInt();
	};

	TimeStamp getTime();


	using namespace ECS::Engine;
	using namespace ECS::Systems;

	// Game
	// Encapsulates complete game state and logic
	class Game {
		enum GameType {
			Undecided,
			SinglePlayer,
			MultiPlayer
		};

		GameType gameType;
		EngineStateManager TimeLine;

        IntroSystem introLogic;

		PausedSystemsPack pausedLogic;
		BoardSystemsPack boardLogic;
		CombatSystemsPack combatLogic;

		RTPhysics rtPhysics;
		BoardRenderer boardRenderer;
		CombatRenderer combatRenderer;

		Networking networking;

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
