cmake_minimum_required(VERSION 3.25)
project(RocketBuilder)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find dependencies
find_package(SFML 3.0.1 REQUIRED COMPONENTS Graphics Window System)
find_package(imgui REQUIRED)
find_package(imgui-sfml REQUIRED)
find_package(box2d REQUIRED)

# Executable
add_executable(Rocket src/main.cpp)

# Link libraries
target_link_libraries(Rocket PRIVATE 
    SFML::Graphics 
    SFML::Window 
    SFML::System 
    imgui::imgui 
    ImGui-SFML::ImGui-SFML 
    box2d::box2d
)

# Output directory and Asset handling
set_target_properties(Rocket PROPERTIES 
    OUTPUT_NAME "Rocket"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)
