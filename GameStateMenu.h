#pragma once
#include "GameState.h"
#include "Image.h"
#include "Text.h"

class GameStateMenu : public GameState {
    States runState(Graphics &gfx) override;
    void updateState() override;
    void drawState(Graphics &gfx) override;
    void initState() override;
    Image imageBackground;
    Text text;
};
