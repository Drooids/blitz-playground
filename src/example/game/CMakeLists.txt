find_package(SDL2 REQUIRED)

add_executable (main main.cpp)

# INCLUDE(FindPkgConfig)
# PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
# INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})
# TARGET_LINK_LIBRARIES(main ${SDL2_LIBRARIES})

target_include_directories(main SYSTEM PRIVATE "${SDL2_INCLUDE_DIR}")
target_link_libraries(main "${SDL2_LIBRARY}")