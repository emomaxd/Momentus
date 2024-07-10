cmake_minimum_required(VERSION 3.10)
project(Momentus-App)

set(CMAKE_CXX_STANDARD 17)

# Include the Engine directory
add_subdirectory(Momentus)
add_subdirectory(Examples)

# Set Engine as the startup project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Examples)

# Remove ALL_BUILD and ZERO_CHECK targets
set(CMAKE_SUPPRESS_REGENERATION true)