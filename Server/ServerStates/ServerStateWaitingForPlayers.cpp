#include "ServerStateWaitingForPlayers.h"

ServerState::States ServerStateWaitingForPlayers::runState(ServerState::States previous) {
    return Start;
}

ServerState::States ServerStateWaitingForPlayers::updateState() {
    return Start;
}

void ServerStateWaitingForPlayers::initState() {

}
