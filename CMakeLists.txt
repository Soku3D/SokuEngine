cmake_minimum_required( VERSION 3.12)

project ( ENGINE )

SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)

SET(OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})

ADD_DEFINITIONS( -DOUTPUT_PATH=${OUTPUT_PATH})

if (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
  list (APPEND PBRT_CXX_FLAGS "-std=c++17")
endif ()
SET ( ENGINE_CORE_HEADERS
	src/core/engine.h
	src/core/geometry.h
	src/core/geometry.cpp
	src/core/renderer.h
	src/core/renderer.cpp
	src/core/shape.h
	src/core/shape.cpp
	src/core/texture.h
	src/core/texture.cpp
	src/core/light.h
	src/core/light.cpp
	src/core/hit.h
	src/core/hit.cpp
)

INCLUDE_DIRECTORIES ( src )
INCLUDE_DIRECTORIES ( src/core )
INCLUDE_DIRECTORIES ( src/textures )

SOURCE_GROUP (core REGULAR_EXPRESSION src/core/.*)
SOURCE_GROUP (textures REGULAR_EXPRESSION src/textures/.*)


ADD_LIBRARY ( engine STATIC
	${ENGINE_CORE_HEADERS}
	)


target_compile_options (engine PUBLIC ${PBRT_CXX_FLAGS})
IF (WIN32)
  # Avoid a name clash when building on Visual Studio
  SET_TARGET_PROPERTIES ( engine PROPERTIES OUTPUT_NAME libengine )
ENDIF()

SET(ALL_ENGINE_LIBS
  engine
)

# Main renderer
ADD_EXECUTABLE ( engine_exe src/main/engine.cpp )

SET_TARGET_PROPERTIES ( engine_exe PROPERTIES OUTPUT_NAME engine )
target_compile_options ( engine_exe PRIVATE ${PBRT_CXX_FLAGS} )
TARGET_LINK_LIBRARIES ( engine_exe ${ALL_ENGINE_LIBS} )
