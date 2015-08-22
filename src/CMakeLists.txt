

set(SOURCE_FILES main.cpp Surface.cpp Surface.h renderer.cpp renderer.h game.cpp game.h Surface.cpp Surface.h surface.cpp surface.h)
add_executable(ld33_monster ${SOURCE_FILES})

target_link_libraries(ld33_monster SDL2Main SDL2)

