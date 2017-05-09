find_package(SDL2 REQUIRED)

add_executable (game test.cpp)

target_include_directories(game SYSTEM PRIVATE "${SDL2_INCLUDE_DIR}")
target_link_libraries(game "${SDL2_LIBRARY}")
