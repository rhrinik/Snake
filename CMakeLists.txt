cmake_minimum_required(VERSION 3.23)
project(hadik)

set(CMAKE_CXX_STANDARD 23)

add_executable(hadik main.cpp Application.cpp Application.h Graphics.cpp Graphics.h Game.cpp Game.h Stopwatch.cpp Stopwatch.h GameState.cpp GameState.h GameStatePlaying.cpp GameStatePlaying.h GameStateDummy.cpp GameStateDummy.h)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "../SFML-2.5.1/lib/cmake/SFML")
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories("../SFML-2.5.1/include")
target_link_libraries(hadik sfml-system sfml-window sfml-graphics sfml-audio sfml-network)