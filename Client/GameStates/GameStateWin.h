#pragma once
#include "GameState.h"

class GameStateWin : public GameState {
    [[nodiscard]] States runState(States previous) override;
    States updateState() override;
    void drawState() override;
    void initState() override;
    Image loseImage;
public:
    GameStateWin(Window &wnd, Graphics &gfx) : GameState(wnd, gfx) {}
    void onKeyEnter() override;
};
