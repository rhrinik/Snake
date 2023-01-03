#include "ServerStatePlayingGame.h"

ServerState::States ServerStatePlayingGame::runState(ServerState::States previous) {
    return Start;
}

ServerState::States ServerStatePlayingGame::updateState() {
    return Start;
}

void ServerStatePlayingGame::initState() {

}
