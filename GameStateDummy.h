#pragma once
#include "GameState.h"

class GameStateDummy : public GameState {
private:
    [[nodiscard]] States runState(Graphics &gfx) override;
    void updateState() override;
    void drawState(Graphics &gfx) override;
    void initState() override;
};
