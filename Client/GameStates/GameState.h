#pragma once
#include "../Display/Graphics.h"
#include "../Utility/KeyPresses.h"

class GameState : public KeyPresses {
public:
    GameState(Window &wnd, Graphics &gfx) : wnd(wnd), gfx(gfx), nextState(End) {
        wnd.registerObject(*this);
    }
    enum States { Start, End, Playing, Menu, Lose, Win };
    [[nodiscard]] States run(States previous);
    States update();
    void draw();
    void init();
private:
    [[nodiscard]] virtual States runState(States previous) = 0;
    virtual States updateState() = 0;
    virtual void drawState() = 0;
    virtual void initState() = 0;
protected:
    Window &wnd;
    Graphics &gfx;
    States nextState;
};
