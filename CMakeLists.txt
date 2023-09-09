cmake_minimum_required(VERSION 3.26)
project(SimplePlatformer)

set(CMAKE_CXX_STANDARD 17)

add_executable(SimplePlatformer main.cpp
        src/rendering/shader_program.cpp
        src/rendering/shader_program.h
        src/rendering/resource_manager.cpp
        src/rendering/resource_manager.h
        src/rendering/image.cpp
        src/rendering/image.h
        src/gui.cpp
        src/gui.h
        src/rendering/texture.cpp
        src/rendering/texture.h
        src/game.cpp
        src/game.h
        src/rendering/stb_definition.cpp
        src/logger.cpp
        src/logger.h
        src/rendering/sprite_renderer.h
        src/rendering/sprite_renderer.cpp
)


add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

target_link_libraries(${PROJECT_NAME} glfw GLEW::GLEW OpenGL::GL)