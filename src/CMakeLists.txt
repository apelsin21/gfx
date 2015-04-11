set(SOURCES
    ${SOURCES}

	#core	
    ${CMAKE_CURRENT_SOURCE_DIR}/core/sdl2_window.cpp

    #gfx
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/free_image_texture.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/free_type_font.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/opengl_renderer.cpp
    
    #net
    ${CMAKE_CURRENT_SOURCE_DIR}/net/address.cpp
	
    PARENT_SCOPE
)
set(HEADERS
   	${HEADERS}
	
    #core	
    ${CMAKE_CURRENT_SOURCE_DIR}/core/window.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/sdl2_window.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/window_event.hpp
    
    ${CMAKE_CURRENT_SOURCE_DIR}/core/keyboard_keys.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/mouse_keys.hpp

	#gfx
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/free_image_texture.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/free_type_font.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/texture.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/font.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/renderer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/opengl_renderer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/color.hpp

    #net
    ${CMAKE_CURRENT_SOURCE_DIR}/net/client.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/net/server.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/net/address.hpp

    PARENT_SCOPE
)
