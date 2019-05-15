#include "Game.h"
#include "ECS.h"
#include "Renderer.h"
#include "Transformer.h"

void Game::GameLoop(double currentTime) {
    Renderer::RenderScene();
}