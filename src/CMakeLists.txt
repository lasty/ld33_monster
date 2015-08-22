

set(SOURCE_FILES main.cpp surface.cpp surface.h renderer.cpp renderer.h game.cpp game.h)
add_executable(ld33_monster ${SOURCE_FILES})

target_link_libraries(ld33_monster SDL2Main SDL2)

