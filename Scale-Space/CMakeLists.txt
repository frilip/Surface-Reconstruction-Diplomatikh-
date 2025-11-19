cmake_minimum_required(VERSION 3.12...3.31)

project(scale_space)

find_package(CGAL REQUIRED)
add_executable(scale-space scale-space.cpp)
target_link_libraries(scale-space CGAL::CGAL)
