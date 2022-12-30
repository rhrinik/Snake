#pragma once
#include "GameState.h"
#include "Image.h"
#include "Text.h"
#include <vector>

class GameStateMenu : public GameState {
    States runState(Window &wnd, Graphics &gfx) override;
    void updateState(Window &wnd) override;
    void drawState(Graphics &gfx) override;
    void initState() override;
    Image imageBackground;
    Text menuTitle;
};
