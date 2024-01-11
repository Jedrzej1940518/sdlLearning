set(SOURCES
    main.cpp
    gameState.cpp
    sdl.cpp
    utils.cpp
    soundManager.cpp
    physics/physics.cpp
    physics/body.cpp
    physics/collisionModel.cpp
    rendering/collisionObject.cpp
    rendering/object.cpp
    rendering/text.cpp
    rendering/menu_ui/button.cpp
    levels/menu.cpp
    levels/arena.cpp
    levels/gameOver.cpp
    ships/ship.cpp
    ships/hostileShip.cpp
    ships/projectile.cpp
)

add_executable(starships ${SOURCES})

target_compile_options(starships PRIVATE -Wall -Wextra -pedantic -Werror)

target_link_libraries(starships PRIVATE SDL2 SDL2_image SDL2_ttf SDL2_mixer SDL2_gfx)

set_target_properties(starships PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

target_include_directories(starships PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
