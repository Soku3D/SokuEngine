cmake_minimum_required( VERSION 3.12)

project ( ENGINE )

SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)

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
)

INCLUDE_DIRECTORIES ( src )
INCLUDE_DIRECTORIES ( src/core )

SOURCE_GROUP (core REGULAR_EXPRESSION src/core/.*)

ADD_LIBRARY ( engine STATIC
	${ENGINE_CORE_HEADERS}
	)

SET ( ENGINE_CXX11_FEATURES
  cxx_auto_type
  cxx_explicit_conversions
  cxx_lambdas
  cxx_nullptr
  cxx_range_for
  cxx_static_assert
)
TARGET_COMPILE_FEATURES ( engine PRIVATE ${engine_CXX11_FEATURES} )

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
TARGET_COMPILE_FEATURES ( engine_exe PRIVATE ${ENGINE_CXX11_FEATURES} )
TARGET_LINK_LIBRARIES ( engine_exe ${ALL_ENGINE_LIBS} )
