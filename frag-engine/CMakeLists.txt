

#TODO add the rov2

# Define all file lists.
FILE(GLOB SOURCE_FILES  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
						${CMAKE_CURRENT_SOURCE_DIR}/src/scene/*.cpp
						${CMAKE_CURRENT_SOURCE_DIR}/src/scene/subgraph/*.cpp
						${CMAKE_CURRENT_SOURCE_DIR}/src/renderpipeline/*.cpp)
FILE(GLOB HEADER_FILES  ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
						${CMAKE_CURRENT_SOURCE_DIR}/include/Animation/*.h
						#${CMAKE_CURRENT_SOURCE_DIR}/include/Navigation/*.h
						${CMAKE_CURRENT_SOURCE_DIR}/include/Asset/*.h
						${CMAKE_CURRENT_SOURCE_DIR}/include/Scene/*.h
						${CMAKE_CURRENT_SOURCE_DIR}/include/RenderPipeline/*.h)

#
IF(PKG_CONFIG_FOUND)
	MESSAGE(STATUS "Found pkg-config: ${PKG_CONFIG_EXECUTABLE} -- version ${PKG_CONFIG_VERSION_STRING}.")
	# Find library and compiling options.
	#TODO add logic for handling if any of the pkg fails.
	#TODO determine if shall be relocated to the editor only.
	PKG_CHECK_MODULES(ASSIMP QUIET assimp)
ELSE()
	# TODO add logic for handling if pkg-config not available.
ENDIF()

SET(FRAG_ENGINE_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include")
SET(FRAG_CORE_INCLUDE_SUB_DIR 
				${CMAKE_CURRENT_SOURCE_DIR}/include/
				${CMAKE_CURRENT_SOURCE_DIR}/include/Animation
				${CMAKE_CURRENT_SOURCE_DIR}/include/Asset
				#${CMAKE_CURRENT_SOURCE_DIR}/include/Navigation
				${CMAKE_CURRENT_SOURCE_DIR}/include/network
				${CMAKE_CURRENT_SOURCE_DIR}/include/RenderPipeline
				${CMAKE_CURRENT_SOURCE_DIR}/include/Scene)


# Core library for adding support for plugin.
ADD_LIBRARY(fragengine ${SOURCE_FILES} ${HEADER_FILES})
TARGET_LINK_LIBRARIES(fragengine PUBLIC fragcore fragcore-render-interface fragcore-audio-interface PRIVATE ${ASSIMP_LIBRARIES})
ADD_DEPENDENCIES(fragengine fragcore fragcore-render-interface fragcore-audio-interface)
TARGET_COMPILE_DEFINITIONS(fragengine PRIVATE FRAG_ENGINE_INTERNAL_IMP=1 FV_VERSION=0)

#
SET_TARGET_PROPERTIES(fragengine PROPERTIES
		COMPILE_FLAGS "${SDL2_CFLAGS_OTHER} ${ASSIMP_CFLAGS_OTHER} " )
TARGET_INCLUDE_DIRECTORIES( fragengine PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

#
CONFIGURE_FILE("${CMAKE_CURRENT_SOURCE_DIR}/include/revision.h.in" "${CMAKE_CURRENT_SOURCE_DIR}/include/revision.h" @ONLY)
#
CONFIGURE_FILE("${CMAKE_CURRENT_SOURCE_DIR}/fragengine.pc.in" "${PROJECT_BINARY_DIR}/fragengine.pc" @ONLY)

IF(BUILD_WITH_INSTALL)
	INSTALL(TARGETS fragengine DESTINATION lib)

	INSTALL(DIRECTORY ${FRAG_CORE_INCLUDE_SUB_DIR} # source directory
			DESTINATION "include/fragengine" # target directory
			COMPONENT ${LIBFRAGENGINE-DEV_COMPONENT}
			)
	INSTALL( FILES "${PROJECT_BINARY_DIR}/fragengine.pc" DESTINATION ${FRAGENGINE_LIB_INSTALL_DIR}/pkgconfig/ COMPONENT ${LIBFRAGENGINE-DEV_COMPONENT})
ENDIF()

# Only UNIX systems.
IF( UNIX )
	Find_PACKAGE(UnixCommands REQUIRED)	
ENDIF()
