cmake_minimum_required(VERSION 3.14)
project(graph)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer")

add_executable(${PROJECT_NAME} main.cpp BaseGraph.h AdjacentVectorGraph.h AdjacentVectorGraph.cpp GraphTest.cpp StrengthComponents.h TopologicalSort.h TopologicalSort.cpp Arrays.h ArraysInt.h Mst.h Mst.cpp QuickSort.h)

target_link_libraries(${PROJECT_NAME} gtest_main gtest pthread)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
