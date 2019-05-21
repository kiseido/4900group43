#include "ECS.h"
#include "Window.h"

namespace ECS {

	enum Entity_templates : Mask_t {
		BoardTileTemplate = BoardTransform_m | BoardModel_m | BoardPosition_m | TerrainType_m,
		BoardPieceTemplate = BoardTransform_m | BoardModel_m | BoardPosition_m | Health_m | Power_m | BoardSpeed_m | TeamAffiliation_m,
		CombatPieceTemplate = CombatTransform_m | CombatModel_m | Momentum_m | RotationalMomentum_m | CombatCollisionBody_m | Health_m,
		CombatBulletTemplate = CombatTransform_m | CombatModel_m | Momentum_m | RotationalMomentum_m | CombatCollisionBody_m | Damage_m
	};
	

	Entity makeBoardTile(EngineState& state, ModelID model, TerrainType type, BoardPosition pos) {
		const ComponentMask mask = (ComponentMask) BoardTileTemplate;
		auto entity = state.NewEntity(mask);

        *entity.boardModel = Resources::GetModel(model);
		*entity.boardPosition = pos;
		*entity.terrainType = type;

		return entity;
	}
	
	Entity makeBoardPiecePawn(EngineState& state, TeamAffiliation team, BoardPosition pos) {
		const ComponentMask mask = (ComponentMask) BoardPieceTemplate;
		auto entity = state.NewEntity(mask);

        *entity.boardModel = Resources::GetModel(Piece1Model);
		*entity.team = team;
        *entity.boardPosition = pos;

		return entity;
	}

	Entity makeBoardPieceKnight(EngineState& state, TeamAffiliation team, BoardPosition pos) {
		const ComponentMask mask = (ComponentMask) BoardPieceTemplate;
		auto entity = state.NewEntity(mask);

        *entity.boardModel = Resources::GetModel(Piece1Model);
        *entity.team = team;
        *entity.boardPosition = pos;

		return entity;
	}

	Entity makeBoardPieceQueen(EngineState& state, TeamAffiliation team, BoardPosition pos) {
		const ComponentMask mask = (ComponentMask) BoardPieceTemplate;
		auto entity = state.NewEntity(mask);

        *entity.boardModel = Resources::GetModel(Piece1Model);
        *entity.team = team;
        *entity.boardPosition = pos;

		return entity;
	}

	void turnPieceRealtime(EngineState& state, EntityID entityID, Position pos) {
		ComponentMask mask = *state.ComponentMasks.getComponent(entityID);

		mask = (ComponentMask) (mask & CombatPieceTemplate);

		state.setEntityComponents(entityID,mask);

		//state.CombatPositions.setComponent(entityID, pos);
	}

	void removePieceRealtime(EngineState& state, EntityID entityID) {
		ComponentMask mask = *state.ComponentMasks.getComponent(entityID);

		mask = (ComponentMask) (mask & ~CombatPieceTemplate);
		mask = (ComponentMask) (mask & BoardPieceTemplate);

		state.setEntityComponents(entityID, mask);
	}

	Entity makeBullet(EngineState& state, TeamAffiliation team, Damage newDamage, Transform transf, Momentum mom) {
		const ComponentMask mask = (ComponentMask) CombatBulletTemplate;
		auto entity = state.NewEntity(mask);

		*entity.team = team;
		*entity.damage = newDamage;
		*entity.combatTransform = transf;
		*entity.momentum = mom;

		return entity;
	}

	void GenerateBoard(EngineState& state) {
		makeBoardTile(state, GrassTileModel, FlatGround, {0,0});
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

		while (Window::IsActive()) {
            Window::Update();
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
			"\t8 8888        8 8 8888888888   `8.`8888.      ,8'\n"\
			"\t8 8888        8 8 8888          `8.`8888.    ,8'\n"\
			"\t8 8888        8 8 8888           `8.`8888.  ,8'\n"\
			"\t8 8888        8 8 8888            `8.`8888.,8'\n"\
			"\t8 8888        8 8 888888888888     `8.`88888'\n"\
			"\t8 8888        8 8 8888             .88.`8888.\n"\
			"\t8 8888888888888 8 8888            .8'`8.`8888.\n"\
			"\t8 8888        8 8 8888           .8'  `8.`8888.\n"\
			"\t8 8888        8 8 8888          .8'    `8.`8888.\n"\
			"\t8 8888        8 8 888888888888 .8'      `8.`8888."
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
	void Game::Setup()
	{
		auto state = TimeLine.NewState();

		state.PlayerTurn = Player1;

		state.status = ECS::EngineState::Board;

		GenerateBoard(state);
		
		Entity p1 = makeBoardPiecePawn(state, Player1, {0,0});


		TODO
	}
	TimeStamp Game::advanceTime(TimeStamp timeToAdvanceBy)
	{
		EngineState * currentState = TimeLine.getState(0);
		const EngineState * lastState = currentState;

		switch (currentState->status)
		{
		case ECS::EngineState::Paused: {
			EngineState & currentState = *TimeLine.getState(0);
			const EngineState & lastState = currentState;
			pausedLogic.Run(lastState, currentState);

			return currentState.WorldTime;
		}
			break;
		case ECS::EngineState::Board: {
			EngineState & currentState = TimeLine.NewState();
			const EngineState & lastState = TimeLine.getPreviousState();

			currentState.WorldTime += timeToAdvanceBy;

			boardLogic.Run(lastState, currentState);
			return currentState.WorldTime;
		}
		   break;
		case ECS::EngineState
		::Combat: {
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