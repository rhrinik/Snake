#pragma once
#include "Graphics.h"

class GameState {
public:
    enum States { Start, End, Playing, Menu };
    [[nodiscard]] States run(Window &wnd, Graphics &gfx);
    virtual void update(Window &wnd);
    virtual void draw(Graphics &gfx);
    virtual void init();
    virtual ~GameState() = default;
private:
    [[nodiscard]] virtual States runState(Window &wnd, Graphics &gfx) = 0;
    virtual void updateState(Window &wnd) = 0;
    virtual void drawState(Graphics &gfx) = 0;
    virtual void initState() = 0;
};
