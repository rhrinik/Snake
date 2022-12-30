#pragma once
#include "Graphics.h"
#include "KeyPresses.h"

class GameState : public KeyPresses {
public:
    GameState(Window &wnd, Graphics &gfx) : wnd(wnd), gfx(gfx) {}
    enum States { Start, End, Playing, Menu };
    [[nodiscard]] States run(States previous);
    virtual void update();
    virtual void draw();
    virtual void init();
private:
    [[nodiscard]] virtual States runState(States previous) = 0;
    virtual void updateState() = 0;
    virtual void drawState() = 0;
    virtual void initState() = 0;
protected:
    Window &wnd;
    Graphics &gfx;
};
