find_package(SDL2 REQUIRED)

add_executable (game test.cpp)

# INCLUDE(FindPkgConfig)
# PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
# INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})
# TARGET_LINK_LIBRARIES(game ${SDL2_LIBRARIES})

target_include_directories(game SYSTEM PRIVATE "${SDL2_INCLUDE_DIR}")
target_link_libraries(game "${SDL2_LIBRARY}")