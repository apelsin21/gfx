set(SOURCES
    ${SOURCES}

	#core	

    #gfx
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/texture.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/font.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/graphics_device.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/context_settings.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/shader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/shader_program.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/sprite_batch.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/gl_object.cpp
    
    #net
    ${CMAKE_CURRENT_SOURCE_DIR}/net/address.cpp
	
    PARENT_SCOPE
)
set(HEADERS
   	${HEADERS}
	
    #core	
    
    ${CMAKE_CURRENT_SOURCE_DIR}/core/keyboard_keys.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/mouse_keys.hpp

	#gfx
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/texture.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/font.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/color.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/graphics_device.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/graphics_device_event.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/context_settings.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/shader.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/shader_program.hpp


    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/sprite_batch.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gfx/gl_object.hpp

    #net
    ${CMAKE_CURRENT_SOURCE_DIR}/net/client.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/net/server.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/net/address.hpp

    PARENT_SCOPE
)
