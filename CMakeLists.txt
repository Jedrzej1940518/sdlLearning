cmake_minimum_required(VERSION 3.0)

project(starships VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(SOURCES
    src/main.cpp
    src/gameState.cpp
    src/utils.cpp
    src/soundManager.cpp
    src/physics/physics.cpp
    src/physics/body.cpp
    src/physics/collisionModel.cpp
    src/rendering/background.cpp
    src/rendering/object.cpp
    src/rendering/collisionObject.cpp
    src/rendering/button.cpp
    src/levels/menu.cpp
    src/levels/arena.cpp
    #src/levels/gameOver.cpp
    src/ships/aiShip.cpp
    src/ships/tactic.cpp
    src/ships/ship.cpp
    src/ships/weapon.cpp
    src/ships/projectile.cpp
    src/ships/playerShip.cpp
)
add_executable(starships ${SOURCES})
add_compile_definitions(_USE_MATH_DEFINES)

target_compile_options(starships PRIVATE)

find_package(SFML COMPONENTS graphics audio REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-audio)

set_target_properties(starships PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin/)

target_include_directories(starships PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/)