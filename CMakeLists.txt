CMAKE_MINIMUM_REQUIRED( VERSION 3.0 )

PROJECT(fragview VERSION 0.11.1)

ENABLE_LANGUAGE(CXX)
ENABLE_LANGUAGE(C)

# Build shared/dynamic library option
OPTION(BUILD_SHARED_LIBS "Build package with shared libraries." ON)
OPTION(BUILD_WITH_COVERAGE "Enable profiling and coverage report analysis." ON)
OPTION(BUILD_WITH_PROFILER "Enable profiling." ON)
OPTION(BUILD_WITH_EXTERNAL_PROJECT "Enable external project build." ON)
OPTION(BUILD_WITH_EXTERNAL_PLUGINS "" ON)
OPTION(BUILD_WITH_INSTALL "Disable this if you want to use fragengine as a submodule." ON )
OPTION(BUILD_WITH_UBSAN "" ON)
OPTION(BUILD_WITH_ASAN "Enable AddressSanitizer." OFF )
OPTION(BUILD_OPT_BUILD_PACKAGES "Set to ON to generate CPack configuration files and packaging targets" OFF)
IF(NOT BUILD_SHARED_LIBS)
	SET(CMAKE_EXE_LINKER_FLAGS "-static")
	SET(LINK_SEARCH_START_STATIC TRUE)
ELSE()
	MESSAGE(STATUS "Shared libraries enabled")
ENDIF(NOT BUILD_SHARED_LIBS)

#
OPTION(BUILD_WITH_TEST "Enable Testing." ON)
OPTION(BUILD_WITH_EDITOR "Build editor." ON)
OPTION(BUILD_WITH_DOCS "Build documentation." OFF)
OPTION(BUILD_WITH_CLIENT "Build Client" ON)
OPTION(BUILD_WITH_CORE "Build Core" ON)
OPTION(BUILD_WITH_ENGINE "Build Frag Engine" ON)
OPTION(BUILD_WITH_SAMPLES "Build sample codes" OFF)

# Build external interface plugin.
OPTION(BUILD_EXTERNAL_RENDERER "Building external renderer libraries" ON)
OPTION(BUILD_EXTERNAL_AUDIO "Building external audio libraries" ON)
OPTION(BUILD_EXTERNAL_PHYSIC "Building external physic libraries" ON)

IF(MSVC)
  OPTION( BUILD_INSTALL_PDB
    "Install MSVC debug files."
    ON
  )
  IF(NOT (MSVC_VERSION LESS 1900))
    # Multibyte character set is deprecated since at least MSVC2015 (possibly earlier)
    ADD_DEFINITIONS( -DUNICODE -D_UNICODE )
  ENDIF()
ENDIF()


# Set version of the project.
SET(VERSION_MAJOR 0)
SET(VERSION_MINOR 11)
SET(VERSION_REVISION 0)
SET(VERSION_STATE a)
SET(VERSION ${VERSION_MAJOR}.${VERSION_MINOR}${VERSION_STATE}${VERSION_REVISION} )
SET(PROJECT_VERSION "${VERSION}")

# Set predefined macro for version.
ADD_DEFINITIONS(-DFV_VERSION="${VERSION}")


IF(NOT FRAG_IGNORE_GIT_HASH)
  # Get the current working branch
  EXECUTE_PROCESS(
    COMMAND git rev-parse --abbrev-ref HEAD
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_BRANCH
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
  )

  # Get the latest abbreviated commit hash of the working branch
  EXECUTE_PROCESS(
    COMMAND git rev-parse --short=8 HEAD
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_COMMIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
  )
ENDIF()

# CONFIGURE_FILE(
#   ${CMAKE_CURRENT_LIST_DIR}/revision.h.in
#   ${CMAKE_CURRENT_BINARY_DIR}/revision.h
# )


LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules" )
SET(LIBFRAGCORE_COMPONENT "libfragcore{VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_REVISION}")
SET(LIBFRAGCORE-DEV_COMPONENT "libfragcore{VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_REVISION}-dev")
SET(LIBFRAGENGINE_COMPONENT "libfragengine{VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_REVISION}")
SET(LIBFRAGENGINE-DEV_COMPONENT "libfragengine{VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_REVISION}-dev")

SET(FRAGVIEW_COMPONENT "fragview{VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_REVISION}")
SET(FRAEDITOR_COMPONENT "frageditor{VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_REVISION}")

SET(CPACK_COMPONENTS_ALL fragview-bin ${LIBFRAGCORE_COMPONENT} ${LIBFRAGCORE-DEV_COMPONENT}
	${LIBFRAGENGINE_COMPONENT} ${LIBFRAGENGINE-DEV_COMPONENT} $FRAGVIEW_COMPONENT} ${FRAGEDITOR_COMPONENT})
