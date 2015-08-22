

set(SOURCE_FILES
        main.cpp
        renderer.cpp renderer.h
        game.cpp game.h
        surface.cpp surface.h text.cpp text.h font.cpp font.h colour.cpp colour.h tile.cpp tile.h)

add_executable(ld33_monster ${SOURCE_FILES})

target_link_libraries(ld33_monster SDL2Main SDL2)

