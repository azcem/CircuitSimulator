cmake_minimum_required(VERSION 3.20)

project(CircuitSimulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Eigen3 REQUIRED)

add_executable(CircuitSimulator
    main.cpp
    src/parse.cpp
    src/solve.cpp
    src/stamp.cpp
    src/Elements/Element.cpp
)

target_include_directories(CircuitSimulator PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(CircuitSimulator PRIVATE Eigen3::Eigen)
