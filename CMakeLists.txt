cmake_minimum_required(VERSION 3.26)
project(SimplePlatformer)

set(CMAKE_CXX_STANDARD 17)

add_executable(SimplePlatformer main.cpp
        src/rendering/shader_program.cpp
        src/rendering/shader_program.h
        src/resources/resource_manager.cpp
        src/resources/resource_manager.h
        src/resources/image.cpp
        src/resources/image.h
        src/gui.cpp
        src/gui.h
        src/rendering/texture.cpp
        src/rendering/texture.h
        src/game.cpp
        src/game.h
        src/lib/stb_definition.cpp
        src/logger.cpp
        src/logger.h
        src/rendering/sprite_renderer.h
        src/rendering/sprite_renderer.cpp
        src/map/game_object.h
        src/fileio.cpp
        src/map/tiles.cpp
        src/map/game_map.cpp
        src/map/player.h
        src/map/player.cpp
        src/map/game_object.cpp
)


add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(jsoncpp REQUIRED)

target_link_libraries(${PROJECT_NAME} glfw GLEW::GLEW OpenGL::GL jsoncpp_lib)
