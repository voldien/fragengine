# Source files for the gl bunny program.
FILE(GLOB SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
FILE(GLOB SOURCE_COMMON ${CMAKE_CURRENT_SOURCE_DIR}/../common/*.cpp)
FILE(GLOB SOURCE_COMMON_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/../common/*.h)

# Get the include directories for the target.
get_target_property(LIBA_INCLUDES fragcore INCLUDE_DIRECTORIES)
get_target_property(LIBB_INCLUDES fragengine INCLUDE_DIRECTORIES)

# Executable OpenGL hpm benchmark.
ADD_EXECUTABLE(audio-example ${SOURCE_FILES} ${SOURCE_COMMON} ${SOURCE_COMMON_HEADER})
TARGET_LINK_LIBRARIES(audio-example fragcore ${SDL2_LIBRARIES})
TARGET_INCLUDE_DIRECTORIES(audio-example PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../common/ ${LIBA_INCLUDES} ${LIBB_INCLUDES})
