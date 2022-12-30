#pragma once
#include "Graphics.h"

class GameState {
public:
    GameState(Window &wnd, Graphics &gfx) : wnd(wnd), gfx(gfx) {}
    enum States { Start, End, Playing, Menu };
    [[nodiscard]] States run();
    virtual void update();
    virtual void draw();
    virtual void init();
    virtual ~GameState() = default;
private:
    [[nodiscard]] virtual States runState() = 0;
    virtual void updateState() = 0;
    virtual void drawState() = 0;
    virtual void initState() = 0;
protected:
    Window &wnd;
    Graphics &gfx;
};
