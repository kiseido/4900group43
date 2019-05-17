#pragma once
#include "ECS.h"
#include "Entity.h"

namespace Game {
    void Start();
    void MouseLeftClick();
    void MouseRightClick();
    void GameLoop(double currentTime);
}