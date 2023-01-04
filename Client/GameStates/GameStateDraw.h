#pragma once
#include "GameState.h"
#include "../../Shared/Utility/Utilities.h"

class GameStateDraw : public GameState {
    [[nodiscard]] States runState(States previous) override;
    States updateState() override;
    void drawState() override;
    void initState() override;
    Font font;
    Text title;
public:
    GameStateDraw(Window &wnd, Graphics &gfx) : GameState(wnd, gfx) {}
    void onKeyEnter() override;
};
