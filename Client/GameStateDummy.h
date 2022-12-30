#pragma once
#include "GameState.h"

class GameStateDummy : public GameState {
    [[nodiscard]] States runState() override;
    void updateState() override;
    void drawState() override;
    void initState() override;
public:
    GameStateDummy(Window &wnd, Graphics &gfx) : GameState(wnd, gfx) {}
};
