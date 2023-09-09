cmake_minimum_required(VERSION 3.26)
project(SimplePlatformer)

set(CMAKE_CXX_STANDARD 17)

add_executable(SimplePlatformer main.cpp
        src/shader_program.cpp
        src/shader_program.h
        src/resource_manager.cpp
        src/resource_manager.h
        src/image.cpp
        src/image.h
        src/gui.cpp
        src/gui.h
        src/texture.cpp
        src/texture.h
        src/game.cpp
        src/game.h
        src/stb_definition.cpp
        src/logger.cpp
        src/logger.h
)


add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

target_link_libraries(${PROJECT_NAME} glfw GLEW::GLEW OpenGL::GL)