add_executable (game
	test.cpp
	${SDL2_INCLUDE_DIR}
	${SDL2_IMAGE_INCLUDE_DIR}
)

include_directories(game
	${SDL2_INCLUDE_DIR}
	${SDL2_IMAGE_INCLUDE_DIR}
)
target_link_libraries(game
	${SDL2_LIBRARY}
	${SDL2_IMAGE_LIBRARY}
)
IF(WIN32)
	target_link_libraries(game "${SDL2_MAIN_LIBRARY}")
	target_link_libraries(game "${SDL2_TEST_LIBRARY}")
ENDIF()

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