SET(FRAGVIEW_LIBRARY_SUFFIX "" CACHE STRING "Suffix to append to library names")

# macro that sets a default (path) if one wasn't specified
MACRO(SET_PATH variable default)
	IF(NOT ${variable})
		SET(${variable} ${default})
	ENDIF(NOT ${variable})
ENDMACRO(SET_PATH)

#LIB_DIRif (${LAYOUT} MATCHES "home")
SET_PATH( PLUGIN_DIR ${CMAKE_INSTALL_PREFIX}/plugins )
SET_PATH( DATA_DIR ${CMAKE_INSTALL_PREFIX} )
SET_PATH( MAN_DIR ${CMAKE_INSTALL_PREFIX}/man/man6 )
SET_PATH( BIN_DIR ${CMAKE_INSTALL_PREFIX} )
SET_PATH( SYSCONF_DIR ${CMAKE_INSTALL_PREFIX} )
SET_PATH( LIB_DIR ${CMAKE_INSTALL_PREFIX} )
SET_PATH( DOC_DIR ${CMAKE_INSTALL_PREFIX}/doc )
SET_PATH( ICON_DIR ${CMAKE_INSTALL_PREFIX} )
SET_PATH( SVG_DIR ${CMAKE_INSTALL_PREFIX} )
SET_PATH( MENU_DIR ${CMAKE_INSTALL_PREFIX} )
SET_PATH( EXAMPLE_CONF_DIR ${CMAKE_INSTALL_PREFIX} )
#elseif (${LAYOUT} MATCHES "fhs")

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
ELSEIF ( "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang" )
  SET(CMAKE_CXX_FLAGS "-fvisibility=hidden -fno-strict-aliasing -Wall -Wno-long-long ${CMAKE_CXX_FLAGS}" )
  SET(CMAKE_C_FLAGS "-fno-strict-aliasing ${CMAKE_C_FLAGS}")
ELSEIF(MSVC)
	# Enable multi-core compilation with MSVC
	IF( "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang" ) # clang-cl
		ADD_COMPILE_OPTIONS(/bigobj /W4 /WX )
	ELSE() # msvc
		ADD_COMPILE_OPTIONS(/MP /bigobj /W4 /WX)
	ENDIF()

	SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /D_DEBUG /Zi /Od")
ELSEIF ( "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang" )
	SET(CMAKE_CXX_FLAGS "-g -fvisibility=hidden -fno-strict-aliasing -Wall -Wno-long-long ${CMAKE_CXX_FLAGS}" )
	SET(CMAKE_C_FLAGS "-fno-strict-aliasing ${CMAKE_C_FLAGS}")
ELSEIF( CMAKE_COMPILER_IS_MINGW )
	SET(CMAKE_CXX_FLAGS "-fvisibility=hidden -fno-strict-aliasing -Wall -Wno-long-long -Wa,-mbig-obj ${CMAKE_CXX_FLAGS}")
	SET(CMAKE_C_FLAGS "-fno-strict-aliasing ${CMAKE_C_FLAGS}")
	ADD_DEFINITIONS( -U__STRICT_ANSI__ )
ELSE()

ENDIF()

IF ( IOS)
  IF (CMAKE_BUILD_TYPE STREQUAL "Debug")
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fembed-bitcode -Og")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fembed-bitcode -Og")
  ELSE()
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fembed-bitcode -O3")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fembed-bitcode -O3")
    # Experimental for pdb generation
  ENDIF()
ENDIF()

#
IF (BUILD_WITH_UBSAN)
  MESSAGE(STATUS "Undefined Behavior sanitizer enabled")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined,shift,shift-exponent,integer-divide-by-zero,unreachable,vla-bound,null,return,signed-integer-overflow,bounds,float-divide-by-zero,float-cast-overflow,nonnull-attribute,returns-nonnull-attribute,bool,enum,vptr,pointer-overflow,builtin -fno-sanitize-recover=all")
  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=undefined,shift,shift-exponent,integer-divide-by-zero,unreachable,vla-bound,null,return,signed-integer-overflow,bounds,float-divide-by-zero,float-cast-overflow,nonnull-attribute,returns-nonnull-attribute,bool,enum,vptr,pointer-overflow,builtin -fno-sanitize-recover=all")
ENDIF()

#
IF (BUILD_WITH_ASAN)
  MESSAGE(STATUS "AddressSanitizer enabled")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address")
