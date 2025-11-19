#include <cstdlib>
#include <iostream>
#include <fstream>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Point_set_3.h>
#include <CGAL/Point_set_3/IO.h>
#include <CGAL/draw_point_set_3.h>
#include <CGAL/Graphics_scene_options.h>
#include <CGAL/Qt/Basic_viewer.h>
#include <CGAL/draw_surface_mesh.h>



#ifdef CGAL_USE_BASIC_VIEWER
#include <QMainWindow>
#endif

// types
typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef Kernel::FT FT;
typedef Kernel::Point_3 Point_3;
typedef Kernel::Vector_3 Vector_3;
typedef Kernel::Sphere_3 Sphere_3;
typedef CGAL::Point_set_3<Point_3, Vector_3> Point_set;

typedef std::array<std::size_t, 3> Facet; // Triple of indices




 

int main(int argc, char *argv[]){

  // Use X11 because Wayland does not cooperate
  setenv("QT_QPA_PLATFORM", "xcb", 1);

  Point_set points;

  std::string fname = argc==1?"../CGAL-6.1/data/points_3/kitten.xyz" : argv[1];
  if (argc < 2)
  {
    std::cerr << "Usage: " << argv[0] << " [input.xyz/off/ply/las]" << std::endl;
    std::cerr <<"Running " << argv[0] << " data/kitten.xyz -1\n";
  }

  std::cout << fname << std::endl;

  std::ifstream stream (fname, std::ios_base::binary);
  if (!stream)
  {
    std::cerr << "Error: cannot read file " << fname << std::endl;
    return EXIT_FAILURE;
  }

  stream >> points;

  std::cout << "Read " << points.size () << " point(s)" << std::endl;
  if (points.empty())
    return EXIT_FAILURE;
  

  CGAL::draw(points);



  return EXIT_SUCCESS;
}
 

