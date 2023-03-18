set(SOURCES
    main.cpp
    gameState.cpp
    sdl.cpp
    utils.cpp
    physics/physics.cpp
    physics/body.cpp
    physics/collisionModel.cpp
    rendering/button.cpp
    rendering/collisionObject.cpp
    rendering/object.cpp
    levels/menu.cpp
    levels/arena.cpp
)

add_executable(starships ${SOURCES})

target_compile_options(starships PRIVATE -Wall -Wextra -pedantic -Werror)

target_link_libraries(starships PRIVATE SDL2 SDL2_image SDL2_ttf)

set_target_properties(starships PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
