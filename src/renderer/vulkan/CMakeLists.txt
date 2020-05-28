# Add support for compiling with debug tracer enable in the code.
IF (CMAKE_BUILD_TYPE STREQUAL "Release")
    ADD_DEFINITIONS(-DDEBUG_TRACKER)
ENDIF()

FIND_PACKAGE(Vulkan REQUIRED)
IF(Vulkan_FOUND)
    MESSAGE(STATUS "Vulkan: ${Vulkan_LIBRARY}")
ENDIF()

FILE(GLOB SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

#
ADD_LIBRARY(fragview-rvk ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(fragview-rvk -lvulkan fragview-core) #
TARGET_INCLUDE_DIRECTORIES(fragview-rvk PRIVATE ${Vulkan_INCLUDE_DIRS})
ADD_DEPENDENCIES(fragview-rvk fragview-core)
INSTALL(TARGETS fragview-rvk DESTINATION lib)