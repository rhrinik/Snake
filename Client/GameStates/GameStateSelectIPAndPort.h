#pragma once
#include <memory>
#include <utility>
#include "GameState.h"
#include "GameStateMenu.h"
#include <cctype>
#include "../Display/Input.h"
#include "../Server.h"

class GameStateSelectIPAndPort : public GameState {
    [[nodiscard]] States runState(States previous) override;
    States updateState() override;
    void drawState() override;
    void initState() override;
    std::shared_ptr<GameStateMenu> menu;
    Server &server;
    Input inputIp;
    Input inputPort;
    Text promptIp;
    Text promptPort;
    Font font;
    int numberPos{0};
    std::vector<int> numberCounts;
    bool ipSelected{false};
    bool input{false};
public:
    GameStateSelectIPAndPort(Window &wnd, Graphics &gfx, std::shared_ptr<GameStateMenu> menu, Server& server)
        : GameState(wnd, gfx), menu(std::move(menu)), server(server), numberCounts(4,0) {}
    void onKeyEnter() override;
    void onBackSpace() override;
    void onTextEntered(char c) override;
};
