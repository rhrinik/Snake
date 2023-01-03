#include "ServerState.h"

void ServerState::init() {
    initState();
}

ServerState::States ServerState::update() {
    return updateState();
}

ServerState::States ServerState::run(ServerState::States previous) {
    return runState(previous);
}
