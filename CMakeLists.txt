cmake_minimum_required(VERSION 3.10)
project(robot_simulation)
set(CMAKE_CXX_STANDARD 17)

# include directories
include_directories(${CMAKE_SOURCE_DIR}/include)


# Add external packages
find_package(yaml-cpp REQUIRED)
find_package(SFML COMPONENTS graphics REQUIRED)

add_library(world libs/world.cpp)
add_library(robot libs/robot.cpp)
add_library(helper_functions libs/helper_functions.cpp)
add_library(data_types libs/data_types.cpp)
add_library(visualization libs/visualization.cpp)

add_library(planning_module libs/planning_module.cpp)
add_library(localization_module libs/localization_module.cpp)
add_library(behavior_controller libs/behavior_controller.cpp)

target_link_libraries(robot helper_functions data_types)
target_link_libraries(world yaml-cpp robot data_types)
target_link_libraries(visualization sfml-graphics data_types)
target_link_libraries(behavior_controller planning_module localization_module world yaml-cpp)

# Create executable
add_executable(main src/main.cpp)

# Link libraries
target_link_libraries(main yaml-cpp sfml-graphics robot world behavior_controller visualization)

