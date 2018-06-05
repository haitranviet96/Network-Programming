cmake_minimum_required(VERSION 3.10)
project(new C)

set(CMAKE_C_STANDARD 99)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(client
        main.c
        Battle.h
        Battle.c
        Cruiser.h
        Cruiser.c
        Draw.h
        Draw.c
        Editor.h
        Editor.c
        Login.h
        Login.c
        Number.h
        Number.c
        ship.h
        ship.c
        specialbox.h
        specialbox.c
        States.h
        States.c
        submarine.h
        submarine.c
        Utils.h
        Utils.c
        Constants.h
        network.c
        network.h
        overall_net.c
        overall_net.h
        Challenge.c
        Challenge.h
        battleship.c
        battleship.h)

add_executable(server
        ../server/server.c
        ../server/server.h)

target_link_libraries(client ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES} SDL2_ttf SDL2_image)
TARGET_LINK_LIBRARIES(server pthread)