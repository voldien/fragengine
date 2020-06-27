
FIND_PACKAGE(Git REQUIRED)
IF(GIT_FOUND)
	# Download all the sources.
	INCLUDE(ExternalProject)
	SET_PROPERTY(DIRECTORY PROPERTY EP_STEP_TARGETS build)

	# Download the task-schedular library.
	SET(SVGNANO_ROOT ${CMAKE_CURRENT_BINARY_DIR}/deps/nanosvg)
	SET(SVGNANO_LIB_DIR ${SVGNANO_ROOT}/lib)

	ExternalProject_Add(nanosvg-external
			PREFIX ${SVGNANO_ROOT}
			GIT_REPOSITORY "https://github.com/memononen/nanosvg"
			GIT_TAG "master"
			UPDATE_COMMAND ""
			PATCH_COMMAND ""
			SOURCE_DIR ${SVGNANO_ROOT}/src/nanosvg
			INSTALL_DIR ${SVGNANO_ROOT}
			STEP_TARGETS build
			COMMENT "Building svg-nano"
			LOG_DOWNLOAD ON)

	SET(SVGNANO_INCLUDE_DIR ${SVGNANO_ROOT}/src/nanosvg/src)
	FILE(GLOB NANOSVG_HEADERS ${SVGNANO_INCLUDE_DIR}/*.h )

	
ELSE()
	MESSAGE(FATAL_ERROR "Require Git for loading external projects.")
ENDIF()