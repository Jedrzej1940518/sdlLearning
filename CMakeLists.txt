cmake_minimum_required(VERSION 3.0)

project(starships VERSION 1.0)


set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(SOURCES
    src/main.cpp
    src/gameState.cpp
    src/mySdl.cpp
    src/utils.cpp
    src/soundManager.cpp
    src/physics/physics.cpp
    src/physics/body.cpp
    src/physics/collisionModel.cpp
    src/rendering/collisionObject.cpp
    src/rendering/object.cpp
    src/rendering/text.cpp
    src/rendering/menu_ui/button.cpp
    src/levels/menu.cpp
    src/levels/arena.cpp
    src/levels/gameOver.cpp
    src/ships/ship.cpp
    src/ships/hostileShip.cpp
    src/ships/projectile.cpp
)

add_executable(starships ${SOURCES})

target_compile_options(starships PRIVATE)

find_package(SDL2 REQUIRED CONFIG)
find_package(SDL2_image REQUIRED CONFIG)
find_package(SDL2_ttf REQUIRED CONFIG)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL2_image::SDL2_image-static)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2_ttf::SDL2_ttf)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2main SDL2::SDL2-static)

#target_link_libraries(starships PRIVATE ${CONAN_LIBS})#SDL2 SDL2_image SDL2_ttf SDL2_mixer SDL2_gfx)

set_target_properties(starships PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(starships PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/)
message(STATUS ${CMAKE_CURRENT_SOURCE_DIR}/src/)