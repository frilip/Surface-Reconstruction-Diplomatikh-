cmake_minimum_required(VERSION 3.12...3.31)

project(Read_pointcloud)

#CGAL_Qt6 is needed for the drawing.
find_package(CGAL REQUIRED OPTIONAL_COMPONENTS Qt6)

#create the executable of the application
create_single_source_cgal_program("Read_pointcloud.cpp")

if(CGAL_Qt6_FOUND) 
  #link it with the required CGAL libraries
  target_link_libraries(Read_pointcloud PRIVATE CGAL::CGAL_Basic_viewer)
endif()
 
#end of the file