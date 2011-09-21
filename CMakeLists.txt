project(test_susure)

set(CMAKE_CXX_FLAGS "-O3 -Wall")

add_executable(test_susure main.cpp)

target_link_libraries(test_susure opencv_core opencv_features2d opencv_calib3d)

