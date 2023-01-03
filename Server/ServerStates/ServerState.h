#pragma once

class ServerState {
public:
    ServerState() : nextState(WaitingForPlayers) {}
    enum States { WaitingForPlayers, PlayingGame, Start, End };
    [[nodiscard]] States run(States previous);
    virtual States update();
    virtual void init();
private:
    [[nodiscard]] virtual States runState(States previous) = 0;
    virtual States updateState() = 0;
    virtual void initState() = 0;
protected:
    States nextState;
};
