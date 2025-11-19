cmake_minimum_required(VERSION 3.12...3.31)
project(Kin_building)

# Find CGAL (and optionally Qt6)
find_package(CGAL REQUIRED OPTIONAL_COMPONENTS Qt6)

# --- Find and include Eigen manually ---
find_package(Eigen3 QUIET)
if (EIGEN3_FOUND)
  message(STATUS "Found Eigen3 in ${EIGEN3_INCLUDE_DIRS}")
  include_directories(${EIGEN3_INCLUDE_DIRS})
else()
  message(WARNING "Eigen3 not found via CMake; adding default include path /usr/include/eigen3")
  include_directories(/usr/include/eigen3)
endif()

# --- Create executable ---
create_single_source_cgal_program("Kin_building.cpp")

# --- Link libraries ---
if(CGAL_Qt6_FOUND)
  target_link_libraries(Kin_building PRIVATE CGAL::CGAL_Basic_viewer)
else()
  target_link_libraries(Kin_building PRIVATE CGAL::CGAL)
endif()

# --- (Optional) Explicitly add include path to target ---
target_include_directories(Kin_building PRIVATE /usr/include/eigen3)

