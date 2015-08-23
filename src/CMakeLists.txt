

set(SOURCE_FILES
        main.cpp
        renderer.cpp renderer.h
        game.cpp game.h
        surface.cpp surface.h
        text.cpp text.h
        font.cpp font.h
        colour.cpp colour.h
        tile.cpp tile.h
        sprite.cpp sprite.h
        spritesheet.cpp spritesheet.h
        particle.cpp particle.h
        particlesystem.cpp particlesystem.h
        world.cpp world.h
        animatedsprite.cpp
        animatedsprite.h
        gui.cpp gui.h
        camera.cpp camera.h
        entity.cpp entity.h
        components.cpp components.h
        entityfactory.cpp entityfactory.h)

add_executable(ld33_monster ${SOURCE_FILES})

target_link_libraries(ld33_monster SDL2Main SDL2)

