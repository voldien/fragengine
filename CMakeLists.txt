CMAKE_MINIMUM_REQUIRED(VERSION 3.7.2)
PROJECT(fragview CXX)

# Build shared/dynamic library option
OPTION(BUILD_SHARED_LIBS "Build package with shared libraries." ON)
OPTION(BUILD_WITH_COVERAGE "Enable profiling and coverage report analysis." ON)
OPTION(BUILD_WITH_PROFILER "Enable profiling." ON)
OPTION(BUILD_WITH_EXTERNAL_PROJECT "Enable external project build." ON)
IF(NOT BUILD_SHARED_LIBS)
	SET(CMAKE_EXE_LINKER_FLAGS "-static")
	SET(LINK_SEARCH_START_STATIC TRUE)
ELSE()
	MESSAGE(STATUS "Shared libraries enabled")
ENDIF(NOT BUILD_SHARED_LIBS)

OPTION(BUILD_WITH_TEST "Enable Testing." ON)
OPTION(BUILD_WITH_EDITOR "Build editor." ON)
OPTION(BUILD_WITH_DOCS "Build documentation." ON)

# Set version of the project.
SET(VERSION_MAJOR 0)
SET(VERSION_MINOR 10)
SET(VERSION_REVISION 0)
SET(VERSION_STATE a)
SET(VERSION ${VERSION_MAJOR}.${VERSION_MINOR}${VERSION_STATE}${VERSION_REVISION} )
SET(PROJECT_VERSION "${VERSION}")

# Set predefined macro for version.
ADD_DEFINITIONS(-DFV_VERSION="${VERSION}")

SET(LIBFRAGVIEW_COMPONENT     "libfragview${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_REVISION}" )
SET(LIBFRAGVIEW-DEV_COMPONENT "libfragview${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_REVISION}-dev" )
SET(CPACK_COMPONENTS_ALL fragview-bin ${LIBFRAGVIEW_COMPONENT} ${LIBFRAGVIEW-DEV_COMPONENT} fragview-dev)
SET(FRAGVIEW_LIBRARY_SUFFIX "" CACHE STRING "Suffix to append to library names")

# GCC compiler flag options.
IF((CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX) AND NOT CMAKE_COMPILER_IS_MINGW)
	IF (BUILD_SHARED_LIBS AND CMAKE_SIZEOF_VOID_P EQUAL 8) # -fPIC is only required
		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
	ENDIF()

	ADD_DEFINITIONS(-Wall -w -fpermissive)
	ADD_DEFINITIONS( -export-dynamic  -rdynamic )

	IF (CMAKE_BUILD_TYPE STREQUAL "Release")
		MESSAGE(STATUS "Compile for release.")
		ADD_DEFINITIONS(-DNDEBUG=1)
		ADD_DEFINITIONS(-O3)
		SET(CMAKE_RELEASE TRUE)
		SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -s")
	ELSE()
		MESSAGE(STATUS "Compile for debug.")
		ADD_DEFINITIONS(-D_DEBUG)
		ADD_DEFINITIONS(-g3 -O0)
		SET(CMAKE_DEBUG TRUE)
		ADD_DEFINITIONS(-D_GLIBCXX_ASSERTIONS)
	ENDIF()

	#
	IF(BUILD_WITH_COVERAGE)
		MESSAGE(STATUS "Building with coverage")
		SET(GCC_COVERAGE_COMPILE_FLAGS "--coverage -fprofile-arcs -ftest-coverage")
		SET(GCC_COVERAGE_LINK_FLAGS    "-lgcov")
		SET(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
		SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
		SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")
	ENDIF()

	#
	IF(BUILD_WITH_PROFILER)
		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
		SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")
		SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -pg")
	ENDIF()

ELSEIF(MSVC)
	# Enable multi-core compilation with MSVC
	ADD_COMPILE_OPTIONS(/MP)
ELSEIF ( "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang" )
	SET(CMAKE_CXX_FLAGS "-g -fvisibility=hidden -fno-strict-aliasing -Wall -Wno-long-long ${CMAKE_CXX_FLAGS}" )
	SET(CMAKE_C_FLAGS "-fno-strict-aliasing ${CMAKE_C_FLAGS}")
ELSEIF( CMAKE_COMPILER_IS_MINGW )
	SET(CMAKE_CXX_FLAGS "-fvisibility=hidden -fno-strict-aliasing -Wall -Wno-long-long -Wa,-mbig-obj ${CMAKE_CXX_FLAGS}")
	SET(CMAKE_C_FLAGS "-fno-strict-aliasing ${CMAKE_C_FLAGS}")
	ADD_DEFINITIONS( -U__STRICT_ANSI__ )
ENDIF()

# 
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include/)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include/)

