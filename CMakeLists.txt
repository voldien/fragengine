CMAKE_MINIMUM_REQUIRED(VERSION 3.7.2)
PROJECT(fragview CXX)

# Build shared/dynamic library option
OPTION(BUILD_SHARED_LIBS "Build package with shared libraries." ON)
IF(NOT BUILD_SHARED_LIBS)
    SET(CMAKE_EXE_LINKER_FLAGS "-static")
    SET(LINK_SEARCH_START_STATIC TRUE)
ENDIF(NOT BUILD_SHARED_LIBS)

# Set version of the project.
SET(VERSION_MAJOR 0)
SET(VERSION_MINOR 6)
SET(VERSION_REVISION 0)
SET(VERSION_STATE a)
SET(VERSION ${VERSION_MAJOR}.${VERSION_MINOR}${VERSION_STATE}${VERSION_REVISION} )
SET(PROJECT_VERSION "${VERSION}")

# Set predefined macro for version.
ADD_DEFINITIONS(-DFV_VERSION="${VERSION}")

# GCC compiler flag options.
IF((CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX) AND NOT CMAKE_COMPILER_IS_MINGW)
    IF (BUILD_SHARED_LIBS AND CMAKE_SIZEOF_VOID_P EQUAL 8) # -fPIC is only required
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
    ENDIF()

    ADD_DEFINITIONS(-Wall -w -fpermissive)
    ADD_DEFINITIONS()
    IF (CMAKE_BUILD_TYPE STREQUAL "Release")
        MESSAGE(STATUS "Compile for release.")
        ADD_DEFINITIONS(-DNDEBUG)
        ADD_DEFINITIONS(-O2)
        SET(CMAKE_RELEASE TRUE)
        SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -s")
    ELSE()
        MESSAGE(STATUS "Compile for debug.")
        ADD_DEFINITIONS(-D_DEBUG)
        ADD_DEFINITIONS(-g3 -O0)
        SET(CMAKE_DEBUG TRUE)
        ADD_DEFINITIONS(-D_GLIBCXX_ASSERTIONS)
    ENDIF()

ENDIF()

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include/)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include/)

# Set c++ language version required for the project.
IF( CMAKE_COMPILER_IS_GNUCXX )
    SET(LIBSTDC++_LIBRARIES -std=c++11)
ENDIF( CMAKE_COMPILER_IS_GNUCXX )

# Find all required libaries for the program.
FIND_PACKAGE(ZLIB REQUIRED)
FIND_PACKAGE(Git)

# Find and include libxml2 for supporting configuration.
INCLUDE(FindLibXml2)
IF ( LIBXML2_FOUND )
    MESSAGE(STATUS "Using xml2 version ${LIBXML2_VERSION_STRING}.")
    INCLUDE_DIRECTORIES(${LIBXML2_INCLUDE_DIR})
ENDIF()

# Download dependices
IF(GIT_FOUND)
    MESSAGE(STATUS "git found: ${GIT_EXECUTABLE} -- ${GIT_VERSION_STRING}")
ENDIF()

INCLUDE(ExternalProject)
SET_PROPERTY(DIRECTORY PROPERTY EP_STEP_TARGETS build)

# Download the task-schedular library.
SET(TASKSCH_ROOT ${CMAKE_BINARY_DIR}/deps/task-sch)
SET(TASKSCH_LIB_DIR ${TASKSCH_ROOT}/lib)
SET(TASKSCH_INCLUDE_DIR ${TASKSCH_ROOT}/include)

#        CONFIGURE_COMMAND cmake .
#        BUILD_COMMAND make
ExternalProject_Add(tasksch-external
        PREFIX ${TASKSCH_ROOT}
        GIT_REPOSITORY "https://github.com/voldien/task-scheduler.git"
        GIT_TAG "master"
        UPDATE_COMMAND ""
        PATCH_COMMAND ""
        SOURCE_DIR ${TASKSCH_ROOT}/src/tasksch
        BINARY_DIR ${TASKSCH_ROOT}/src/tasksch-build
        INSTALL_DIR ${TASKSCH_ROOT}
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
        STEP_TARGETS build
        COMMENT "Building taskschedular"
        LOG_DOWNLOAD ON)
# Include tasksch headers.
ADD_LIBRARY(taskSch SHARED IMPORTED)
SET_TARGET_PROPERTIES(taskSch PROPERTIES
        IMPORTED_LOCATION "${TASKSCH_LIB_DIR}/libtaskSch.so"
        INTERFACE_INCLUDE_DIRECTORIES "${TASKSCH_INCLUDE_DIR}")
INCLUDE_DIRECTORIES(${TASKSCH_INCLUDE_DIR})

