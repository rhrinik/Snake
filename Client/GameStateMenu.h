#pragma once
#include "GameState.h"
#include "Image.h"
#include "Text.h"
#include <vector>

class GameStateMenu : public GameState {
    States runState() override;
    void updateState() override;
    void drawState() override;
    void initState() override;
    Image imageBackground;
    Text menuTitle;
public:
    GameStateMenu(Window &wnd, Graphics &gfx) : GameState(wnd, gfx) {}
};
