add_executable (game test.cpp)

include_directories(game "${SDL2_INCLUDE_DIR}")
target_link_libraries(game "${SDL2_LIBRARY}")
