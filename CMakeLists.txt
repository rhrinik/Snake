cmake_minimum_required(VERSION 3.23)
project(hadik)

set(CMAKE_CXX_STANDARD 23)

add_executable(snakeClient Client/main.cpp Client/Application.cpp Client/Application.h Client/Graphics.cpp Client/Graphics.h Client/Game.cpp Client/Game.h Client/Stopwatch.cpp Client/Stopwatch.h Client/GameState.cpp Client/GameState.h Client/GameStatePlaying.cpp Client/GameStatePlaying.h Client/GameStateDummy.cpp Client/GameStateDummy.h Client/Snake.cpp Client/Snake.h Client/Color.cpp Client/Color.h Client/GameStateMenu.cpp Client/GameStateMenu.h Client/Image.cpp Client/Image.h Client/Text.cpp Client/Text.h Client/Food.cpp Client/Food.h Client/Utilities.h Client/Window.cpp Client/Window.h Client/Font.cpp Client/Font.h)
add_executable(snakeServer Server/main.cpp Server/Application.cpp Server/Application.h Server/Game.cpp Server/Game.h)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "../SFML-2.5.1/lib/cmake/SFML")
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories("../SFML-2.5.1/include")
target_link_libraries(snakeClient sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
target_link_libraries(snakeServer sfml-system sfml-window sfml-graphics sfml-audio sfml-network)