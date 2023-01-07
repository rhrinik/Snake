#pragma once
#include <memory>
#include "GameState.h"
#include "GameStateMenu.h"
#include "GameStateSelectIPAndPort.h"
#include "../../Shared/Utility/Stopwatch.h"

class GameStateTryToConnect : public GameState {
    [[nodiscard]] States runState(States previous) override;
    States updateState() override;
    void drawState() override;
    void initState() override;
    std::shared_ptr<GameStateSelectIPAndPort> menu;
    Server &server;
    Text connectionStatusText;
    Font font;
    bool input{false};
    bool initPass{false};
    Stopwatch tryConnectFor;
public:
    GameStateTryToConnect(Window &wnd, Graphics &gfx, std::shared_ptr<GameStateSelectIPAndPort> menu, Server& server)
            : GameState(wnd, gfx), menu(std::move(menu)), server(server) {}
    void restart();
};
