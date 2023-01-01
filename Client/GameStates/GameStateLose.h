#pragma once
#include "GameState.h"

class GameStateLose : public GameState {
    [[nodiscard]] States runState(States previous) override;
    States updateState() override;
    void drawState() override;
    void initState() override;
    Image loseImage;
public:
    GameStateLose(Window &wnd, Graphics &gfx) : GameState(wnd, gfx) {}
    void onKeyEnter() override;
};
