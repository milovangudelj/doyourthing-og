cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
set(VERSION 0.1.1)
project(doyourthing VERSION ${VERSION} LANGUAGES CXX)

set(TARGET_NAME doyourthing) # Target name
set(CMAKE_CXX_STANDARD 17) # C++ Standard

# Internal library
add_library(libdyt STATIC
	src/libdyt.cc
	src/action.cc
	src/section.cc
	src/spinner.cc
)

# Internal include directory
include_directories(include)

# Main executable
add_executable(${TARGET_NAME} src/targets/doyourthing.cc)

# Link internal library to main executable
target_link_libraries(${TARGET_NAME} PRIVATE libdyt)

# json - Lightweight library for parsing json data - https://github.com/nlohmann/json.git
add_subdirectory(extern/json)
target_include_directories(${TARGET_NAME} PRIVATE json)
target_link_libraries(${TARGET_NAME} PRIVATE nlohmann_json::nlohmann_json)