ENDIF()


# Set C++ language version required for the project.
IF( CMAKE_COMPILER_IS_GNUCXX )
	SET(LIBSTDC++_LIBRARIES -std=c++11)
ENDIF( CMAKE_COMPILER_IS_GNUCXX )

# Cache these to allow the user to override them manually.
SET( FRAGVIEW_LIB_INSTALL_DIR "lib" CACHE STRING
		"Path the built library files are installed to." )
SET( FRAGVIEW_INCLUDE_INSTALL_DIR "fragview-core" CACHE STRING
		"Path the header files are installed to." )
SET( FRAGVIEW_BIN_INSTALL_DIR "bin" CACHE STRING
		"Path the tool executables are installed to." )

# Find all required libaries for the program.
FIND_PACKAGE(ZLIB)
FIND_PACKAGE(Git)
FIND_PACKAGE(Backtrace)
FIND_PACKAGE(PkgConfig)
FIND_PACKAGE(OpenSSL)
FIND_PACKAGE(CUDA)
IF( UNIX )
  # Use GNUInstallDirs for Unix predefined directories
  INCLUDE(GNUInstallDirs)
ENDIF()

IF(CUDA_FOUND)

ELSE()

ENDIF()

# Find and include libxml2 for supporting configuration.
FIND_PACKAGE(LibXml2)
IF ( LIBXML2_FOUND )
	MESSAGE(STATUS "Using xml2 version ${LIBXML2_VERSION_STRING}.")
	INCLUDE_DIRECTORIES(${LIBXML2_INCLUDE_DIR})
ELSE()

ENDIF()

IF(PKG_CONFIG_FOUND)
	MESSAGE(STATUS "Found pgk-config: ${PKG_CONFIG_EXECUTABLE} -- version ${PKG_CONFIG_VERSION_STRING}.")
	# Find library and compiling options.
	#TODO add logic for handling if any of the pkg fails.
	PKG_CHECK_MODULES(JSONC REQUIRED json-c)
	PKG_CHECK_MODULES(SDL2 REQUIRED sdl2)
	PKG_CHECK_MODULES(AVFORMAT REQUIRED libavformat)
	PKG_CHECK_MODULES(AVCODEC REQUIRED libavcodec)
	PKG_CHECK_MODULES(AVUTIL REQUIRED libavutil)
	PKG_CHECK_MODULES(SWSCALE REQUIRED libswscale)
	PKG_CHECK_MODULES(ASSIMP REQUIRED assimp)
	PKG_CHECK_MODULES(ZIP REQUIRED libzip)
ELSE()
	# TODO add logic for handling if pkg-config not available.
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

IF(OPENSSL_FOUND)
	MESSAGE(STATUS "backtrace found: ${OPENSSL_LIBRARIES} -- ${OPENSSL_VERSION}")
	INCLUDE_DIRECTORIES(${OPENSSL_INCLUDE_DIR})
ELSE()

ENDIF()

#
FIND_PACKAGE(Freetype)
IF(FREETYPE_FOUND)
	MESSAGE(STATUS "Using freetype version ${FREETYPE_VERSION_STRING}.")
	INCLUDE_DIRECTORIES(${FREETYPE_INCLUDE_DIRS})
ELSE()
	# Attempt to find it manually.
ENDIF()

# Inlucde external resources.
INCLUDE(${CMAKE_CURRENT_SOURCE_DIR}/extern/CMakeLists.txt)

IF(BUILD_WITH_EXTERNAL_PROJECT)

	# Git must be avaiable on the system for using the external projects.
	IF(NOT GIT_FOUND)
		MESSAGE(FATAL_ERROR "Require Git for loading external projects.")
	ENDIF()
	INCLUDE(ExternalProject)
	SET_PROPERTY(DIRECTORY PROPERTY EP_STEP_TARGETS build)
