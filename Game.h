#pragma once
#include "Graphics.h"
#include "GameState.h"
#include "GameStatePlaying.h"
#include "GameStateDummy.h"

class Game {
    Graphics& gfx;
public:
    explicit Game(Graphics &gfx) : gfx(gfx) {}
    void run();
    bool init();

    bool running{false};
    [[nodiscard]] bool isRunning() const;

    std::vector<std::unique_ptr<GameState>> states;
    GameState::States currentState{GameState::Playing};
    GameState::States previousState{GameState::Start};
};
