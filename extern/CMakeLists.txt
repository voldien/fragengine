
FIND_PACKAGE(Git REQUIRED)
IF(GIT_FOUND)
	# Download all the sources.
	INCLUDE(ExternalProject)
	SET_PROPERTY(DIRECTORY PROPERTY EP_STEP_TARGETS build)

	# Download the nano-svg  library.
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
			BUILD_IN_SOURCE 0
			COMMENT "Building svg-nano"
			LOG_DOWNLOAD ON)
	SET(SVGNANO_INCLUDE_DIR ${SVGNANO_ROOT}/src/nanosvg/src)
	FILE(GLOB NANOSVG_HEADERS ${SVGNANO_INCLUDE_DIR}/*.h )

	# Download the polypartition library.
	SET(POLYPARTITION_ROOT ${CMAKE_CURRENT_BINARY_DIR}/deps/polypartition)
	SET(POLYPARTITION_LIB_DIR ${POLYPARTITION_ROOT}/lib)

	ExternalProject_Add(polypartition-external
			PREFIX ${POLYPARTITION_ROOT}
			GIT_REPOSITORY "https://github.com/ivanfratric/polypartition"
			GIT_TAG "master"
			UPDATE_COMMAND ""
			PATCH_COMMAND ""
			SOURCE_DIR ${POLYPARTITION_ROOT}/src/polypartition
			INSTALL_DIR ${POLYPARTITION_ROOT}
			CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
			COMMENT "Building polypartition"
			LOG_DOWNLOAD ON)
	SET(POLYPARTITION_INCLUDE_DIR ${POLYPARTITION_ROOT}/src/polypartition/include)


	# Download the polypartition library.
	SET(XATLAS_ROOT ${CMAKE_CURRENT_BINARY_DIR}/deps/xatlas)
	SET(XATLAS_LIB_DIR ${XATLAS_ROOT}/lib)

	ExternalProject_Add(xatlas-external
			PREFIX ${XATLAS_ROOT}
			GIT_REPOSITORY "https://github.com/jpcy/xatlas"
			GIT_TAG "master"
			UPDATE_COMMAND ""
			PATCH_COMMAND ""
			SOURCE_DIR ${XATLAS_ROOT}/src/xatlas
			INSTALL_DIR ${XATLAS_ROOT}
			CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
			COMMENT "Building xatlas"
			LOG_DOWNLOAD ON)
	SET(XATLAS_INCLUDE_DIR ${XATLAS_ROOT}/src/xatlas/include)

	#https://github.com/recastnavigation/recastnavigation
	# Download the polypartition library.
	SET(RECASTNAVIGATION_ROOT ${CMAKE_CURRENT_BINARY_DIR}/deps/recastnavigation)
	SET(RECASTNAVIGATION_LIB_DIR ${RECASTNAVIGATION_ROOT}/lib)

	ExternalProject_Add(recastnavigation-external
			PREFIX ${RECASTNAVIGATION_ROOT}
			GIT_REPOSITORY "https://github.com/recastnavigation/recastnavigation"
			GIT_TAG "master"
			UPDATE_COMMAND ""
			PATCH_COMMAND ""
			SOURCE_DIR ${RECASTNAVIGATION_ROOT}/src/recastnavigation
			INSTALL_DIR ${RECASTNAVIGATION_ROOT}
			COMMENT "Building xatlas"
			CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
			LOG_DOWNLOAD ON)
	SET(RECASTNAVIGATION_INCLUDE_DIR ${RECASTNAVIGATION_ROOT}/src/recastnavigation/include)

	# https://github.com/smcameron/open-simplex-noise-in-c
	SET(OPENSIMPLENOISE_ROOT ${CMAKE_CURRENT_BINARY_DIR}/deps/open-simplex-noise-in-c)
	SET(OPENSIMPLENOISE_LIB_DIR ${OPENSIMPLENOISE_ROOT}/lib)

	ExternalProject_Add(open-simplex-noise-in-c-external
			PREFIX ${OPENSIMPLENOISE_ROOT}
			GIT_REPOSITORY "https://github.com/smcameron/open-simplex-noise-in-c"
			GIT_TAG "master"
			UPDATE_COMMAND ""
			PATCH_COMMAND ""
			SOURCE_DIR ${OPENSIMPLENOISE_ROOT}/src/open-simplex-noise-in-c
			INSTALL_DIR ${OPENSIMPLENOISE_ROOT}
			COMMENT "Building open-simplex-noise-in-c"
			CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
			LOG_DOWNLOAD ON)
	SET(OPENSIMPLENOISE_INCLUDE_DIR ${OPENSIMPLENOISE_ROOT}/src/open-simplex-noise-in-c/include)

	#https://gitlab.com/libeigen/eigen
	SET(EIGEN_ROOT ${CMAKE_CURRENT_BINARY_DIR}/deps/eigen)
	SET(EIGEN_LIB_DIR ${EIGEN_ROOT}/lib)

	ExternalProject_Add(eigen-external
			PREFIX ${EIGEN_ROOT}
			GIT_REPOSITORY "https://gitlab.com/libeigen/eigen"
			GIT_TAG "master"
			UPDATE_COMMAND ""
			PATCH_COMMAND ""
			SOURCE_DIR ${EIGEN_ROOT}/src/eigen
			INSTALL_DIR ${EIGEN_ROOT}
			COMMENT "Building eigen"
			CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
			LOG_DOWNLOAD ON)
	SET(EIGEN_INCLUDE_DIR ${EIGEN_ROOT}/src/eigen/include)

	# https://github.com/googlefonts/noto-fonts
	# https://github.com/source-foundry/Hack
	# https://github.com/google/etc2comp

	#https://gitlab.com/libeigen/eigen
	# https://github.com/baldurk/renderdoc.git
	# https://github.com/ispc/ispc.git
	# https://github.com/mborgerding/kissfft.git
	# https://github.com/NVIDIAGameWorks/PhysX.git

	#https://github.com/jemalloc/jemalloc.git
	# https://github.com/turbulenz/NvTriStrip.git
	# https://github.com/microsoft/ShaderConductor.git
	# https://github.com/AcademySoftwareFoundation/openexr.git
	# https://github.com/erikd/libsamplerate.git
	# https://bitbucket.org/jthlim/pvrtccompressor
	# https://sourceforge.net/projects/libsquish
	# https://github.com/syoyo/tinyexr
	# https://github.com/tatsuhiro-t/wslay.git

ELSE()
	MESSAGE(WARNING "Require Git for loading external source codes.")
ENDIF()

# Check that all the depdends variables are found
