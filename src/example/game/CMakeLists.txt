find_package(SDL2 REQUIRED)

include_directories(deps)

add_executable (main
    main.cpp
    deps/Game.cpp
    deps/Game.h
)

target_link_libraries(main ${CMAKE_CURRENT_SOURCE_DIR}/deps)

target_include_directories(main SYSTEM PRIVATE "${SDL2_INCLUDE_DIR}")
target_link_libraries(main "${SDL2_LIBRARY}")
