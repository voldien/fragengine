
OPTION(BUILD_WITH_GTK "Use GTK API." OFF)

FILE(GLOB EDITOR_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
						${CMAKE_CURRENT_SOURCE_DIR}/src/Tools/*.cpp)
FILE(GLOB EDITOR_HEADER_FILES  ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
FILE(GLOB RES_FILES ${CMAKE_CURRENT_SOURCE_DIR}/res/*.ui)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include/)


SET(CMAKE_AUTOMOC ON)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
FIND_PACKAGE(Qt5 COMPONENTS Widgets Core )

IF(Qt5Widgets_FOUND)
	FILE(GLOB QT_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/QT/*.cpp)

	INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include/)
	ADD_EXECUTABLE(fragview-editor-qt ${EDITOR_SOURCE_FILES} ${EDITOR_HEADER_FILES} ${QT_SOURCE_FILES})

	TARGET_LINK_LIBRARIES(fragview-editor-qt ${Qt5Widgets_LIBRARIES} ${Qt5Core_LIBRARIES} fragengine)

	TARGET_COMPILE_OPTIONS(fragview-editor-qt PRIVATE
			${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS} -DFRAG_EDITOR_QT_WINDOW_MANAGER=1)

	TARGET_INCLUDE_DIRECTORIES(fragview-editor-qt PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/include/ ${Qt5Widgets_INCLUDE_DIRS} ${Qt5Core_INCLUDE_DIRS})

	ADD_DEPENDENCIES(fragview-editor-qt fragcore fragengine)
	INSTALL(TARGETS fragview-editor-qt DESTINATION bin)

ELSE()
	MESSAGE(FATAL_ERROR "Could not locate QT5 Version")
ENDIF()

#
IF(UNIX)


ENDIF()

FIND_PACKAGE(Icotool)
IF(ICOTOOL_FOUND)
	MESSAGE(STATUS "icotool: ${ICOTOOL_EXECUTABLE} -- ${ICOTOOL_VERSION_STRING}")
	# Generate icon for window platforms.
	# -c -o favicon.ico mysite_32x32.png mysite_64x64.png
	ADD_CUSTOM_TARGET( create-icon-type
			COMMENT "Creating header and source file for display shaders."
			COMMAND ${ICOTOOL_EXECUTABLE} -c -o favicon.ico mysite_32x32.png mysite_64x64.png)
ELSE()
	MESSAGE(WARNING "Could not find the program tools for creating window icons.")
ENDIF()