# Download the task-schedular library.
	SET(TASKSCH_ROOT ${CMAKE_CURRENT_BINARY_DIR}/deps/task-sch)
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
			COMMENT "Building task-schedular."
			LOG_DOWNLOAD ON)
	# Include tasksch headers.
	ADD_LIBRARY(taskSch SHARED IMPORTED)
	ADD_DEPENDENCIES(taskSch tasksch-external)
	SET_TARGET_PROPERTIES(taskSch PROPERTIES
			IMPORTED_LOCATION "${TASKSCH_LIB_DIR}/libtaskSch.so"
			INTERFACE_INCLUDE_DIRECTORIES "${TASKSCH_INCLUDE_DIR}")
	INCLUDE_DIRECTORIES(${TASKSCH_INCLUDE_DIR})

	# Download the hpm library.
	SET(HPM_ROOT ${CMAKE_CURRENT_BINARY_DIR}/deps/hpm)
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
			CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR> -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
			STEP_TARGETS build
			COMMENT "Building Hpm."
			LOG_DOWNLOAD ON)
	# Include HPM headers.
	ADD_LIBRARY(hpm SHARED IMPORTED)
	ADD_DEPENDENCIES(hpm hpm-external)
	SET_TARGET_PROPERTIES(hpm PROPERTIES
			IMPORTED_LOCATION "${HPM_LIB_DIR}/libhpm.so"
			INTERFACE_INCLUDE_DIRECTORIES "${HPM_INCLUDE_DIR}")
	INCLUDE_DIRECTORIES(${HPM_INCLUDE_DIR})

	# Download the HPMCPP library.
	SET(HPMCPP_ROOT ${CMAKE_CURRENT_BINARY_DIR}/deps/hpmcpp)
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
			CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>  -DBUILD_WITH_EXTERNAL_PROJECT=OFF -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_CXX_FLAGS="-I${HPM_INCLUDE_DIR}"
			STEP_TARGETS hpm-external build
			COMMENT "Building HPM-CPP"
			LOG_DOWNLOAD ON)
	# Include HPMCPP headers.
	ADD_LIBRARY(hpmcpp SHARED IMPORTED)
	#TARGET_LINK_DIRECTORIES(hpmcpp BEFORE INTERFACE ${HPM_LIB_DIR}/)
	ADD_DEPENDENCIES(hpmcpp hpm hpmcpp-external)
	SET_TARGET_PROPERTIES(hpmcpp PROPERTIES
			IMPORTED_LOCATION "${HPMCPP_LIB_DIR}/libhpmcpp.so"
			INTERFACE_INCLUDE_DIRECTORIES "${HPMCPP_INCLUDE_DIR}")
	SET_TARGET_PROPERTIES(hpmcpp-external PROPERTIES
			INTERFACE_INCLUDE_DIRECTORIES ${HPM_INCLUDE_DIR}
			INCLUDE_DIRECTORIES ${HPM_INCLUDE_DIR}
			LINK_DIRECTORIES ${HPM_LIB_DIR})
	INCLUDE_DIRECTORIES(${HPMCPP_INCLUDE_DIR})

ENDIF()


#TODO relocate to the core.
OPTION(BUILD_WITH_SDL_WINDOW "Use SDL for window mangement." ON)

