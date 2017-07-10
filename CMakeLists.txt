cmake_minimum_required(VERSION 2.8)

set(CMAKE_VERBOSE_MAKEFILE OFF)

project(blitz-playground)

# Strange policy stuff
# Solution from: http://answers.ros.org/question/222139/how-to-disable-policy-cmp0045-is-not-set-warnings/

# Supress policy
# https://cmake.org/cmake/help/v3.0/policy/CMP0040.html
# It came from: add_custom_command() below
# cmake_policy(SET CMP0040 OLD)

# Hardware System info

IF (${CMAKE_SYSTEM_PROCESSOR} MATCHES i386|i586|i686)
    set(BIT_MODE "32bit")
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

message("--")
message("-- CMAKE_SYSTEM_INFO_FILE: ${CMAKE_SYSTEM_INFO_FILE}")
message("-- CMAKE_SYSTEM_NAME:      ${CMAKE_SYSTEM_NAME}")
message("-- CMAKE_SYSTEM_PROCESSOR: ${CMAKE_SYSTEM_PROCESSOR}")
message("-- CMAKE_SYSTEM:           ${CMAKE_SYSTEM}")
message("-- ARCHITECTURE:           ${BIT_MODE}")
message("-- OS:                     ${OS}")
message("-- SDL2: ${SDL2}")

