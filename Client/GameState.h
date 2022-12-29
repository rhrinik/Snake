#pragma once
#include "Graphics.h"

class GameState {
public:
    enum States { Start, End, Playing, Menu };
    [[nodiscard]] States run(Graphics &gfx);
    virtual void update();
    virtual void draw(Graphics &gfx);
    virtual void init();
    virtual ~GameState() = default;
private:
    [[nodiscard]] virtual States runState (Graphics &gfx) = 0;
    virtual void updateState() = 0;
    virtual void drawState(Graphics &gfx) = 0;
    virtual void initState() = 0;
};
