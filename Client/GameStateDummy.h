#pragma once
#include "GameState.h"

class GameStateDummy : public GameState {
private:
    [[nodiscard]] States runState(Window &wnd, Graphics &gfx) override;
    void updateState(Window &wnd) override;
    void drawState(Graphics &gfx) override;
    void initState() override;
};
