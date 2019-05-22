#include "ECS.h"
#include "Window.h"
#include "BoardManager.h"

namespace ECS {

	
    Entity makeBoardPiece(EngineState& state, ModelID model, TeamAffiliation team, BoardPosition pos, BoardPiece piece, Health hp, Power power) {
        const ComponentMask mask = (ComponentMask)BoardPieceTemplate;
        Entity entity = state.NewEntity(mask);

        *entity.boardModel = Resources::GetModel(model);
        *entity.boardPosition = pos;
        *entity.team = team;
        *entity.boardPiece = piece;
        *entity.health = hp;
        *entity.power = power;
        BoardManager::SetTransformFromBoard(entity.boardTransform, entity.boardPosition);
        return entity;
    }

    Entity makeBoardTile(EngineState& state, ModelID model, TerrainType type, BoardPosition pos) {
        const ComponentMask mask = (ComponentMask)BoardTileTemplate;
        auto entity = state.NewEntity(mask);

        *entity.boardModel = Resources::GetModel(model);
        *entity.boardPosition = pos;
        *entity.terrainType = type;
        BoardManager::SetTransformFromBoard(entity.boardTransform, entity.boardPosition);
		return entity;
	}
	
	Entity makeBoardPiecePawn(EngineState& state, TeamAffiliation team, BoardPosition pos) {
		const ComponentMask mask = (ComponentMask) BoardPieceTemplate;
		auto entity = state.NewEntity(mask);

        *entity.boardModel = Resources::GetModel(Piece1Model);
		*entity.team = team;
        *entity.boardPosition = pos;
        *entity.boardPiece = { 3 };

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
        Board b = BoardManager::MakeBoard(state, 5);
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
		auto & state = TimeLine.NewState();

		state.PlayerTurn = Player1;

		state.status = ECS::EngineState::Board;

		GenerateBoard(state);

        for (int i = 0; i < 3; i++) {
            int x = 5 - glm::pow(1 - i, 2) + i/2;
            int y = 1 - i;
            std::cout << "p1 = " << x << ", " << y << std::endl;
            std::cout << "p2 = " << -x << ", " << y << std::endl;
            Entity p1 = makeBoardPiecePawn(state, Player1, { x, y });
            BoardManager::SetTransformFromBoard(p1.boardTransform, p1.boardPosition);
            Entity p2 = makeBoardPiecePawn(state, Player2, { -x, -y });
            BoardManager::SetTransformFromBoard(p2.boardTransform, p2.boardPosition);
        }

		TODO
	}

    void BasicCopyState(const ECS::Engine::EngineState & lastState, ECS::Engine::EngineState & newState) {
        newState.PlayerTurn = lastState.PlayerTurn;
        newState.status = lastState.status;
        newState.WorldTime = lastState.WorldTime;
        newState.EntityIDs = lastState.EntityIDs;
        newState.ComponentMasks = lastState.ComponentMasks;
        newState.Healths = lastState.Healths;
        newState.Damages = lastState.Damages;
        newState.Powers = lastState.Powers;

        newState.Teams = lastState.Teams;
        newState.AI = lastState.AI;
        newState.TerrainTypes = lastState.TerrainTypes;
    }

	TimeStamp Game::advanceTime(TimeStamp timeToAdvanceBy)
	{
		EngineState * currentState = TimeLine.getState(0);
		const EngineState * lastState;

		switch (currentState->status)
		{
        case ECS::EngineState::Intro: {

            return currentState->WorldTime;
        }
                                      break;
		case ECS::EngineState::Paused: {
			currentState = TimeLine.getState(0);
			lastState = currentState;
			pausedLogic.Run(*lastState, *currentState);

			return currentState->WorldTime;
		}
									   break;
		case ECS::EngineState::Board: {
			currentState = &TimeLine.NewState();
			lastState = &TimeLine.getPreviousState();
            BasicCopyState(*lastState, *currentState);
			currentState->WorldTime += timeToAdvanceBy;

			boardLogic.Run(*lastState, *currentState);
			return currentState->WorldTime;
		}
									  break;
		case ECS::EngineState::Combat: {
			currentState = &TimeLine.NewState();
			lastState = &TimeLine.getPreviousState();

			currentState->WorldTime += timeToAdvanceBy;

			combatLogic.Run(*lastState, *currentState);
			return currentState->WorldTime;
		}
									   break;
		default:
			TODOe
				break;
		}
		TODOe
	}
}