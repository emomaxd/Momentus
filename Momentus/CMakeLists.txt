project(Momentus)

file(GLOB_RECURSE Momentus_SRC
    "${CMAKE_SOURCE_DIR}/Momentus/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/Momentus/src/*.hpp"
    "${CMAKE_SOURCE_DIR}/Momentus/src/*.h"
)

add_library(Momentus 
    ${Momentus_SRC}
)

target_include_directories(Momentus PRIVATE
    "${CMAKE_SOURCE_DIR}/Momentus/src"
)