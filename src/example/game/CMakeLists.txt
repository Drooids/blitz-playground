include_directories(deps)

add_executable (main
    main.cpp
    deps/Game.cpp
    deps/Game.h
    ${SDL2_INCLUDE_DIR}
    ${SDL2_IMAGE_INCLUDE_DIR}
)

include_directories(
    ${SDL2_INCLUDE_DIR}
    ${SDL2_IMAGE_INCLUDE_DIR}
	"deps"
)

target_link_libraries(main
    ${SDL2_LIBRARY}
    ${SDL2_IMAGE_LIBRARY}
)

IF(WIN32)
	target_link_libraries(main "${SDL2_MAIN_LIBRARY}")
	target_link_libraries(main "${SDL2_TEST_LIBRARY}")
ENDIF()

add_custom_command(TARGET main PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
      ${CMAKE_CURRENT_SOURCE_DIR}/assets
      $<TARGET_FILE_DIR:main>/assets)

IF(WIN32)
    # SDL
    add_custom_command(TARGET game PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${SDL2_DLLS}
        $<TARGET_FILE_DIR:game>)

    # SDL_image
    add_custom_command(TARGET game PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${SDL2_IMAGE_DLLS}
        $<TARGET_FILE_DIR:game>)
ENDIF()
