#pragma once
#include "../../Shared/GameObjects/GameSpaceBase.h"

class GameSpace : public GameSpaceBase {
    GameSpace(const std::pair<int, int> &space) : GameSpaceBase(space) {}
};
