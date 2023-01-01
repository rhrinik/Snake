#pragma once
#include "GameState.h"
#include "../Display/Image.h"
#include "../Display/Text.h"
#include <vector>
#include "../../Shared/Utility/Utilities.h"

class GameStateMenu : public GameState {
    States runState(States previous) override;
    States updateState() override;
    void drawState() override;
    void initState() override;
    Image imageBackground;
    Font font;
    Text title;
    Text play;
    Text exit;
    enum Selected { Play, Exit } selected{Play};
    bool selectionConfirmed{false};
public:
    void onKeyUp() override;
    void onKeyDown() override;
    void onKeyEnter() override;
    GameStateMenu(Window &wnd, Graphics &gfx) : GameState(wnd, gfx) {}

    void restart();
};
