#include "ECS.h"

namespace ECS {

	enum Entity_templates : Mask_t {
		BoardTileTemplate = BoardVisual_m | BoardPosition_m | TerrainType_m,
		BoardPieceTemplate = BoardVisual_m | BoardPosition_m | RealTimeVisual_m | Health_m | Power_m | BoardSpeed_m | RealtimeSpeed_m | TeamAffiliation_m,
		RealtimePieceTemplate = RealTimeVisual_m | RealTimePosition_m | RealTimeMomentum_m | RealTimeRotation_m | RotationalMomentum_m | RealTimeCollisionBody_m | Health_m,
		RealtimeBulletTemplate = RealTimeVisual_m | RealTimePosition_m | RealTimeMomentum_m | RealTimeRotation_m | RotationalMomentum_m | RealTimeCollisionBody_m | Damage_m
	};
	

	Entity makeBoardTile(EngineState& state, TerrainType type, Position pos) {
		const ComponentMask mask = (ComponentMask) BoardTileTemplate;
		auto entity = state.NewEntity(mask);

		*entity.boardVisual = Visual::Terrain_v;
		*entity.boardPosition = pos;
		*entity.terrainType = type;

		return entity;
	}
	
	Entity makeBoardPiecePawn(EngineState& state, TeamAffiliation team, Position pos) {
		const ComponentMask mask = (ComponentMask) BoardPieceTemplate;
		auto entity = state.NewEntity(mask);

		*entity.boardVisual = Visual::Pawn_v;
		*entity.team = team;
		*entity.boardPosition = pos;

		return entity;
	}

	Entity makeBoardPieceKnight(EngineState& state, TeamAffiliation team, Position pos) {
		const ComponentMask mask = (ComponentMask) BoardPieceTemplate;
		auto entity = state.NewEntity(mask);

		*entity.boardVisual = Visual::Knight_v;
		*entity.team = team;
		*entity.boardPosition = pos;

		return entity;
	}

	Entity makeBoardPieceQueen(EngineState& state, TeamAffiliation team, Position pos) {
		const ComponentMask mask = (ComponentMask) BoardPieceTemplate;
		auto entity = state.NewEntity(mask);

		*entity.boardVisual = Visual::Queen_v;
		*entity.team = team;
		*entity.boardPosition = pos;

		return entity;
	}

	void turnPieceRealtime(EngineState& state, EntityID entityID, Position pos) {
		ComponentMask mask = *state.ComponentMasks.getComponent(entityID);

		mask = (ComponentMask) (mask & RealtimePieceTemplate);

		state.setEntityComponents(entityID,mask);

		state.RealTimePositions.setComponent(entityID, pos);
	}

	void removePieceRealtime(EngineState& state, EntityID entityID) {
		ComponentMask mask = *state.ComponentMasks.getComponent(entityID);

		mask = (ComponentMask) (mask & ~RealtimePieceTemplate);
		mask = (ComponentMask) (mask & BoardPieceTemplate);

		state.setEntityComponents(entityID, mask);
	}

	Entity makeBullet(EngineState& state, TeamAffiliation team, Damage newDamage, Position pos, Momentum mom) {
		const ComponentMask mask = (ComponentMask) RealtimeBulletTemplate;
		auto entity = state.NewEntity(mask);

		*entity.boardVisual = Visual::Bullet_v;
		*entity.team = team;
		*entity.damage = newDamage;
		*entity.realTimePosition = pos;
		*entity.realTimeMomentum = pos;

		return entity;
	}

	void GenerateBoard(EngineState& state) {
		makeBoardTile(state, FlatGround, {0,0,0});
		makeBoardTile(state, FlatGround, {0,1,0});
		makeBoardTile(state, FlatGround, {1,0,0});
		makeBoardTile(state, FlatGround, {1,1,0});
	}



	Game::Game()
	{
		//TODO
	}
	Game::~Game()
	{
		//TODO
	}
	void Game::GameLoop()
	{
		playing = true;

		float timePerTick = 1.0f / 120.0f;

		while (playing) {
			switch (gameType)
			{
			case ECS::Game::SinglePlayer:
			case ECS::Game::MultiPlayer:
				advanceTime(timePerTick);
				break;
			default:
				std::cout << "Invalid gametype" << std::endl;
				break;
			}
		}
		//TODO
	}
	void Game::ShowSplash()
	{
		std::cout << "Displaying splash screen" << std::endl;

		std::cout << std::endl << 
			"8 8888        8 8 8888888888   `8.`8888.      ,8'\n"\
			"8 8888        8 8 8888          `8.`8888.    ,8'\n"\
			"8 8888        8 8 8888           `8.`8888.  ,8'\n"\
			"8 8888        8 8 8888            `8.`8888.,8'\n"\
			"8 8888        8 8 888888888888     `8.`88888'\n"\
			"8 8888        8 8 8888             .88.`8888.\n"\
			"8 8888888888888 8 8888            .8'`8.`8888.\n"\
			"8 8888        8 8 8888           .8'  `8.`8888.\n"\
			"8 8888        8 8 8888          .8'    `8.`8888.\n"\
			"8 8888        8 8 888888888888 .8'      `8.`8888."
			<< std::endl << std::endl;

		TODO
	}
	void Game::RequestGameType()
	{
		std::cout << "Requesting desired game type" << std::endl;

		// TEMP autoselect becuase we have no input yet
		TODO
			gameType = SinglePlayer;

		switch (gameType)
		{
		case ECS::Game::Undecided:
			std::cout << "Game type " << "Undecided" << std::endl;
			break;
		case ECS::Game::SinglePlayer:
			std::cout << "Game type " << "SinglePlayer" << std::endl;
			break;
		case ECS::Game::MultiPlayer:
			std::cout << "Game type " << "MultiPlayer" << std::endl;
			break;
		default:
			TODOe
				break;
		}
	}
	void Game::setupGame()
	{
		auto state = TimeLine.NewState();

		state.PlayerTurn = Player1;

		status = ECS::Game::Board;

		GenerateBoard(state);
		
		makeBoardPiecePawn(state, Player1, {0,1,0});
		makeBoardPiecePawn(state, Player2, {0,1,0});



		TODO
	}
	TimeStamp Game::advanceTime(TimeStamp timeToAdvanceBy)
	{
		switch (status)
		{
		case ECS::Game::Paused: {
			EngineState & currentState = *TimeLine.getState(0);
			const EngineState & lastState = currentState;
			pausedLogic.Run(lastState, currentState);

			return currentState.WorldTime;
		}
			break;
		case ECS::Game::Board: {
			EngineState & currentState = TimeLine.NewState();
			const EngineState & lastState = TimeLine.getPreviousState();

			currentState.WorldTime += timeToAdvanceBy;

			boardLogic.Run(lastState, currentState);
			return currentState.WorldTime;
		}
		   break;
		case ECS::Game::Combat: {
			EngineState & currentState = TimeLine.NewState();
			const EngineState & lastState = TimeLine.getPreviousState();

			currentState.WorldTime += timeToAdvanceBy;

			combatLogic.Run(lastState, currentState);
			return currentState.WorldTime;
		}
			break;
		default:
			TODOe
				break;
		}
		TODOe
	}
}