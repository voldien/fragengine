
FIND_PACKAGE(GTest REQUIRED)
IF(GTEST_FOUND)
	MESSAGE(STATUS "Gtest found: ${GTEST_BOTH_LIBRARIES}")
ELSE()
	MESSAGE(ERROR "Gtest is required in order to compile and run the tests")
ENDIF()


# Get the include directories for the target.
get_target_property(LIBA_INCLUDES fragcore INCLUDE_DIRECTORIES)
get_target_property(LIBB_INCLUDES fragengine INCLUDE_DIRECTORIES)

# Source files.
FILE(GLOB SOURCE_FILES 	${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
						${CMAKE_CURRENT_SOURCE_DIR}/src/fragengine/*.cpp)	#TODO resolve 
FILE(GLOB HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

ADD_EXECUTABLE(fragengine-assert ${SOURCE_FILES} ${HEADER_FILES})
TARGET_LINK_LIBRARIES(fragengine-assert ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} fragcore fragengine pthread )
TARGET_INCLUDE_DIRECTORIES(fragengine-assert PRIVATE ${GTEST_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/include/ ${FRAG_CORE_INCLUDE} ${LIBA_INCLUDES} ${LIBB_INCLUDES})
ADD_DEPENDENCIES(fragengine-assert fragcore fragengine)

INSTALL(TARGETS fragengine-assert DESTINATION bin)

ADD_TEST(NAME assert-functionality
		COMMAND fragengine-assert
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})