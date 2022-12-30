#pragma once
#include "GameState.h"
#include "Image.h"
#include "Text.h"
#include <vector>
#include "Utilities.h"

class GameStateMenu : public GameState {
    States runState() override;
    void updateState() override;
    void drawState() override;
    void initState() override;
    Image imageBackground;
    Text menuTitle;
    Font font;
public:
    GameStateMenu(Window &wnd, Graphics &gfx) : GameState(wnd, gfx) {}
};
