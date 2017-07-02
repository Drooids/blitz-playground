include_directories(deps)

SET(DEPS
	deps/Game.cpp
	deps/Game.h
	deps/LoaderParams.h
	deps/TextureManager.cpp
	deps/TextureManager.h
	deps/Vector2D.cpp
	deps/Vector2D.h
	deps/InputHandler.cpp
	deps/InputHandler.h
	deps/GameObject.cpp
	deps/GameObject.h
	deps/SDLGameObject.cpp
	deps/SDLGameObject.h
	deps/AnimatedGraphic.cpp
	deps/AnimatedGraphic.h
	deps/Player.cpp
	deps/Player.h
	deps/Enemy.cpp
	deps/Enemy.h
	deps/MenuButton.cpp
	deps/MenuButton.h
	deps/GameState.h
	deps/GameStateMachine.cpp
	deps/GameStateMachine.h
	deps/MenuState.cpp
	deps/MenuState.h
	deps/PlayState.cpp
	deps/PlayState.h
	deps/PauseState.h
	deps/PauseState.cpp
	deps/GameOverState.h
	deps/GameOverState.cpp
)

add_executable (main
	main.cpp
	${DEPS}
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
	add_custom_command(TARGET main PRE_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		${SDL2_DLLS}
		$<TARGET_FILE_DIR:main>)

	# SDL_image
	add_custom_command(TARGET main PRE_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		${SDL2_IMAGE_DLLS}
		$<TARGET_FILE_DIR:main>)
ENDIF()
