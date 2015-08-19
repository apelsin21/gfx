set(SOURCES
    ${SOURCES}

	#core	
    ${CMAKE_CURRENT_SOURCE_DIR}/core/sdl2_window.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/sdl2_keyboard.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/sdl2_mouse.cpp

    #gfx
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/texture.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/shader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/font.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/gfx/gl_texture.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/gl_shader.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/gfx/gl_vertex_buffer.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/sprite_batch.cpp

	#game
    ${CMAKE_CURRENT_SOURCE_DIR}/game/game.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/game/player.cpp

	#sound
	${CMAKE_CURRENT_SOURCE_DIR}/sound/sound_player.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/sound/sound.cpp

    PARENT_SCOPE
)
set(HEADERS
   	${HEADERS}
	
    #core	
    ${CMAKE_CURRENT_SOURCE_DIR}/core/window.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/sdl2_window.hpp
    
    ${CMAKE_CURRENT_SOURCE_DIR}/core/keyboard.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/sdl2_keyboard.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/keyboard_keys.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/core/mouse.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/sdl2_mouse.hpp

	#gfx
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/texture.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/shader.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/font.hpp

	${CMAKE_CURRENT_SOURCE_DIR}/gfx/gl_texture.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/gl_shader.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/gfx/gl_vertex_buffer.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/sprite_batch.hpp

	#game
    ${CMAKE_CURRENT_SOURCE_DIR}/game/game.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/game/entity.hpp

	#sound
	${CMAKE_CURRENT_SOURCE_DIR}/sound/sound_player.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/sound/sound.hpp

    PARENT_SCOPE
)
