cmake_minimum_required(VERSION 2.8)

project(mct_linear_solver)

option(USE_MPI "Compile with MPI support" OFF)

add_executable(main main.cpp)

find_package(INMOST REQUIRED)
if(NOT INMOST_FOUND)
    message("INMOST not found!")
endif()

include_directories(${INMOST_INCLUDE_DIRS})
target_link_libraries(main ${INMOST_LIBRARIES})
