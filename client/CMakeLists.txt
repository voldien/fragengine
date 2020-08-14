
OPTION(FRAGVIEW_BUILD_WITH_SANITY_CHECK "" ON)

#OPTION(BUILD_WITH_SDL_WINDOW "Use SDL for window mangement." ON)

# # Find packages.
# FIND_PACKAGE(PkgConfig)
# FIND_PROGRAM(OPENSSL openssl)
# IF(PKG_CONFIG_FOUND)
# 	IF(BUILD_WITH_SDL_WINDOW)
# 		PKG_CHECK_MODULES(SDL2 REQUIRED sdl2)
# 	ENDIF()
# ELSE()
# 	MESSAGE(WARNING "Could not find pgk-config, attempting default values.")
# 	#TODO default values for SDL2
# ENDIF()

# IF(SDL2_FOUND)
# 	MESSAGE(STATUS "SDL2 found: ${SDL2_LIBRARIES} -- ${SDL2_VERSION}")
# ELSE()

# ENDIF()

#TODO add for fragengine and fragcore!
#PKG_CHECK_MODULES(SDL2 REQUIRED sdl2)

#
FILE(GLOB SAMPLE_GLSL_FILES ${CMAKE_CURRENT_SOURCE_DIR}/samples/glsl/* )
FILE(GLOB SAMPLE_HLSL_FILES ${CMAKE_CURRENT_SOURCE_DIR}/samples/hlsl/* )
FILE(GLOB SAMPLE_SPIRV_FILES ${CMAKE_CURRENT_SOURCE_DIR}/samples/spirv/* )
FILE(GLOB SAMPLE_CLC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/samples/clc/* )



# Source files.
FILE(GLOB SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
FILE(GLOB HEADER_FILES  ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)


#
ADD_EXECUTABLE(fragview ${SOURCE_FILES} ${HEADER_FILES})
TARGET_LINK_LIBRARIES(fragview fragcore fragengine)
TARGET_INCLUDE_DIRECTORIES(fragview PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/ )
ADD_DEPENDENCIES(fragview fragcore fragengine)

# Create default shader zip file.
SET( SHADERZIP "fragview-internal-shaders" )
SET( SHADERZIPFILE "${SHADERZIP}.zip" )

FILE(GLOB SAMPLE_SHADER_GLSL_FILES ${PROJECT_SOURCE_DIR}/shaders/glsl/* )
FILE(GLOB SAMPLE_SHADER_SPIRV_FILES ${PROJECT_SOURCE_DIR}/shaders/spriv/* )


# Install binary program
IF(BUILD_WITH_INSTALL)
	INSTALL(TARGETS fragview DESTINATION bin COMPONENT ${BINFRAGVIEW_COMPONENT})

	IF(UNIX)
		Find_PACKAGE(UnixCommands REQUIRED)

		# Generate compressed man page.
		ADD_CUSTOM_TARGET(mangzip
				COMMAND ${GZIP} -k -c ${CMAKE_CURRENT_SOURCE_DIR}/fragview.1 > ${CMAKE_CURRENT_SOURCE_DIR}/fragview.1.gz
				COMMENT "Compressing man page.")
		ADD_DEPENDENCIES(fragview mangzip)
		INSTALL( FILES ${CMAKE_CURRENT_SOURCE_DIR}/fragview.1.gz DESTINATION /usr/share/man/man1/)

		#TOOD add spriv generating file.

		IF(ZIP)
			# TODO add addition for adding support for spirv and combine multiple files

			ADD_CUSTOM_TARGET(	internal-shader-generation
					COMMAND mkdir -p ${CMAKE_CURRENT_SOURCE_DIR}/shaders
					COMMAND ${CP} -r ${PROJECT_SOURCE_DIR}/shaders/* ${CMAKE_CURRENT_SOURCE_DIR}/shaders/
					COMMAND zip -r ${SHADERZIPFILE} ${PROJECT_SOURCE_DIR}/shaders/
					COMMAND ${RM} -r ${CMAKE_CURRENT_SOURCE_DIR}/shaders
					COMMENT "")
			ADD_DEPENDENCIES(fragview internal-shader-generation)
			INSTALL( FILES ${SHADERZIPFILE} DESTINATION /usr/share/fragview )
		ELSE()

		ENDIF()

		# Install scripts
		INSTALL( FILES ${CMAKE_CURRENT_SOURCE_DIR}/scripts/newshad.sh DESTINATION /usr/share/fragview/ )
		ADD_DEFINITIONS(-DICON_LOCATION="/usr/share/fragview/")

		INSTALL( FILES ${CMAKE_CURRENT_SOURCE_DIR}/fragview.png DESTINATION /usr/share/fragview/ )
		INSTALL( FILES ${CMAKE_CURRENT_SOURCE_DIR}/fragview.desktop DESTINATION /usr/share/fragview/ )

	ENDIF()

	# Install samples.
	#TODO resolve install path
	# INSTALL( FILES ${SAMPLE_GLSL_FILES} DESTINATION /usr/share/fragview/samples/glsl COMPONENT ${BINFRAGVIEW_COMPONENT})
	# INSTALL( FILES ${SAMPLE_HLSL_FILES} DESTINATION /usr/share/fragview/samples/hlsl COMPONENT ${BINFRAGVIEW_COMPONENT})
	# INSTALL( FILES ${SAMPLE_SPIRV_FILES} DESTINATION /usr/share/fragview/samples/spriv COMPONENT ${BINFRAGVIEW_COMPONENT})
	# INSTALL( FILES ${SAMPLE_CLC_FILES} DESTINATION /usr/share/fragview/samples/clc COMPONENT ${BINFRAGVIEW_COMPONENT})
ENDIF()

IF(OPENSSL AND FRAGVIEW_BUILD_WITH_SANITY_CHECK)
	# Generate verification finger print.
	MESSAGE(STATUS "openssl found: ${OPENSSL}")
	# ADD_CUSTOM_TARGET(hash-resources
	# 		COMMENT ".")
	# FOREACH(glslFile ${SAMPLE_SHADER_GLSL_FILES})
	# 	ADD_CUSTOM_COMMAND(TARGET hash-resources
	# 			COMMAND ${OPENSSL} dgst -md5 ${glslFile})
	# ENDFOREACH()
	# ADD_DEPENDENCIES(fragview hash-resources)
ENDIF()