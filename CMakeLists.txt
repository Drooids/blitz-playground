cmake_minimum_required(VERSION 2.8)

set(CMAKE_VERBOSE_MAKEFILE OFF)

project(blitz-playground)

# Hardware System info

IF (${CMAKE_SYSTEM_PROCESSOR} MATCHES i386|i586|i686)
    set(BIT_MODE "64bit")
ELSE()
    set(BIT_MODE "64bit")
ENDIF()

# OS

set(OS "win")

IF(NOT WINDOWS)
    IF("${CMAKE_SYSTEM}" MATCHES "Linux")
        set(OS "linux")
    ENDIF()
ENDIF()

# Print message

message("-- CMAKE_SYSTEM_INFO_FILE: ${CMAKE_SYSTEM_INFO_FILE}")
message("-- CMAKE_SYSTEM_NAME:      ${CMAKE_SYSTEM_NAME}")
message("-- CMAKE_SYSTEM_PROCESSOR: ${CMAKE_SYSTEM_PROCESSOR}")
message("-- CMAKE_SYSTEM:           ${CMAKE_SYSTEM}")
message("-- ARCHITECTURE:           ${BIT_MODE}")
message("-- OS:                     ${OS}")
message("-- SDL2: ${SDL2}")

# Development/Production
# TODO Somehow we need to pass this value as an argument to cmake command
set(DEBUG_MODE "release")

# Useful cmake files
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE STRING "Root dir")#

set(CP_CMAKE_DIR ${PROJECT_SOURCE_DIR}/cmake)

include(cotire)
include(${CP_CMAKE_DIR}/macros.cmake)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

LINK_DIRECTORIES(${CMAKE_BINARY_DIR}/lib)

add_subdirectory(dependencies)

set(DEPENDENCIES "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/platform")

IF(NOT WINDOWS)
    IF("${CMAKE_SYSTEM}" MATCHES "Linux")
        set(SDL2_INCLUDE_DIR "${DEPENDENCIES}/include/SDL")
        set(SDL2_LIBRARY "${DEPENDENCIES}/${BIT_MODE}/${OS}/SDL/lib/${DEBUG_MODE}/libSDL2.so")

        message("-- SDL2_INCLUDE_DIR: ${SDL2_INCLUDE_DIR}")
        message("-- SDL2_LIBRARY: ${SDL2_LIBRARY}")

        set(SDL2_IMAGE_INCLUDE_DIR "${DEPENDENCIES}/include/SDL_image")
        set(SDL2_IMAGE_LIBRARY "${DEPENDENCIES}/${BIT_MODE}/${OS}/SDL_image/lib/${DEBUG_MODE}/libSDL2_image.so")

        message("-- SDL2_IMAGE_INCLUDE_DIR: ${SDL2_IMAGE_INCLUDE_DIR}")
        message("-- SDL2_IMAGE_LIBRARY: ${SDL2_IMAGE_LIBRARY}")
    ENDIF()
ENDIF()

IF(WIN32)
    # Win goes here...
ENDIF()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -std=c++1y")

find_package(OpenGL REQUIRED)

set(BLITZ_LIBS
    ${OPENGL_LIBRARY}
    ${SDL2_LIBRARY}
    ${SDL2_IMAGE_LIBRARY}
)

set(BLITZ_INCLUDES
    ${SDL2_INCLUDE_DIR}
    ${SDL2_IMAGE_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/
)

include_directories(${BLITZ_INCLUDES})

add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/src )
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT game)