# Define all file lists.
FILE(GLOB SOURCE_FILES  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/src/audio/*.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/src/physic/*.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/src/scene/*.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/src/scene/subgraph/*.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/src/renderpipeline/*.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/src/renderer/*.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/src/exception/*.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/src/utils/*.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/src/core/*.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/src/core/io/*.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/src/core/Scheduler/*.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/src/video/*.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/src/shadermodel/*.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/src/shaders/*.cpp)
FILE(GLOB SOURCE_MAIN_FILES client/src/main.cpp)
FILE(GLOB HEADER_FILES  ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
		${CMAKE_CURRENT_SOURCE_DIR}/include/Animation/*.h
		${CMAKE_CURRENT_SOURCE_DIR}/include/Core/*.h
		${CMAKE_CURRENT_SOURCE_DIR}/include/Exception/*.h
		${CMAKE_CURRENT_SOURCE_DIR}/include/Renderer/*.h
		${CMAKE_CURRENT_SOURCE_DIR}/include/RenderPipeline/*.h
		${CMAKE_CURRENT_SOURCE_DIR}/include/Video/*.h
		${CMAKE_CURRENT_SOURCE_DIR}/include/Utils/*.h)
# Public headers - subset of header files.
FILE(GLOB DEVELOPMENT_HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
									${CMAKE_CURRENT_SOURCE_DIR}/include/Core/*.h
									${CMAKE_CURRENT_SOURCE_DIR}/include/Core/IO/*.h
									${CMAKE_CURRENT_SOURCE_DIR}/include/Renderer/*.h
									${CMAKE_CURRENT_SOURCE_DIR}/include/Utils/*.h
									${CMAKE_CURRENT_SOURCE_DIR}/include/Exception/*.h)
#
FILE(GLOB SAMPLE_GLSL_FILES ${CMAKE_CURRENT_SOURCE_DIR}/samples/glsl/* )
FILE(GLOB SAMPLE_HLSL_FILES ${CMAKE_CURRENT_SOURCE_DIR}/samples/hlsl/* )
FILE(GLOB SAMPLE_SPIRV_FILES ${CMAKE_CURRENT_SOURCE_DIR}/samples/spirv/* )
FILE(GLOB SAMPLE_CLC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/samples/clc/* )
FILE(GLOB SAMPLE_SHADER_GLSL_FILES ${CMAKE_CURRENT_SOURCE_DIR}/shaders/glsl/* )
FILE(GLOB SAMPLE_SHADER_SPIRV_FILES ${CMAKE_CURRENT_SOURCE_DIR}/shaders/spriv/* )

#TODO Add platform source code
IF(UNIX)

ELSEIF(APPLE)

ELSEIF(CYGWIN)

ENDIF()

# #${XATLAS_SOURCE} ${NANOSVG_SOURCE}
# # Core library for adding support for plugin.
# ADD_LIBRARY(fragview-core ${SOURCE_FILES} ${HEADER_FILES}
#  							${OPEN_SIMPLEX_NOISE_SOURCE}  ${PCG_C_BASIC_SOURCE}
# 							${RECASTNAVIGATION_SOURCE} ${POLYPARITION_SOURCE} ${KISS_FFT_SOURCE}
# 							${MISC_SOURCE})
# TARGET_LINK_LIBRARIES(fragview-core ${SDL2_LIBRARIES} ${ZLIB_LIBRARIES} ${LIBXML2_LIBRARIES} ${Backtrace_LIBRARIES} ${FREETYPE_LIBRARIES}
# 		${ZIP_LIBRARIES} freeimage m dl taskSch fswatch ${JSONC_LIBRARIES} yaml hpmcpp hpm ${ASSIMP_LIBRARIES} ${OPENSSL_CRYPTO_LIBRARY}
# 		${AVFORMAT_LIBRARIES} ${AVCODEC_LIBRARIES} ${SWSCALE_LIBRARIES} )
# ADD_DEPENDENCIES(fragview-core taskSch hpm hpmcpp)
# TARGET_COMPILE_DEFINITIONS(fragview-core PRIVATE FRAGVIEW_CORE_INTERNAL_IMP=1)

# #
# SET_TARGET_PROPERTIES(fragview-core PROPERTIES
# 		COMPILE_FLAGS "${JSONC_CFLAGS_OTHER} ${SDL2_CFLAGS_OTHER} ${AVFORMAT_CFLAGS_OTHER} ${AVCODEC_CFLAGS_OTHER}
# 		${AVUTIL_CFLAGS_OTHER} ${SWSCALE_CFLAGS_OTHER} ${ASSIMP_CFLAGS_OTHER} ${ZIP_CFLAGS_OTHER}")
# TARGET_INCLUDE_DIRECTORIES(fragview-core PRIVATE ${SDL2_INCLUDE_DIRS} ${ZIP_INCLUDE_DIRS} ${JSONC_INCLUDE_DIRS}
# 													 ${NANOSVG_INCLUDE_DIRS} ${RECASTNAVIGATION_INCLUDE_DIRS} ${NANOSVG_INCLUDE_DIRS}
# 													 ${OPEN_SIMPLEX_NOISE_INCLUDE_DIRS} ${PCG_C_BASIC_INCLUDE_DIRS} ${XATLAS_INCLUDE_DIRS}
# 													 ${KISS_FFT_INCLUDE_DIRS} ${MISC_INCLUDE_DIRS}
# 										PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)

# Build frag core.
IF(BUILD_WITH_CORE)
	ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/frag-core)
ENDIF()

# Build frag engine.
IF(BUILD_WITH_ENGINE)
	ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/frag-engine)
ENDIF()

# Build frag editor.
IF(NOT ANDROID)
	IF(BUILD_WITH_EDITOR)
		ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/editor/)
	ENDIF()
ENDIF()

# Client
IF(BUILD_WITH_CLIENT)
	ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/client/)
ENDIF()

# Rendering interfaces.
IF(BUILD_EXTERNAL_RENDERER)
	ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/frag-core/src/renderer/opengl/)
	ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/frag-core/src/renderer/directx/)
	ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/frag-core/src/renderer/vulkan/)
	#TODO changed to a compute base class and module extension.
	ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/frag-core/src/renderer/opencl/)
ENDIF()

IF(BUILD_EXTERNAL_AUDIO)
	ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/frag-core/src/audio/openal/)
	ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/frag-core/src/audio/fmod/)
ENDIF()

IF(BUILD_EXTERNAL_PHYSIC)
	ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/frag-core/src/physic/bullet/)
#	ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/src/physic/bullet3/)
	ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/frag-core/src/physic/physx/)
		#TODO moved to the PVEngine
#	ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/src/physic/rpc/)
ENDIF()

# Plugins.
IF(BUILD_WITH_EXTERNAL_PLUGINS)
	ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/plugins/)
ENDIF()


#TODO resolve and add options and etc.
IF(Android)
	MESSAGE(STATUS "Hello from Android build!")
	ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/platforms/android/)
ENDIF()

IF(${CMAKE_SYSTEM_NAME} MATCHES "Tmp")
	ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/platforms/windows/)
ENDIF()
IF(${CMAKE_SYSTEM_NAME} MATCHES "Tmp")
	ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/platforms/uwp/)
ENDIF()
IF(UNIX)
	ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/platforms/unix/)
ENDIF()

# Testing.
IF(NOT ANDROID)
	IF(BUILD_WITH_TEST)
		ENABLE_TESTING()
		ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/test/)
	ENDIF(BUILD_WITH_TEST)
ENDIF()

#TODO control it from main cmake file.
IF(BUILD_WITH_SAMPLES)
	#ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/test/examples)
ENDIF()

# Generate documentations.
FIND_PACKAGE(Doxygen)
IF(DOXYGEN_FOUND)
	MESSAGE(STATUS "Doxygen found: ${DOXYGEN_EXECUTABLE} -- ${DOXYGEN_VERSION}")
	IF(BUILD_WITH_DOCS)
		ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/docs/)
	ENDIF(BUILD_WITH_DOCS)
ENDIF()

# Generate package configuration file.


CONFIGURE_FILE( "${PROJECT_SOURCE_DIR}/fragengine.pc.in" "${PROJECT_BINARY_DIR}/fragengine.pc" @ONLY )

# Only UNIX systems.
IF( UNIX )
	# Use GNUInstallDirs for Unix predefined directories
	INCLUDE(GNUInstallDirs)

	# 
	Find_PACKAGE(UnixCommands REQUIRED)

	FIND_PROGRAM(GLSLLANGVALIDATOR glslangValidator)
	FIND_PROGRAM(SPIRVDIS spirv-dis)
	FIND_PROGRAM(SPIRVAS spirv-as)
	FIND_PROGRAM(SPIRVREMAP spirv-remap)
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
					-u:time:10 -G450 ${glslFile} -o ${CMAKE_CURRENT_SOURCE_DIR}/samples/spirv/)
		ENDFOREACH()

		# Create default shader
		ADD_CUSTOM_TARGET(display-spirv
				COMMENT "Creating spirv shader from the display shader.")
		#ADD_DEPENDENCIES(fragview display-spirv)
		FOREACH(glslFile ${SAMPLE_SHADER_GLSL_FILES})
			ADD_CUSTOM_COMMAND(TARGET display-spirv PRE_BUILD
					COMMAND glslangValidator --entry-point main --auto-map-bindings --auto-map-locations --uniform-base 0 -G -d
					-u:time:10 ${glslFile} -o ${CMAKE_CURRENT_SOURCE_DIR}/)
		ENDFOREACH()

	ELSE()
		MESSAGE(WARNING "Could not find the glslangValidator program for creating spirv shaders.")
	ENDIF()

	FIND_PROGRAM(ZIP zip)

	IF(ZIP)
		MESSAGE(STATUS "zip found: ${ZIP}")

	ENDIF()
		# Install main icon image.
		ADD_DEFINITIONS(-DICON_LOCATION="/usr/share/fragview/")
		IF(BUILD_WITH_INSTALL)
		INSTALL( FILES ${CMAKE_CURRENT_SOURCE_DIR}/fragview.png DESTINATION /usr/share/fragview/ )

		# Install samples.
		INSTALL( FILES ${CMAKE_CURRENT_SOURCE_DIR}/fragview.desktop DESTINATION /usr/share/fragview/ )
		INSTALL( FILES ${SAMPLE_GLSL_FILES} DESTINATION /usr/share/fragview/samples/glsl )
		INSTALL( FILES ${SAMPLE_HLSL_FILES} DESTINATION /usr/share/fragview/samples/hlsl )
		INSTALL( FILES ${SAMPLE_SPIRV_FILES} DESTINATION /usr/share/fragview/samples/spriv )
		INSTALL( FILES ${SAMPLE_CLC_FILES} DESTINATION /usr/share/fragview/samples/clc )

		# Install scripts
		INSTALL( FILES ${CMAKE_CURRENT_SOURCE_DIR}/scripts/newshad.sh DESTINATION /usr/share/fragview/ )
	ENDIF()
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
			${CMAKE_CURRENT_SOURCE_DIR}/client
			${CMAKE_CURRENT_SOURCE_DIR}/editor
			${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt
			${CMAKE_CURRENT_SOURCE_DIR}/travis.yaml
			${CMAKE_CURRENT_SOURCE_DIR}/fragview.desktop
			client/fragview.1
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


IF(BUILD_WITH_INSTALL)
	# #TODO add logic for installing only the development headers.
	# INSTALL(TARGETS fragview-core LIBRARY DESTINATION lib)
	# #INSTALL(FILES ${DEVELOPMENT_HEADER_FILES} DESTINATION include/fragview-core)

	# INSTALL(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include" # source directory
	# 		DESTINATION "fragview" # target directory
	# 		FILES_MATCHING # install only matched files
	# 		PATTERN "*.h" # select header files
	# 		)

	#
	# INSTALL( FILES "${PROJECT_BINARY_DIR}/fragcore.pc" DESTINATION ${FRAGCORE_LIB_INSTALL_DIR}/pkgconfig/ COMPONENT ${LIBFRAGCORE-DEV_COMPONENT})
	# INSTALL( FILES "${PROJECT_BINARY_DIR}/fragengine.pc" DESTINATION ${FRAGCORE_LIB_INSTALL_DIR}/pkgconfig/ COMPONENT ${LIBFRAGENGINE-DEV_COMPONENT})

	# TODO add some logic for determine if exists.
	IF(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/images/icons AND UNIX)
		FOREACH(size 16 24 32 48 64 128 256)
			INSTALL( FILES ${CMAKE_CURRENT_SOURCE_DIR}/images/icons/${size}x${size}/fragview.png DESTINATION /usr/share/icons/hicolor/${size}x${size}/apps/
					RENAME fragview.png)
			INSTALL( FILES ${CMAKE_CURRENT_SOURCE_DIR}/images/icons/${size}x${size}/fragview.png DESTINATION /usr/share/icons/hicolor/${size}x${size}/mimetypes/
					RENAME application-fragview-doc.png)
		ENDFOREACH()
	ENDIF()

ENDIF()

FIND_PACKAGE(PythonInterp)
IF(PYTHONINTERP_FOUND)
	#TODO relocate to the fragengine and editor.
	ADD_CUSTOM_TARGET( compile-shader
			COMMENT "Creating header and source file for display shaders."
			COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/utils/glsl2CString.py ${CMAKE_CURRENT_SOURCE_DIR}/shaders/glsl/
			DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/utils/glsl2CString.py)
	#ADD_DEPENDENCIES(fragview compile-shader)
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

IF ( BUILD_WITH_INSTALL )
	IF(CMAKE_CPACK_COMMAND AND UNIX AND BUILD_OPT_BUILD_PACKAGES)
		# Packing information
		SET(CPACK_PACKAGE_NAME                    "frag{FRAG_VERSION_MAJOR}.{VERSION_MINOR}")
		SET(CPACK_PACKAGE_CONTACT "" CACHE STRING "Package maintainer and PGP signer.")
		SET(CPACK_PACKAGE_VENDOR                  "https://github.com/voldien/fragengine")
		SET(CPACK_PACKAGE_DISPLAY_NAME            "Frag ${VERSION}")
		SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY     " -  ${VERSION}")
		SET(CPACK_PACKAGE_VERSION                 "${VERSION}.${PACKAGE_VERSION}" )
		SET(CPACK_PACKAGE_VERSION_MAJOR           "${VERSION_MAJOR}")
		SET(CPACK_PACKAGE_VERSION_MINOR           "${VERSION_MINOR}")
		SET(CPACK_PACKAGE_VERSION_PATCH           "${VERSION_PATCH}")
		SET(CPACK_PACKAGE_INSTALL_DIRECTORY       "frag${VERSION_MAJOR}.${VERSION_MINOR}")
		SET(CPACK_RESOURCE_FILE_LICENSE           "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")

		STRING(TOUPPER ${LIBFRAGCORE_COMPONENT}     "LIBFRAGCORE_COMPONENT_UPPER")
		STRING(TOUPPER ${LIBFRAGCORE-DEV_COMPONENT} "LIBFRAGCORE-DEV_COMPONENT_UPPER")

		#
		SET(CPACK_COMPONENT_FRAGCORE-BIN_DISPLAY_NAME                       "tools")
		SET(CPACK_COMPONENT_FRAGCORE-BIN_DEPENDS                            "${LIBFRAGCORE_COMPONENT}" )
		SET(CPACK_COMPOENTT_${LIBFRAGENGINE_COMPONENT_UPPER}_DISPLAY_NAME "")
		SET(CPACK_COMPOENTT_${LIBFRAGENGINE-DEV_COMPONENT_UPPER}_DISPLAY_NAME "")
		SET(CPACK_COMPONENT_${LIBFRAGENGINE-DEV_COMPONENT_UPPER}_DEPENDS $    "{LIBFRAGCORE_COMPONENT}" )
		SET(CPACK_COMPOENTT_${LIBFRAGENGINE-DEV_COMPONENT_UPPER}_DISPLAY_NAME "")
		SET(CPACK_COMPONENT_${LIBFRAGCORE_COMPONENT_UPPER}_DISPLAY_NAME     "libraries")
		SET(CPACK_COMPONENT_${LIBFRAGCORE-DEV_COMPONENT_UPPER}_DISPLAY_NAME "common headers and installs")
		SET(CPACK_COMPONENT_${LIBFRAGCORE-DEV_COMPONENT_UPPER}_DEPENDS $    "{LIBFRAGCORE_COMPONENT}" )
		SET(CPACK_COMPONENT_LIBFRAGCORE-DEV_DISPLAY_NAME                       "${CPACK_COMPONENT_${LIBFRAGCORE-DEV_COMPONENT}_DISPLAY_NAME}" )
		SET(CPACK_COMPONENT_LIBFRAGCORE-DEV_DEPENDS                            "${LIBFRAGCORE-DEV_COMPONENT}" )
		SET(CPACK_DEBIAN_BUILD_DEPENDS debhelper cmake zlib1g-dev pkg-config)

		# debian
		SET(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
		SET(CPACK_DEBIAN_CMAKE_OPTIONS    "")
		SET(CPACK_DEBIAN_PACKAGE_SECTION  "libs" )
		SET(CPACK_DEBIAN_PACKAGE_DEPENDS  "${CPACK_COMPONENTS_ALL}")
		SET(CPACK_DEBIAN_PACKAGE_SUGGESTS)
		SET(cPACK_DEBIAN_PACKAGE_NAME     "fragengine")
		SET(CPACK_DEBIAN_PACKAGE_REMOVE_SOURCE_FILES build doc obj samples packaging)
		SET(CPACK_DEBIAN_PACKAGE_SOURCE_COPY svn export --force)
		SET(CPACK_DEBIAN_CHANGELOG)
		execute_process(COMMAND lsb_release -is
			OUTPUT_VARIABLE _lsb_distribution OUTPUT_STRIP_TRAILING_WHITESPACE
			RESULT_VARIABLE _lsb_release_failed)
		SET(CPACK_DEBIAN_DISTRIBUTION_NAME ${_lsb_distribution} CACHE STRING "Name of the distrubiton")
		STRING(TOLOWER ${CPACK_DEBIAN_DISTRIBUTION_NAME} CPACK_DEBIAN_DISTRIBUTION_NAME)
		IF( ${CPACK_DEBIAN_DISTRIBUTION_NAME} STREQUAL "ubuntu" )
			SET(CPACK_DEBIAN_DISTRIBUTION_RELEASES lucid maverick natty oneiric precise CACHE STRING "Release code-names of the distrubiton release")
		ENDIF()
		SET(DPUT_HOST "" CACHE STRING "PPA repository to upload the debian sources")
		INCLUDE(CPack)
		INCLUDE(DebSourcePPA)
	ENDIF()
ENDIF()

# Final verbose message status.
MESSAGE(STATUS "")
MESSAGE(STATUS "These are the configured paths:")
MESSAGE(STATUS "  PREFIX: ${CMAKE_INSTALL_PREFIX}")
MESSAGE(STATUS "  LIB_DIR: ${LIB_DIR}")
MESSAGE(STATUS "  RENDERING_DIR: ${PLUGIN_DIR}")
MESSAGE(STATUS "  BIN_DIR: ${BIN_DIR}")
MESSAGE(STATUS "  DATA_DIR: ${DATA_DIR}")
MESSAGE(STATUS "  MAN_DIR: ${MAN_DIR}")
MESSAGE(STATUS "  DOC_DIR: ${DOC_DIR}")
MESSAGE(STATUS "  ICON_DIR: ${ICON_DIR}")
MESSAGE(STATUS "  SVG_DIR: ${SVG_DIR}")
MESSAGE(STATUS "  MENU_DIR: ${MENU_DIR}")
MESSAGE(STATUS "")
MESSAGE(STATUS "Options:")
MESSAGE(STATUS "  LAYOUT: ${LAYOUT}")
MESSAGE(STATUS "")
MESSAGE(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
MESSAGE(STATUS "Target bitness: ${CMAKE_SIZEOF_VOID_P}*8")
MESSAGE(STATUS "")
