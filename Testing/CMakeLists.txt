#====================== Copyright:JunZhe Fan ========================#
cmake_minimum_required(VERSION 3.8)
project(Testing)
include(CTest)

add_executable(Vector_Test Vector_Class_Testing.cpp)
target_link_libraries(Vector_Test Semester1_LIBRARIES)

add_executable(Cell_Test Cell_Class_Testing.cpp)
target_link_libraries(Cell_Test Semester1_LIBRARIES)

add_executable(Material_Test Material_Class_Testing.cpp)
target_link_libraries(Material_Test Semester1_LIBRARIES)

add_executable(Matrix_Test Matrix_Class_Testing.cpp)
target_link_libraries(Matrix_Test Semester1_LIBRARIES)


add_executable(Model_Test Model_Class_Testing.cpp)
target_link_libraries(Model_Test Semester1_LIBRARIES)


add_test(test Vector_Test Cell_Test Material_Test Matrix_Test Model_Test)