set(SOURCES
    ${SOURCES}

	#core	
    ${CMAKE_CURRENT_SOURCE_DIR}/core/sdl2_window.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/sdl2_keyboard.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/sdl2_mouse.cpp

    #gfx
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/texture.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/font.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/shader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/sprite_batch.cpp

	#lua
    ${CMAKE_CURRENT_SOURCE_DIR}/lua/lua_environment.cpp
	
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
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/font.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/shader.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/sprite_batch.hpp

	#lua
    ${CMAKE_CURRENT_SOURCE_DIR}/lua/lua_environment.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/lua/utils.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/lua/window_binds.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/lua/vec2_binds.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/lua/keyboard_binds.hpp


    PARENT_SCOPE
)
