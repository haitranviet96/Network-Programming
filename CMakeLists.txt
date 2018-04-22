cmake_minimum_required(VERSION 3.10)
project(new C)

set(CMAKE_C_STANDARD 99)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(new
        main.c
        Battle.h
        Battle.c
        Cruiser.h
        Cruiser.c
        Draw.h
        Draw.c
        Editor.h
        Editor.c
        handlemouseEditor.h
        handlemouseEditor.c
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
        Constants.h)

target_link_libraries(new ${SDL2_LIBRARIES})