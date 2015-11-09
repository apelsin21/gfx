set(SOURCES
    ${SOURCES}

	#core	
    ${CMAKE_CURRENT_SOURCE_DIR}/core/sdl2_window.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/sdl2_keyboard.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/sdl2_mouse.cpp

    #gfx
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/texture.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/texture_loader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/shader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/font.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/gfx/mesh.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/mesh_loader.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/gfx/shader_uniforms.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/gfx/batch.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/framebuffer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/gfx/renderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/shader.cpp

	#game
    ${CMAKE_CURRENT_SOURCE_DIR}/game/game.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/game/player.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/game/marching_cubes.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/game/world.cpp

	#sound
	${CMAKE_CURRENT_SOURCE_DIR}/sound/sound_player.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/sound/sound.cpp

	#net
	${CMAKE_CURRENT_SOURCE_DIR}/net/server.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/net/client.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/net/packet.cpp

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
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/texture_loader.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/shader.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/font.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/mesh.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/mesh_loader.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/vertex_format.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/framebuffer.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/gfx/renderer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/shader.hpp

	#game
    ${CMAKE_CURRENT_SOURCE_DIR}/game/game.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/game/entity.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/game/marching_cubes.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/game/world.hpp

	#sound
	${CMAKE_CURRENT_SOURCE_DIR}/sound/sound_player.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/sound/sound.hpp

	#net
	${CMAKE_CURRENT_SOURCE_DIR}/net/server.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/net/client.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/net/packet.hpp

    PARENT_SCOPE
)