# Include library include directories.
INCLUDE_DIRECTORIES(${SDL_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${ZLIB_INCLUDE_DIRS})

# Define all file lists.
FILE(GLOB SOURCE_FILES  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
                        ${CMAKE_CURRENT_SOURCE_DIR}/src/scene/*.cpp
                        ${CMAKE_CURRENT_SOURCE_DIR}/src/utils/*.cpp
                        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/*.cpp
                        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/io/*.cpp
                        ${CMAKE_CURRENT_SOURCE_DIR}/src/shadermodel/*.cpp
                        ${CMAKE_CURRENT_SOURCE_DIR}/src/shaders/*.cpp)
FILE(GLOB SOURCE_MAIN_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
FILE(GLOB HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
FILE(GLOB SAMPLE_GLSL_FILES ${CMAKE_CURRENT_SOURCE_DIR}/samples/glsl/* )
FILE(GLOB SAMPLE_HLSL_FILES ${CMAKE_CURRENT_SOURCE_DIR}/samples/hlsl/* )
FILE(GLOB SAMPLE_SPIRV_FILES ${CMAKE_CURRENT_SOURCE_DIR}/samples/spirv/* )
FILE(GLOB SAMPLE_CLC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/samples/clc/* )

# Core library for adding support for plugin.
ADD_LIBRARY(fragview-core ${SOURCE_FILES} ${HEADER_FILES} src/RendererWindow_SDL2.cpp)
TARGET_LINK_LIBRARIES(fragview-core  -lSDL2  ${ZLIB_LIBRARIES} ${LIBXML2_LIBRARIES} -lzip -lfreeimage -lm -ldl taskSch -lfswatch)
ADD_DEPENDENCIES(fragview-core tasksch-external)
INSTALL(TARGETS fragview-core DESTINATION lib)

# Main executable.
ADD_EXECUTABLE(fragview  ${SOURCE_MAIN_FILES} ${HEADER_FILES})
TARGET_LINK_LIBRARIES(fragview fragview-core)
INSTALL(TARGETS fragview DESTINATION bin)

# Rendering interfaces.
ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/src/renderer/opengl/)
ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/src/renderer/directx/)
ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/src/renderer/vulkan/)
ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/src/renderer/opencl/)

# Testing.
ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/test/)

# Only UNIX systems.
IF( UNIX )
#FindUnixCommands.cmake

    # Create spriv samples.
#    ADD_CUSTOM_TARGET(samples-spirv
#            COMMENT "Creating spirv shader from the display shader."
#            COMMAND glslangValidator --entry-point main --auto-map-bindings --auto-map-locations --uniform-base 0
#            -u:time:10 --client opengl100 -V -G450 ${CMAKE_CURRENT_SOURCE_DIR}/samples/glsl/guassian.frag -o ${CMAKE_CURRENT_SOURCE_DIR}/samples/spirv/guassian.spv)
#    ADD_DEPENDENCIES(fragview samples-spirv)

    # Create default shader
    ADD_CUSTOM_TARGET(display-spirv
            COMMENT "Creating spirv shader from the display shader."
            COMMAND glslangValidator --entry-point main -V ${CMAKE_CURRENT_SOURCE_DIR}/shaders/spirv/display.frag --vn vertex_display -o ${CMAKE_CURRENT_SOURCE_DIR}/
            COMMAND glslangValidator --entry-point main -V ${CMAKE_CURRENT_SOURCE_DIR}/shaders/spirv/display.vert --vn fragment_display -o ${CMAKE_CURRENT_SOURCE_DIR}/ ) # -o ${CMAKE_CURRENT_SOURCE_DIR}/shaders/spirv/*)
    
    ADD_DEPENDENCIES(fragview display-spirv)

    INSTALL( FILES ${SHADERZIPFILE} DESTINATION /usr/share/fragview )

    # Install bash autocomplete.
    INSTALL( FILES ${CMAKE_CURRENT_SOURCE_DIR}/bashcomplete/fragview DESTINATION /usr/share/bash-completion/completions/ )

    # Install
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
    INSTALL( FILES ${CMAKE_CURRENT_SOURCE_DIR}/fragview.1 DESTINATION /usr/share/man/man1/)

    # Create distribution tarball.
    SET( TARGETDIR "${PROJECT_NAME}-${VERSION}")
    ADD_CUSTOM_TARGET(	distribution
            COMMENT "Creating distrubtion file."
            COMMAND mkdir -p ${TARGETDIR}
            COMMAND cp -r   ${CMAKE_CURRENT_SOURCE_DIR}/src
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
            COMMAND tar cf - ${TARGETDIR} | gzip -c > ${TARGETDIR}.tar.gz
            COMMAND rm -r ${TARGETDIR} )

    ADD_CUSTOM_TARGET(install-desktop
            COMMENT "Validating and installing desktop entry."
            COMMAND desktop-file-validate ${CMAKE_CURRENT_SOURCE_DIR}/fragview.desktop
            COMMAND desktop-file-install --rebuild-mime-info-cache ${CMAKE_CURRENT_SOURCE_DIR}/fragview.desktop
            COMMAND update-desktop-database )

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
            COMMAND convert ${CMAKE_CURRENT_SOURCE_DIR}/fragview.png -resize 1024x1024 ${CMAKE_CURRENT_SOURCE_DIR}/images/icons/1024x1024/fragview.png )

ELSEIF(WIN32)

ELSE()

ENDIF()

# TODO add some logic for determine if exists.
FOREACH(size 16 24 32 48 64 128 256)

    INSTALL( FILES ${CMAKE_CURRENT_SOURCE_DIR}/images/icons/${size}x${size}/fragview.png DESTINATION /usr/share/icons/hicolor/${size}x${size}/apps/
            RENAME fragview.png)
    INSTALL( FILES ${CMAKE_CURRENT_SOURCE_DIR}/images/icons/${size}x${size}/fragview.png DESTINATION /usr/share/icons/hicolor/${size}x${size}/mimetypes/
            RENAME application-fragview-doc.png)
ENDFOREACH()

FIND_PACKAGE(PythonInterp)
IF(PYTHONINTERP_FOUND)
    ADD_CUSTOM_TARGET( compile-shader
            COMMENT "Creating header and source file for display shaders."
            COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/utils/glsl2CString.py ${CMAKE_CURRENT_SOURCE_DIR}/shaders/glsl/
            DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/utils/glsl2CString.py)
    ADD_DEPENDENCIES(fragview compile-shader)
ENDIF()
