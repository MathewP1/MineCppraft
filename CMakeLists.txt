cmake_minimum_required(VERSION 3.23)
project(MineCppraft
        VERSION 0.1
        DESCRIPTION "Template for cross-platform OpenGL cmake project"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Include third-party libs
add_subdirectory(third_party/glew)
add_subdirectory(third_party/glfw)
add_subdirectory(third_party/stb_image)
add_subdirectory(third_party/glm)
add_subdirectory(third_party/imgui/imgui)

# Generate config.h
set(RESOURCE_PATH "${PROJECT_SOURCE_DIR}/res/")
configure_file(src/config.h.in src/config.h)

set(SOURCE_FILES
        "src/gl_util.h" "src/gl_util.cpp"
        src/game/game_loop.h src/game/game_loop.cpp
        src/renderer/cube_renderer.h src/renderer/cube_renderer.cpp
        src/game/camera.h src/game/camera.cpp
        src/renderer/chunk_renderer_naive.h src/renderer/chunk_renderer_naive.cpp
        src/renderer/texture_atlas.h src/renderer/texture_atlas.cpp
        src/game/key_input.h src/game/key_input.cpp src/game/mouse_input.h src/game/mouse_input.cpp)

add_executable(MineCppraft src/main.cpp ${SOURCE_FILES})

target_include_directories(MineCppraft
        PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/src"
        PRIVATE "src"
        PRIVATE "third_party/stb_image"
        PRIVATE "third_party/imgui")

target_link_libraries(MineCppraft
        PRIVATE glfw
        PRIVATE libglew_static
        glm
        stb_image
        imgui)