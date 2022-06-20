cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
set(VERSION 0.1.1)
project(doyourthing VERSION ${VERSION} LANGUAGES CXX)

set(TARGET_NAME doyourthing) # Target name
set(CMAKE_CXX_STANDARD 20) # C++ Standard

# Internal library
add_library(libdyt STATIC
	src/manager.cc
	src/action.cc
	src/section.cc
	src/spinner.cc
	src/colors.cc
	src/settings.cc
)

# Internal include directory
include_directories(include)

# Main executable
add_executable(${TARGET_NAME} src/targets/doyourthing.cc)

# Link internal library to main executable
target_link_libraries(${TARGET_NAME} PRIVATE libdyt)

# json - Lightweight library for parsing json data - https://github.com/nlohmann/json.git
add_subdirectory(extern/json)
add_subdirectory(extern/fmt)
target_include_directories(${TARGET_NAME} PRIVATE json)
target_link_libraries(${TARGET_NAME} PRIVATE nlohmann_json::nlohmann_json fmt::fmt)

# CPack stuff
set(CPACK_GENERATOR "RPM")

set(CPACK_RPM_USER_BINARY_SPECFILE "${CMAKE_CURRENT_SOURCE_DIR}/release/DoYourThing.spec")
set(CPACK_PACKAGE_NAME "DoYourThing")
set(CPACK_PACKAGE_SUMMARY "A small installer/configurator for your linux setups.")

set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/release/DESCRIPTION.txt")
set(CPACK_PACKAGE_VERSION ${VERSION})
set(CPACK_PACKAGE_RELEASE 1)
set(CPACK_PACKAGE_LICENSE "MIT")
set(CPACK_PACKAGE_GROUP "Applications/Productivity/Other")
set(CPACK_PACKAGE_CONTACT "Milovan Gudelj <i.like.martians@gmail.com>")
set(CPACK_PACKAGE_VENDOR "i.like.martians Inc.")
set(CMAKE_PROJECT_HOMEPAGE_URL "https://github.com/milovangudelj/doyourthing")

set(CPACK_PACKAGE_BUILD_REQUIRES "cmake >= 3.15")

set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CPACK_PACKAGE_RELEASE}.${CMAKE_SYSTEM_PROCESSOR}")
set(CPACK_INSTALL_PREFIX "/usr/local/bin")
set(CPACK_PACKAGING_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})

set(CPACK_RPM_CHANGELOG_FILE "${CMAKE_CURRENT_SOURCE_DIR}/release/CHANGELOG.txt")
file(READ ${CPACK_RPM_CHANGELOG_FILE} CPACK_RPM_SPEC_CHANGELOG)
install(TARGETS doyourthing RUNTIME DESTINATION bin)

include(CPack)