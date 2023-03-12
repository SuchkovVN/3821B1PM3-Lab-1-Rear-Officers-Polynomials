set(target ${TESTS})

file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/gtest")
#include_directories("${CMAKE_CURRENT_SOURCE_DIR}/lib")

add_executable(${target} ${srcs} ${hdrs})
target_link_libraries(${target} gtest MML)
