cmake_minimum_required(VERSION 3.17)
project(MCBE-hopper-fix)

set(CMAKE_CXX_STANDARD 17)
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_compile_definitions(-O3 -Wall)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    add_compile_options(/wd4819 /EHsc)
endif ()

#上面不用管
include_directories(${PROJECT_NAME} lib hook src gsl)
add_library(${PROJECT_NAME} SHARED dllmain.cpp src/HopperFix.cpp) #这里是.cpp文件
target_link_libraries(
        ${PROJECT_NAME}
        ${PROJECT_SOURCE_DIR}/lib/detours.lib

)