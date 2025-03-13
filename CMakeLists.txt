cmake_minimum_required(VERSION 3.10)
project(robot_simulation)
set(CMAKE_CXX_STANDARD 17)

# include directories
include_directories(${CMAKE_SOURCE_DIR}/include)


# Add external packages
find_package(yaml-cpp REQUIRED)
find_package(SFML COMPONENTS graphics REQUIRED)

# Add internal packages
# add_library(problem_description libs/problem_description.cpp) 
# target_link_libraries(problem_description yaml-cpp)

# add_library(coordinator libs/coordinator.cpp)
add_library(simulator libs/simulator.cpp)
add_library(data_types libs/data_types.cpp)
add_library(robot libs/robot.cpp)

target_link_libraries(simulator data_types)
target_link_libraries(robot data_types)
# add_library(robot libs/robot.cpp)
# target_link_libraries(coordinator yaml-cpp simulator robot)

# Create executable
# add_executable(read_config src/read_config.cpp)
add_executable(main src/main.cpp)

# Link libraries
# target_link_libraries(read_config problem_description)
target_link_libraries(main yaml-cpp sfml-graphics simulator robot)

# add_executable(hello_world src/hello_world.cpp)
# add_executable(give_commands src/give_commands.cpp)