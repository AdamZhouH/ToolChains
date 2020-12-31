cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(recipe-08)
message("C++ compiler flags: " ${CMAKE_CXX_FLAGS})

list(APPEND flags "-fPIC" "-Wall")

if(NOT WIN32)
    list(APPEND flags "-Wextra" "-Wpedantic")
endif()

add_library(geometry STATIC
        geometry_circle.cpp
        geometry_polygon.cpp
        geometry_rhombus.cpp 
        geometry_square.cpp
)
# 添加一些编译选项到geometry库的编译过程中
# 可见性
#
# PRIVATE 编译选项应用于给定的target而不会传递给和target相关的其他target
# INTERFACE 编译选项只应用于制定目标，并传递给与目标相关的目标
# PUBLIC 编译选项将应用于制定目标和使用塔的目标
# 利用target_compile_options添加编译选项相比于直接修改CMAKE_<LANG>_FLAGS_<CONFIG>
# 能更加细粒度地控制在哪些目标上使用哪些选项，并且不会影响上述的全局CMake变量
target_compile_options(geometry PRIVATE ${flags})

add_executable(compute-areas compute-areas.cpp)
target_compile_options(compute-areas PRIVATE "-fPIC")
target_link_libraries(compute-areas geometry)