message(STATUS "CMAKE_SYSTEM_NAME          = ${CMAKE_SYSTEM_NAME}"         )
message(STATUS "CMAKE_CXX_COMPILER_ID      = ${CMAKE_CXX_COMPILER_ID}"     )
message(STATUS "CMAKE_CXX_COMPILER_VERSION = ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "CMAKE_COMPILER_IS_GNUCXX   = ${CMAKE_COMPILER_IS_GNUCXX}"  )
message("--")

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

IF(NOT WIN32)
    IF("${CMAKE_SYSTEM}" MATCHES "Linux")
        # SDL
        set(SDL2_INCLUDE_DIR "${DEPENDENCIES}/include/SDL")
        set(SDL2_LIBRARY "${DEPENDENCIES}/${BIT_MODE}/${OS}/SDL/lib/${DEBUG_MODE}/libSDL2.so")

        # SDL_image
        set(SDL2_IMAGE_INCLUDE_DIR "${DEPENDENCIES}/include/SDL_image")
        set(SDL2_IMAGE_LIBRARY "${DEPENDENCIES}/${BIT_MODE}/${OS}/SDL_image/lib/${DEBUG_MODE}/libSDL2_image.so")

        # tinyxml2
        set(TINYXML2_INCLUDE_DIR "${DEPENDENCIES}/include/tinyxml2")
        set(TINYXML2_LIBRARY "${DEPENDENCIES}/${BIT_MODE}/${OS}/tinyxml2/lib/${DEBUG_MODE}/libtinyxml2.so")
    ENDIF()
ENDIF()

IF(WIN32)
    # SDL
    set(SDL2_INCLUDE_DIR "${DEPENDENCIES}/include/SDL")
    set(SDL2_LIBRARY "${DEPENDENCIES}/${BIT_MODE}/${OS}/SDL/lib/${DEBUG_MODE}/SDL2.lib")
    set(SDL2_MAIN_LIBRARY "${DEPENDENCIES}/${BIT_MODE}/${OS}/SDL/lib/${DEBUG_MODE}/SDL2main.lib")
    set(SDL2_TEST_LIBRARY "${DEPENDENCIES}/${BIT_MODE}/${OS}/SDL/lib/${DEBUG_MODE}/SDL2test.lib")
    set(SDL2_DLLS "${DEPENDENCIES}/${BIT_MODE}/${OS}/SDL/dll/${DEBUG_MODE}")

    # SDL_image
    set(SDL2_IMAGE_INCLUDE_DIR "${DEPENDENCIES}/include/SDL_image")
    set(SDL2_IMAGE_LIBRARY "${DEPENDENCIES}/${BIT_MODE}/${OS}/SDL_image/lib/${DEBUG_MODE}/SDL2_image.lib")
    set(SDL2_IMAGE_DLLS "${DEPENDENCIES}/${BIT_MODE}/${OS}/SDL_image/dll/${DEBUG_MODE}")

    # tinyxml2
    set(TINYXML2_INCLUDE_DIR "${DEPENDENCIES}/include/tinyxml2")
    set(TINYXML2_LIBRARY "${DEPENDENCIES}/${BIT_MODE}/${OS}/tinyxml2/lib/${DEBUG_MODE}/tinyxml2d.lib")
    set(TINYXML2_DLLS "${DEPENDENCIES}/${BIT_MODE}/${OS}/tinyxml2/dll/${DEBUG_MODE}")

    # Copy .dll files
    # ${CMAKE_BINARY_DIR}/bin

    # SDL
    #add_custom_command(TARGET main PRE_BUILD
    #    COMMAND ${CMAKE_COMMAND} -E copy_directory
    #    ${SDL2_DLLS}
    #    $<TARGET_FILE_DIR:main>)

    # SDL_image
    #add_custom_command(TARGET main PRE_BUILD
    #    COMMAND ${CMAKE_COMMAND} -E copy_directory
    #    ${SDL2_IMAGE_DLLS}
    #    $<TARGET_FILE_DIR:main>)
ENDIF()

message("--")
message("-- SDL2_INCLUDE_DIR: ${SDL2_INCLUDE_DIR}")
message("-- SDL2_LIBRARY: ${SDL2_LIBRARY}")

IF(WIN32)
    message("-- SDL2_MAIN_LIBRARY: ${SDL2_MAIN_LIBRARY}")
    message("-- SDL2_TEST_LIBRARY: ${SDL2_TEST_LIBRARY}")
    message("-- SDL2_DLLS: ${SDL2_DLLS}")
    message("-- SDL2_IMAGE_DLLS: ${SDL2_IMAGE_DLLS}")
    message("-- TINYXML2_DLLS: ${TINYXML2_DLLS}")
ENDIF()

message("-- SDL2_IMAGE_INCLUDE_DIR: ${SDL2_IMAGE_INCLUDE_DIR}")
message("-- SDL2_IMAGE_LIBRARY: ${SDL2_IMAGE_LIBRARY}")

message("-- SDL2_IMAGE_INCLUDE_DIR: ${SDL2_IMAGE_INCLUDE_DIR}")
message("-- SDL2_IMAGE_LIBRARY: ${SDL2_IMAGE_LIBRARY}")

message("-- TINYXML2_INCLUDE_DIR: ${TINYXML2_INCLUDE_DIR}")
message("-- TINYXML2_LIBRARY: ${TINYXML2_LIBRARY}")
message("--")

IF(NOT WIN32)
    # -std=c++14 requires at least gcc 4.9.1
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -std=c++14")
ENDIF()

IF(MSVC)
  # StringPooling: true == /GF  false == /GF-
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /GF")

  # RuntimeLibrary
  # 0 (MultiThreaded) == /MT
  # 1 (MultiThreadedDebug) == /MTd
  # 2 (MultiThreadedDLL) == /MD
  # 3 (MultiThreadedDebugDLL) == /MDd
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")

  # TreatWChar_tAsBuiltInType: true == /Zc:wchar_t  false == /Zc:wchar_t-
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:wchar_t")

  # WarningLevel: /W<level 0 to 4> or /Wall
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3")

  # Detect64BitPortabilityProblems: /Wp64 - Deprecated since VC++ 2010
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Wp64")
endif()

find_package(OpenGL REQUIRED)

set(BLITZ_LIBS
    ${OPENGL_LIBRARY}
    ${SDL2_LIBRARY}
    ${SDL2_IMAGE_LIBRARY}
    ${TINYXML2_LIBRARY}
)

set(BLITZ_INCLUDES
    ${SDL2_INCLUDE_DIR}
    ${SDL2_IMAGE_INCLUDE_DIR}
    ${TINYXML2_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/
)

include_directories(${BLITZ_INCLUDES})

add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/src )
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT game)
