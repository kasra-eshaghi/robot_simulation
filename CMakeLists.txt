cmake_minimum_required(VERSION 3.10)
project(robot_simulation)
set(CMAKE_CXX_STANDARD 17)

# include directories
include_directories(${CMAKE_SOURCE_DIR}/include)


# Add external packages
find_package(yaml-cpp REQUIRED)

# Add internal packages
add_library(problem_description libs/problem_description.cpp) 
target_link_libraries(problem_description yaml-cpp)

# Create executable
add_executable(read_config src/read_config.cpp)

# Link libraries
target_link_libraries(read_config problem_description)

# add_executable(hello_world src/hello_world.cpp)
# add_executable(give_commands src/give_commands.cpp)