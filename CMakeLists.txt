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
SET(VERSION_MINOR 5)
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
    SET(LIBSTDC++_LIBRARIES -std=c++0x)
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
    # Download git dependices.
#    FILE(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/dep)
#    ADD_CUSTOM_TARGET(download_dependencies
#            COMMAND ${GIT_EXECUTABLE} clone https://github.com/voldien/task-scheduler.git ${CMAKE_CURRENT_SOURCE_DIR}/dep/task-scheduler
#            COMMAND ${GIT_EXECUTABLE} clone https://github.com/voldien/hpm.git ${CMAKE_CURRENT_SOURCE_DIR}/dep/hpm
#            COMMAND ${GIT_EXECUTABLE} clone https://github.com/voldien/hpmcpp.git ${CMAKE_CURRENT_SOURCE_DIR}/dep/hpmcpp
#            )
ENDIF()

# Include library include directories.
INCLUDE_DIRECTORIES(${SDL_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${ZLIB_INCLUDE_DIRS})

# Define all file lists.
FILE(GLOB SOURCE_FILES  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
                        ${CMAKE_CURRENT_SOURCE_DIR}/src/scene/*.cpp
                        ${CMAKE_CURRENT_SOURCE_DIR}/src/utils/*.cpp)
FILE(GLOB SOURCE_MAIN_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
FILE(GLOB HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
FILE(GLOB_RECURSE SAMPLE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/samples/* )

# Core library for adding support for plugin.
ADD_LIBRARY(fragview-core ${SOURCE_FILES} ${HEADER_FILES})
TARGET_LINK_LIBRARIES(fragview-core  -lSDL2  ${ZLIB_LIBRARIES} ${LIBXML2_LIBRARIES} -lzip -lfreeimage  -lm -ldl -ltaskSch -lfswatch)
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

INCLUDE(ExternalProject)
ExternalProject_Add(tasksch
        PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/deps/task-sch
        GIT_REPOSITORY "https://github.com/voldien/task-scheduler.git"
        GIT_TAG        "654870105b9e9b2bded3f54ff4b169ed9270e4c1"
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/deps
        CONFIGURE_COMMAND cmake .
        BUILD_COMMAND make
        COMMENT        "Building taskschedular")
ExternalProject_Add(hpmcpp
        PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/deps/hpmcpp
        GIT_REPOSITORY "https://github.com/voldien/hpmcpp.git"
        GIT_TAG        "master"
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/deps
        CONFIGURE_COMMAND cmake .
        BUILD_COMMAND make
        COMMENT        "Building HMPCPP")
ADD_DEPENDENCIES(fragview tasksch)

# Only UNIX systems.
IF( UNIX )

#    ADD_CUSTOM_TARGET(samples-spirv
#            COMMENT "Creating spirv shader from the display shader."
#            COMMAND glslangValidator --entry-point main --auto-map-bindings --auto-map-locations --uniform-base 0
#            -u:time:10 --client opengl100 -V -G450 ${CMAKE_CURRENT_SOURCE_DIR}/samples/glsl/guassian.frag -o ${CMAKE_CURRENT_SOURCE_DIR}/samples/spirv/guassian.spv)
#    ADD_DEPENDENCIES(fragview samples-spirv)

    ADD_CUSTOM_TARGET(display-spirv
            COMMENT "Creating spirv shader from the display shader."
            COMMAND glslangValidator --entry-point main -V ${CMAKE_CURRENT_SOURCE_DIR}/shaders/spirv/*.frag --vn vertex_display -o ${CMAKE_CURRENT_SOURCE_DIR}/
            COMMAND glslangValidator --entry-point main -V ${CMAKE_CURRENT_SOURCE_DIR}/shaders/spirv/*.vert --vn fragment_display -o ${CMAKE_CURRENT_SOURCE_DIR}/) # -o ${CMAKE_CURRENT_SOURCE_DIR}/shaders/spirv/*)
    
    ADD_DEPENDENCIES(fragview display-spirv)

    INSTALL( FILES ${SHADERZIPFILE} DESTINATION /usr/share/fragview )

    # Install bash autocomplete.
    INSTALL( FILES ${CMAKE_CURRENT_SOURCE_DIR}/bashcomplete/fragview DESTINATION /usr/share/bash-completion/completions/ )

    # Install
    ADD_DEFINITIONS(-DICON_LOCATION="/usr/share/fragview/")
    INSTALL( FILES ${CMAKE_CURRENT_SOURCE_DIR}/fragview.png DESTINATION /usr/share/fragview/ )

    #
    INSTALL( FILES ${CMAKE_CURRENT_SOURCE_DIR}/fragview.desktop DESTINATION /usr/share/fragview/ )
    INSTALL( FILES ${SAMPLE_FILES} DESTINATION /usr/share/fragview/samples )

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
                            ${CMAKE_CURRENT_SOURCE_DIR}/images
                            ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt
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
