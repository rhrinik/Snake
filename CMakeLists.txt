cmake_minimum_required(VERSION 3.23)
project(hadik)

set(CMAKE_CXX_STANDARD 23)

add_executable(snakeClient Client/main.cpp Client/Application.cpp Client/Application.h Client/Display/Graphics.cpp Client/Display/Graphics.h Client/Game.cpp Client/Game.h Client/Utility/Stopwatch.cpp Client/Utility/Stopwatch.h Client/GameStates/GameState.cpp Client/GameStates/GameState.h Client/GameStates/GameStatePlaying.cpp Client/GameStates/GameStatePlaying.h Client/GameStates/GameStateDummy.cpp Client/GameStates/GameStateDummy.h Client/GameObjects/Snake.cpp Client/GameObjects/Snake.h Client/Display/Color.cpp Client/Display/Color.h Client/GameStates/GameStateMenu.cpp Client/GameStates/GameStateMenu.h Client/Display/Image.cpp Client/Display/Image.h Client/Display/Text.cpp Client/Display/Text.h Client/GameObjects/Food.cpp Client/GameObjects/Food.h Client/Utility/Utilities.h Client/Display/Window.cpp Client/Display/Window.h Client/Display/Font.cpp Client/Display/Font.h Client/Utility/KeyPresses.cpp Client/Utility/KeyPresses.h Client/Server.cpp Client/Server.h Client/DataToServer.cpp Client/DataToServer.h Client/DataFromServer.cpp Client/DataFromServer.h)
add_executable(snakeServer Server/main.cpp Server/Application.cpp Server/Application.h Server/Game.cpp Server/Game.h Server/Utility/Stopwatch.cpp Server/Utility/Stopwatch.h Server/Utility/Utilities.h Server/GameObjects/Food.h Server/GameObjects/Food.cpp Server/GameObjects/Snake.h Server/GameObjects/Snake.cpp Server/DataToClient.cpp Server/DataToClient.h Server/DataFromClient.cpp Server/DataFromClient.h Server/Client.cpp Server/Client.h)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "../SFML-2.5.1/lib/cmake/SFML")
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories("../SFML-2.5.1/include")
target_link_libraries(snakeClient sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
target_link_libraries(snakeServer sfml-system sfml-window sfml-graphics sfml-audio sfml-network)