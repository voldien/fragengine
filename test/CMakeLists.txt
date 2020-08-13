# Asserting the functonality.
#ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/assert)
#SET(FRAGVIEW_BIN ${CMAKE_CURRENT_SOURCE_DIR}/../client/fragview)

IF (UNIX)
	#TODO improve with arguments for more flexiable testing.
	ADD_TEST(NAME assert-samples
			COMMAND ${BASH} sample-testing.sh ${CMAKE_CURRENT_SOURCE_DIR}/../samples/ ${CMAKE_CURRENT_SOURCE_DIR}/../client/fragview
			WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
ENDIF ()

FIND_PROGRAM(MEMORYCHECK_COMMAND valgrind)
IF (MEMORYCHECK_COMMAND)
	MESSAGE(STATUS "valgrind found: ${MEMORYCHECK_COMMAND}")
	SET(MEMORYCHECK_COMMAND_OPTIONS "--tool=memcheck --xml=yes --xml-file=/tmp/valgrind --gen-suppressions=all --leak-check=full --leak-resolution=med --track-origins=yes --vgdb=no")
	SET(MEMORYCHECK_SUPPRESSIONS_FILE "${PROJECT_SOURCE_DIR}/valgrind_suppress.txt")
	SET(MEMORYCHECK_FULL_COMMAND "${MEMORYCHECK_COMMAND} ${MEMORYCHECK_COMMAND_OPTIONS}")

	ADD_TEST(NAME memory-leak-default
			COMMAND ${MEMORYCHECK_FULL_COMMAND} ${FRAGVIEW_BIN} --version)
ENDIF ()



#TODO perhaps relocate
#ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/examples)