# Set c++ language version required for the project.
IF( CMAKE_COMPILER_IS_GNUCXX )
	SET(LIBSTDC++_LIBRARIES -std=c++11)
ENDIF( CMAKE_COMPILER_IS_GNUCXX )

# Cache these to allow the user to override them manually.
SET( FRAGVIEW_LIB_INSTALL_DIR "lib" CACHE STRING
		"Path the built library files are installed to." )
SET( FRAGVIEW_INCLUDE_INSTALL_DIR "include" CACHE STRING
		"Path the header files are installed to." )
SET( FRAGVIEW_BIN_INSTALL_DIR "bin" CACHE STRING
		"Path the tool executables are installed to." )

# Find all required libaries for the program.
FIND_PACKAGE(ZLIB REQUIRED)
FIND_PACKAGE(Git REQUIRED)
FIND_PACKAGE(Backtrace REQUIRED)
FIND_PACKAGE(PkgConfig)
FIND_PACKAGE(Doxygen)

# Find and include libxml2 for supporting configuration.
FIND_PACKAGE(LibXml2)
IF ( LIBXML2_FOUND )
	MESSAGE(STATUS "Using xml2 version ${LIBXML2_VERSION_STRING}.")
	INCLUDE_DIRECTORIES(${LIBXML2_INCLUDE_DIR})
ELSE()
ENDIF()

IF(GIT_FOUND)
	MESSAGE(STATUS "git found: ${GIT_EXECUTABLE} -- ${GIT_VERSION_STRING}")
ELSE()
ENDIF()

IF(ZLIB_FOUND)
	MESSAGE(STATUS "zlib found: ${ZLIB_LIBRARIES} -- ${ZLIB_VERSION_STRING}")
	INCLUDE_DIRECTORIES(${ZLIB_INCLUDE_DIRS})
ELSE()
ENDIF()

IF(Backtrace_FOUND)
	MESSAGE(STATUS "backtrace found: ${Backtrace_LIBRARIES} -- ${Backtrace_HEADER}")
	INCLUDE_DIRECTORIES(${Backtrace_INCLUDE_DIRS})
ELSE()
ENDIF()

IF(DOXYGEN_FOUND)
	MESSAGE(STATUS "Doxygen found: ${DOXYGEN_EXECUTABLE} -- ${DOXYGEN_VERSION}")
	IF(BUILD_WITH_DOCS)
		ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/docs/)
	ENDIF(BUILD_WITH_DOCS)
ENDIF()

#
FIND_PACKAGE(Freetype REQUIRED)
IF(FREETYPE_FOUND)
	MESSAGE(STATUS "Using freetype version ${FREETYPE_VERSION_STRING}.")
	INCLUDE_DIRECTORIES(${FREETYPE_INCLUDE_DIRS})
ELSE()
ENDIF()

# Include library include directories.
#INCLUDE_DIRECTORIES(${SDL_INCLUDE_DIR})

