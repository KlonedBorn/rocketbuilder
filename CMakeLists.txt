cmake_minimum_required(VERSION 3.25)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
project(RocketBuilder)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# SFML 3.0.0
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
)

# ImGui v1.91.8 (< 1.92)
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.91.8
)

# imgui-sfml v3.0 (compatible with SFML 3)
FetchContent_Declare(
    imgui-sfml
    GIT_REPOSITORY https://github.com/SFML/imgui-sfml.git
    GIT_TAG v3.0
)

# Populate SFML and ImGui first
FetchContent_MakeAvailable(SFML imgui)

# Set IMGUI_DIR so imgui-sfml can find it
set(IMGUI_DIR ${imgui_SOURCE_DIR} CACHE PATH "Path to ImGui")

# Since we are using FetchContent for SFML, tell imgui-sfml not to call find_package(SFML)
set(IMGUI_SFML_FIND_SFML OFF CACHE BOOL "Don't find SFML" FORCE)

# Populate imgui-sfml
FetchContent_MakeAvailable(imgui-sfml)

# Executable
add_executable(Rocket 
    src/main.cpp
    src/Core/Application.hpp
    src/Core/Application.cpp
    src/Graphics/Grid.hpp
    src/Graphics/Grid.cpp
    src/Scene/Scene.hpp
    src/Scene/SceneManager.hpp
    src/Scene/SceneManager.cpp)

# Link libraries
# Note: imgui-sfml v3.0 defines ImGui-SFML::ImGui-SFML
# It also handles linking to SFML and ImGui
target_link_libraries(Rocket PRIVATE 
    SFML::Graphics 
    SFML::Window 
    SFML::System 
    ImGui-SFML::ImGui-SFML
)

# Output directory
set_target_properties(Rocket PROPERTIES 
    OUTPUT_NAME "Rocket"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)
