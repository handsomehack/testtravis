#====================== Copyright:JunZhe Fan ========================#
cmake_minimum_required(VERSION 3.8)

project(Semester1_LIBRARIES)

#======================= INCLUSION OF Our Code ======================#
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

file(GLOB_RECURSE SOURCES
    "${INCLUDE_DIR}/*.h"
    "${SOURCE_DIR}/*.cpp"
)

#tell CMake where to find the headers
include_directories(./include)

# generate a static lib
add_library(Semester1_LIBRARIES ${SOURCES})

# Make sure the compiler can find include files when the other programs need to link against this library 
target_include_directories (Semester1_LIBRARIES PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)


#=======================Install configuration =================#
#install optional header files
file(GLOB_RECURSE HEADERS
        "${INCLUDE_DIR}/*.h"
        )
install(FILES ${HEADERS}
        DESTINATION include
        COMPONENT headers)

#install optional CPP files
file(GLOB_RECURSE CPPS
        "${SOURCE_DIR}/*.cpp"
        )
install(FILES ${CPPS}
        DESTINATION source
        COMPONENT sources)

