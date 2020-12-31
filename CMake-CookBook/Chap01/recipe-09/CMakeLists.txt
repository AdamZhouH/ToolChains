cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(recipe-09 LANGUAGES CXX)

set(CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION ON)

add_library(animals SHARED 
    Animal.cpp 
    Cat.cpp 
    Dog.cpp 
    Factory.hpp    
)

set_target_properties(animals PROPERTIES
    CXX_STANDARD 14
    CXX_EXTENSIONS OFF
    CXX_STANDARD_REQUIRED ON 
    POSITION_INDEPENDENT_CODE 1
)

add_executable(animal-farm animal-farm.cpp)
set_target_properties(animal-farm PROPERTIES
    CXX_STANDARD 14
    CXX_EXTENSIONS OFF
    CXX_STANDARD_REQUIRED ON
)
target_link_libraries(animal-farm animals)