IF(BUILD_WITH_EXTERNAL_PROJECT)
	# Git must be avaiable on the system for using the external projects.
	IF(NOT GIT_FOUND)
		MESSAGE(FATAL_ERROR "Require Git for loading external projects.")
	ENDIF()
	INCLUDE(ExternalProject)
	SET_PROPERTY(DIRECTORY PROPERTY EP_STEP_TARGETS build)

	# TODO add build config for CMAKE_BUILD_TYPE

	# Download the task-schedular library.
	SET(TASKSCH_ROOT ${CMAKE_BINARY_DIR}/deps/task-sch)
	SET(TASKSCH_LIB_DIR ${TASKSCH_ROOT}/lib)
	SET(TASKSCH_INCLUDE_DIR ${TASKSCH_ROOT}/include)

	ExternalProject_Add(tasksch-external
			PREFIX ${TASKSCH_ROOT}
			GIT_REPOSITORY "https://github.com/voldien/task-scheduler.git"
			GIT_TAG "master"
			UPDATE_COMMAND ""
			PATCH_COMMAND ""
			SOURCE_DIR ${TASKSCH_ROOT}/src/tasksch
			BINARY_DIR ${TASKSCH_ROOT}/src/tasksch-build
			INSTALL_DIR ${TASKSCH_ROOT}
			CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>  -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
			STEP_TARGETS build
			COMMENT "Building taskschedular"
			LOG_DOWNLOAD ON)
	# Include tasksch headers.
	ADD_LIBRARY(taskSch SHARED IMPORTED)
	ADD_DEPENDENCIES(taskSch tasksch-external)
	SET_TARGET_PROPERTIES(taskSch PROPERTIES
			IMPORTED_LOCATION "${TASKSCH_LIB_DIR}/libtaskSch.so"
			INTERFACE_INCLUDE_DIRECTORIES "${TASKSCH_INCLUDE_DIR}")
	INCLUDE_DIRECTORIES(${TASKSCH_INCLUDE_DIR})

	# Download the hpm library.
	SET(HPM_ROOT ${CMAKE_BINARY_DIR}/deps/hpm)
	SET(HPM_LIB_DIR ${HPM_ROOT}/lib)
	SET(HPM_INCLUDE_DIR ${HPM_ROOT}/include)
	ExternalProject_Add(hpm-external
			PREFIX ${HPM_ROOT}
			GIT_REPOSITORY "https://github.com/voldien/hpm.git"
			GIT_TAG "master"
			UPDATE_COMMAND ""
			PATCH_COMMAND ""
			SOURCE_DIR ${HPM_ROOT}/src/hpm
			BINARY_DIR ${HPM_ROOT}/src/hpm-build
			INSTALL_DIR ${HPM_ROOT}
			CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>  -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
			STEP_TARGETS build
			COMMENT "Building Hpm."
			LOG_DOWNLOAD ON)
	# Include tasksch headers.
	ADD_LIBRARY(hpm SHARED IMPORTED)
	ADD_DEPENDENCIES(hpm hpm-external)
	SET_TARGET_PROPERTIES(hpm PROPERTIES
			IMPORTED_LOCATION "${HPM_LIB_DIR}/libhpm.so"
			INTERFACE_INCLUDE_DIRECTORIES "${HPM_INCLUDE_DIR}")
	INCLUDE_DIRECTORIES(${HPM_INCLUDE_DIR})

	# Download the HPMCPP library.
	SET(HPMCPP_ROOT ${CMAKE_BINARY_DIR}/deps/hpmcpp)
	SET(HPMCPP_LIB_DIR ${HPMCPP_ROOT}/lib)
	SET(HPMCPP_INCLUDE_DIR ${HPMCPP_ROOT}/include)
	ExternalProject_Add(hpmcpp-external
			PREFIX ${HPMCPP_ROOT}
			GIT_REPOSITORY "https://github.com/voldien/hpmcpp.git"
			GIT_TAG "master"
			UPDATE_COMMAND ""
			PATCH_COMMAND ""
			SOURCE_DIR ${HPMCPP_ROOT}/src/hpmcpp
			BINARY_DIR ${HPMCPP_ROOT}/src/hpmcpp-build
			INSTALL_DIR ${HPMCPP_ROOT}
			CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>  -DBUILD_WITH_EXTERNAL_PROJECT=OFF -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
			STEP_TARGETS hpm-external build
			COMMENT "Building HPM-CPP"
			LOG_DOWNLOAD ON)
	# Include HPMCPP headers.
	ADD_LIBRARY(hpmcpp SHARED IMPORTED)
	ADD_DEPENDENCIES(hpmcpp hpm-external hpmcpp-external)
	SET_TARGET_PROPERTIES(hpmcpp PROPERTIES
			IMPORTED_LOCATION "${HPMCPP_LIB_DIR}/libhpmcpp.so"
			INTERFACE_INCLUDE_DIRECTORIES "${HPMCPP_INCLUDE_DIR}")
	INCLUDE_DIRECTORIES(${HPMCPP_INCLUDE_DIR})

ENDIF()


