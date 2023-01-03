cmake_minimum_required(VERSION 3.23)
project(hadik)

set(CMAKE_CXX_STANDARD 23)

add_executable(snakeClient Client/main.cpp Client/Application.cpp Client/Application.h Client/Display/Graphics.cpp Client/Display/Graphics.h Client/Game.cpp Client/Game.h Client/GameStates/GameState.cpp Client/GameStates/GameState.h Client/GameStates/GameStatePlaying.cpp Client/GameStates/GameStatePlaying.h Client/GameStates/GameStateDummy.cpp Client/GameStates/GameStateDummy.h Client/GameObjects/Snake.cpp Client/GameObjects/Snake.h Client/Display/Color.cpp Client/Display/Color.h Client/GameStates/GameStateMenu.cpp Client/GameStates/GameStateMenu.h Client/Display/Image.cpp Client/Display/Image.h Client/Display/Text.cpp Client/Display/Text.h Client/GameObjects/Food.cpp Client/GameObjects/Food.h Client/Display/Window.cpp Client/Display/Window.h Client/Display/Font.cpp Client/Display/Font.h Client/Utility/KeyPresses.cpp Client/Utility/KeyPresses.h Client/Server.cpp Client/Server.h Shared/DataFromServer.h Shared/DataFromServer.cpp Shared/DataFromClient.h Shared/DataFromClient.cpp Shared/Utility/Utilities.h Shared/Utility/Stopwatch.h Shared/Utility/Stopwatch.cpp Shared/GameObjects/Snake.h Shared/GameObjects/Snake.cpp Client/GameStates/GameStateLose.cpp Client/GameStates/GameStateLose.h)
add_executable(snakeServer Server/main.cpp Server/Application.cpp Server/Application.h Server/Game.cpp Server/Game.h Shared/DataFromServer.h Shared/DataFromServer.cpp Shared/DataFromClient.cpp Shared/DataFromClient.h Server/Client.cpp Server/Client.h Shared/Utility/Utilities.h Shared/Utility/Stopwatch.h Shared/Utility/Stopwatch.cpp Server/GameObjects/Snake.h Server/GameObjects/Snake.cpp Server/ServerStates/ServerState.cpp Server/ServerStates/ServerState.h)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "../SFML-2.5.1/lib/cmake/SFML")
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories("../SFML-2.5.1/include")
target_link_libraries(snakeClient sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
target_link_libraries(snakeServer sfml-system sfml-window sfml-graphics sfml-audio sfml-network)