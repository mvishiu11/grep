cmake_minimum_required(VERSION 3.13)

project(grep-project)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20) # Enable the C++20 standard
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Source files
file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

# Add the executable
add_executable(grep_exe ${SOURCE_FILES})

# Optional: Set the output directory for the executable
set_target_properties(grep_exe PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)