# Define all file lists.
FILE(GLOB SOURCE_FILES  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/src/scene/*.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/src/scene/subgraph/*.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/src/RenderPipeline/*.cpp	#TODO rename to lower case letter.
		${CMAKE_CURRENT_SOURCE_DIR}/src/renderer/*.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/src/exception/*.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/src/utils/*.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/src/core/*.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/src/core/io/*.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/src/shadermodel/*.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/src/shaders/*.cpp)
FILE(GLOB SOURCE_MAIN_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
FILE(GLOB HEADER_FILES  ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
		${CMAKE_CURRENT_SOURCE_DIR}/include/Core/*.h
		${CMAKE_CURRENT_SOURCE_DIR}/include/Exception/*.h
		${CMAKE_CURRENT_SOURCE_DIR}/include/Renderer/*.h
		${CMAKE_CURRENT_SOURCE_DIR}/include/RenderPipeline/*.h)
FILE(GLOB DEVELOPMENT_HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
FILE(GLOB SAMPLE_GLSL_FILES ${CMAKE_CURRENT_SOURCE_DIR}/samples/glsl/* )
FILE(GLOB SAMPLE_HLSL_FILES ${CMAKE_CURRENT_SOURCE_DIR}/samples/hlsl/* )
FILE(GLOB SAMPLE_SPIRV_FILES ${CMAKE_CURRENT_SOURCE_DIR}/samples/spirv/* )
FILE(GLOB SAMPLE_CLC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/samples/clc/* )
FILE(GLOB SAMPLE_SHADER_SPIRV_FILES ${CMAKE_CURRENT_SOURCE_DIR}/shaders/spirv/* )

# Core library for adding support for plugin.
ADD_LIBRARY(fragview-core ${SOURCE_FILES} ${HEADER_FILES})
TARGET_LINK_LIBRARIES(fragview-core  -lSDL2  ${ZLIB_LIBRARIES} ${LIBXML2_LIBRARIES} ${Backtrace_LIBRARIES} ${FREETYPE_LIBRARIES}
		-lzip -lfreeimage -lm -ldl taskSch -lfswatch -ljsoncpp -lyaml hpmcpp hpm -lassimp)
ADD_DEPENDENCIES(fragview-core taskSch hpm)
INSTALL(TARGETS fragview-core DESTINATION lib)
INSTALL(FILES ${DEVELOPMENT_HEADER_FILES} DESTINATION include)

# Main executable.
ADD_EXECUTABLE(fragview  ${SOURCE_MAIN_FILES} ${HEADER_FILES})
TARGET_LINK_LIBRARIES(fragview fragview-core)
INSTALL(TARGETS fragview DESTINATION bin)

# Rendering interfaces.
ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/src/renderer/opengl/)
ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/src/renderer/directx/)
ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/src/renderer/vulkan/)
ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/src/renderer/opencl/)

# Editor.
IF(BUILD_WITH_EDITOR)
	ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/editor/)
ENDIF()

# Testing.
IF(BUILD_WITH_TEST)
	ENABLE_TESTING()
	ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/test/)
ENDIF(BUILD_WITH_TEST)

# Generate package configuration file.
CONFIGURE_FILE( "${PROJECT_SOURCE_DIR}/fragview-core.pc.in" "${PROJECT_BINARY_DIR}/fragview-core.pc" @ONLY )
INSTALL( FILES "${PROJECT_BINARY_DIR}/fragview-core.pc" DESTINATION ${FRAGVIEW_LIB_INSTALL_DIR}/pkgconfig/ COMPONENT ${LIBFRAGVIEW-DEV_COMPONENT})

# Only UNIX systems.
IF( UNIX )
	Find_PACKAGE(UnixCommands REQUIRED)

	FIND_PROGRAM(GLSLLANGVALIDATOR glslangValidator)
	IF(GLSLLANGVALIDATOR)
		MESSAGE(STATUS "glslangValidator found: ${GLSLLANGVALIDATOR}")
		#TODO add for all shaders.
		ADD_CUSTOM_TARGET(samples-spirv
				COMMENT "Creating spirv shader from the display shader.")
		#ADD_DEPENDENCIES(fragview samples-spirv)
		FOREACH(glslFile ${SAMPLE_GLSL_FILES})
			MESSAGE(STATUS ${glslFile} )
			ADD_CUSTOM_COMMAND(TARGET samples-spirv PRE_BUILD
					COMMAND glslangValidator --entry-point main --auto-map-bindings --auto-map-locations --uniform-base 0
					-u:time:10 --client opengl100 -V -G450 ${glslFile} -o ${CMAKE_CURRENT_SOURCE_DIR}/samples/spirv/)
		ENDFOREACH()

		# Create default shader
		ADD_CUSTOM_TARGET(display-spirv
				COMMENT "Creating spirv shader from the display shader.")
		#ADD_DEPENDENCIES(fragview display-spirv)
		FOREACH(glslFile ${SAMPLE_SHADER_SPIRV_FILES})
			ADD_CUSTOM_COMMAND(TARGET display-spirv PRE_BUILD
					COMMAND glslangValidator --entry-point main --auto-map-bindings --auto-map-locations --uniform-base 0
					-u:time:10 --client opengl100 -V -G450 ${glslFile} -o ${CMAKE_CURRENT_SOURCE_DIR}/)
		ENDFOREACH()

	ELSE()
		MESSAGE(WARNING "Could not find the glslangValidator program for creating spirv shaders.")
	ENDIF()

	FIND_PROGRAM(ZIP zip)

	IF(ZIP)
		MESSAGE(STATUS "zip found: ${ZIP}")
		# Create default shader zip file.
		SET( SHADERZIP "defaultshader" )
		SET( SHADERZIPFILE "${SHADERZIP}.zip" )

		#		# TODO add addition for adding support for spirv and combine multiple files.
		ADD_CUSTOM_TARGET(	internal-shader-generation
				#				COMMAND mkdir -p glsl
				#				COMMAND cp -r shader/glsl/* glsl/
				#				COMMAND zip -r ${SHADERZIPFILE} glsl/
				#				COMMAND rm -r glsl
				COMMENT "Generating internal glsl shader files")
		ADD_DEPENDENCIES(fragview internal-shader-generation)

		INSTALL( FILES ${SHADERZIPFILE} DESTINATION /usr/share/fragview )
	ENDIF()
	# Install bash autocomplete.
	INSTALL( FILES ${CMAKE_CURRENT_SOURCE_DIR}/bashcomplete/fragview DESTINATION /usr/share/bash-completion/completions/ )

	# Install main icon image.
	ADD_DEFINITIONS(-DICON_LOCATION="/usr/share/fragview/")
	INSTALL( FILES ${CMAKE_CURRENT_SOURCE_DIR}/fragview.png DESTINATION /usr/share/fragview/ )

	# Install samples.
	INSTALL( FILES ${CMAKE_CURRENT_SOURCE_DIR}/fragview.desktop DESTINATION /usr/share/fragview/ )
	INSTALL( FILES ${SAMPLE_GLSL_FILES} DESTINATION /usr/share/fragview/samples/glsl )
	INSTALL( FILES ${SAMPLE_HLSL_FILES} DESTINATION /usr/share/fragview/samples/hlsl )
	INSTALL( FILES ${SAMPLE_SPIRV_FILES} DESTINATION /usr/share/fragview/samples/spriv )
	INSTALL( FILES ${SAMPLE_CLC_FILES} DESTINATION /usr/share/fragview/samples/clc )

	# Install scripts
	INSTALL( FILES ${CMAKE_CURRENT_SOURCE_DIR}/scripts/newshad.sh DESTINATION /usr/share/fragview/ )

	# Install man page. TODO add compression.
	#ADD_CUSTOM_TARGET() ${GZIP}
	INSTALL( FILES ${CMAKE_CURRENT_SOURCE_DIR}/fragview.1.gz DESTINATION /usr/share/man/man1/)

	# Create distribution tarball.
	SET( TARGETDIR "${PROJECT_NAME}-${VERSION}")
	ADD_CUSTOM_TARGET(	distribution
			COMMENT "Creating distrubtion file."
			COMMAND mkdir -p ${TARGETDIR}
			COMMAND ${CP} -r   ${CMAKE_CURRENT_SOURCE_DIR}/src
			${CMAKE_CURRENT_SOURCE_DIR}/include
			${CMAKE_CURRENT_SOURCE_DIR}/shaders
			${CMAKE_CURRENT_SOURCE_DIR}/samples
			${CMAKE_CURRENT_SOURCE_DIR}/scripts
			${CMAKE_CURRENT_SOURCE_DIR}/utils
			${CMAKE_CURRENT_SOURCE_DIR}/test
			${CMAKE_CURRENT_SOURCE_DIR}/images
			${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt
			${CMAKE_CURRENT_SOURCE_DIR}/travis.yaml
			${CMAKE_CURRENT_SOURCE_DIR}/fragview.desktop
			${CMAKE_CURRENT_SOURCE_DIR}/fragview.1
			${CMAKE_CURRENT_SOURCE_DIR}/bashcomplete
			${CMAKE_CURRENT_SOURCE_DIR}/fragview.png
			${CMAKE_CURRENT_SOURCE_DIR}/.gitignore
			${CMAKE_CURRENT_SOURCE_DIR}/LICENSE
			${TARGETDIR}
			COMMAND ${TAR} cf - ${TARGETDIR} | ${GZIP} -c > ${TARGETDIR}.tar.gz
			COMMAND ${RM} -r ${TARGETDIR} )

	# Check if desktop icon tools exists.
	FIND_PROGRAM(INSTALL_DESKTOP install-desktop)
	FIND_PROGRAM(INSTALL_DESKTOP_FILE_VALIDATE desktop-file-validate)
	FIND_PROGRAM(DESKTOP_FILE_INSTALL desktop-file-install)
	FIND_PROGRAM(UPDATE_DESKTOP_DATABASE update-desktop-database)

	# Check that the program exists.
	IF(INSTALL_DESKTOP AND INSTALL_DESKTOP_FILE_VALIDATE AND DESKTOP_FILE_INSTALL AND UPDATE_DESKTOP_DATABASE)
		MESSAGE(STATUS "install-desktop: ${INSTALL_DESKTOP}")
		MESSAGE(STATUS "desktop-file-validate: ${INSTALL_DESKTOP_FILE_VALIDATE}")
		MESSAGE(STATUS "desktop-file-install: ${DESKTOP_FILE_INSTALL}")
		MESSAGE(STATUS "update-desktop-database: ${UPDATE_DESKTOP_DATABASE}")

		# Install icons.
		ADD_CUSTOM_TARGET(install-desktop
				COMMENT "Validating and installing desktop entry."
				COMMAND desktop-file-validate ${CMAKE_CURRENT_SOURCE_DIR}/fragview.desktop
				COMMAND desktop-file-install --rebuild-mime-info-cache ${CMAKE_CURRENT_SOURCE_DIR}/fragview.desktop
				COMMAND update-desktop-database
				DEPENDS INSTALL_DESKTOP INSTALL_DESKTOP_FILE_VALIDATE DESKTOP_FILE_INSTALL UPDATE_DESKTOP_DATABASE)
	ELSE()
		MESSAGE(WARNING "Could not find the program tools for installing the icon and its images.")
	ENDIF()

	FIND_PROGRAM(CONVERT convert)
	IF(CONVERT)
		# Create icons for all sizes
		ADD_CUSTOM_TARGET(create-icons
				COMMENT "Creating icon for all sizes."
				COMMAND mkdir -p ${CMAKE_CURRENT_SOURCE_DIR}/images/
				COMMAND mkdir -p ${CMAKE_CURRENT_SOURCE_DIR}/images/icons
				COMMAND mkdir -p ${CMAKE_CURRENT_SOURCE_DIR}/images/icons/16x16
				COMMAND mkdir -p ${CMAKE_CURRENT_SOURCE_DIR}/images/icons/24x24
				COMMAND mkdir -p ${CMAKE_CURRENT_SOURCE_DIR}/images/icons/32x32
				COMMAND mkdir -p ${CMAKE_CURRENT_SOURCE_DIR}/images/icons/48x48
				COMMAND mkdir -p ${CMAKE_CURRENT_SOURCE_DIR}/images/icons/64x64
				COMMAND mkdir -p ${CMAKE_CURRENT_SOURCE_DIR}/images/icons/96x96
				COMMAND mkdir -p ${CMAKE_CURRENT_SOURCE_DIR}/images/icons/128x128
				COMMAND mkdir -p ${CMAKE_CURRENT_SOURCE_DIR}/images/icons/256x256
				COMMAND mkdir -p ${CMAKE_CURRENT_SOURCE_DIR}/images/icons/1024x1024
				COMMAND convert ${CMAKE_CURRENT_SOURCE_DIR}/fragview.png -resize 16x16 ${CMAKE_CURRENT_SOURCE_DIR}/images/icons/16x16/fragview.png
				COMMAND convert ${CMAKE_CURRENT_SOURCE_DIR}/fragview.png -resize 24x24 ${CMAKE_CURRENT_SOURCE_DIR}/images/icons/24x24/fragview.png
				COMMAND convert ${CMAKE_CURRENT_SOURCE_DIR}/fragview.png -resize 32x32 ${CMAKE_CURRENT_SOURCE_DIR}/images/icons/32x32/fragview.png
				COMMAND convert ${CMAKE_CURRENT_SOURCE_DIR}/fragview.png -resize 48x48 ${CMAKE_CURRENT_SOURCE_DIR}/images/icons/48x48/fragview.png
				COMMAND convert ${CMAKE_CURRENT_SOURCE_DIR}/fragview.png -resize 64x64 ${CMAKE_CURRENT_SOURCE_DIR}/images/icons/64x64/fragview.png
				COMMAND convert ${CMAKE_CURRENT_SOURCE_DIR}/fragview.png -resize 96x96 ${CMAKE_CURRENT_SOURCE_DIR}/images/icons/96x96/fragview.png
				COMMAND convert ${CMAKE_CURRENT_SOURCE_DIR}/fragview.png -resize 128x128 ${CMAKE_CURRENT_SOURCE_DIR}/images/icons/128x128/fragview.png
				COMMAND convert ${CMAKE_CURRENT_SOURCE_DIR}/fragview.png -resize 256x256 ${CMAKE_CURRENT_SOURCE_DIR}/images/icons/256x256/fragview.png
				COMMAND convert ${CMAKE_CURRENT_SOURCE_DIR}/fragview.png -resize 1024x1024 ${CMAKE_CURRENT_SOURCE_DIR}/images/icons/1024x1024/fragview.png)
	ELSE()
		MESSAGE(WARNING "Could not find the convert program for resizing the images.")
	ENDIF()

ELSEIF(WIN32)

ELSE()

ENDIF()

FIND_PACKAGE(Icotool)
IF(ICOTOOL_FOUND)
	MESSAGE(STATUS "icotool: ${ICOTOOL_EXECUTABLE} -- ${ICOTOOL_VERSION_STRING}")
	# Generate icon for window platforms.
	# -c -o favicon.ico mysite_32x32.png mysite_64x64.png
	#    ADD_CUSTOM_TARGET( create-icon-type
	#            COMMENT "Creating header and source file for display shaders."
	#            COMMAND ${ICOTOOL_EXECUTABLE} -c -o favicon.ico mysite_32x32.png mysite_64x64.png)
ELSE()
	MESSAGE(WARNING "Could not find the program tools for creating window icons.")
ENDIF()

# TODO add some logic for determine if exists.
IF(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/images/icons)
	FOREACH(size 16 24 32 48 64 128 256)

		INSTALL( FILES ${CMAKE_CURRENT_SOURCE_DIR}/images/icons/${size}x${size}/fragview.png DESTINATION /usr/share/icons/hicolor/${size}x${size}/apps/
				RENAME fragview.png)
		INSTALL( FILES ${CMAKE_CURRENT_SOURCE_DIR}/images/icons/${size}x${size}/fragview.png DESTINATION /usr/share/icons/hicolor/${size}x${size}/mimetypes/
				RENAME application-fragview-doc.png)
	ENDFOREACH()
ENDIF()

FIND_PACKAGE(PythonInterp)
IF(PYTHONINTERP_FOUND)
	ADD_CUSTOM_TARGET( compile-shader
			COMMENT "Creating header and source file for display shaders."
			COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/utils/glsl2CString.py ${CMAKE_CURRENT_SOURCE_DIR}/shaders/glsl/
			DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/utils/glsl2CString.py)
	ADD_DEPENDENCIES(fragview compile-shader)
ENDIF()


IF(WIN32)
	IF (CMAKE_SIZEOF_VOID_P EQUAL 8)
		SET(BIN_DIR "${PROJECT_SOURCE_DIR}/bin64/")
		SET(LIB_DIR "${PROJECT_SOURCE_DIR}/lib64/")
	else()
		SET(BIN_DIR "${PROJECT_SOURCE_DIR}/bin32/")
		SET(LIB_DIR "${PROJECT_SOURCE_DIR}/lib32/")
	ENDIF()

	IF(MSVC_TOOLSET_VERSION)
		set(MSVC_PREFIX "vc${MSVC_TOOLSET_VERSION}")
	ELSE()
		IF(MSVC12)
		ELSEIF(MSVC14)
		ELSEIF(MSVC15)
		ENDIF(MSVC12)

	ENDIF()

	IF(MSVC12 OR MSVC14 OR MSVC15 )

	ENDIF(MSVC12 OR MSVC14 OR MSVC15 )
ENDIF (WIN32)


