find_package(SDL2 REQUIRED)

include_directories(deps)

add_executable (main
    main.cpp
    deps/Game.cpp
    deps/Game.h
)

target_link_libraries(main ${CMAKE_CURRENT_SOURCE_DIR}/deps)

include_directories(main
    ${SDL2_INCLUDE_DIR}
    ${SDL2_IMAGE_INCLUDE_DIR}
)

target_link_libraries(main
    ${SDL2_LIBRARY}
    ${SDL2_IMAGE_LIBRARIES}
)

add_custom_command(TARGET main PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
      ${CMAKE_CURRENT_SOURCE_DIR}/assets
      $<TARGET_FILE_DIR:main>/assets)
