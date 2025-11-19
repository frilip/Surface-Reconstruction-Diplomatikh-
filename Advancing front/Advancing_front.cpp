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

// For Advancing front
#include <CGAL/Advancing_front_surface_reconstruction.h>
#include <CGAL/Surface_mesh.h>
#include <CGAL/Polygon_mesh_processing/polygon_soup_to_polygon_mesh.h>


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

  // Surface reconstruction with Advancing Front algorithm (Delaunay like, keeps all points as verts)
  std::vector<Facet> facets;
  CGAL::advancing_front_surface_reconstruction(points.points().begin(),
                                              points.points().end(),
                                              std::back_inserter(facets));

  std::vector<Point_3> vertices;
  vertices.reserve (points.size());
  std::copy (points.points().begin(), points.points().end(), std::back_inserter (vertices));

  CGAL::Surface_mesh<Point_3> output_mesh_AF;
  CGAL::Polygon_mesh_processing::polygon_soup_to_polygon_mesh (vertices, facets, output_mesh_AF);

  CGAL::draw(output_mesh_AF);






  return EXIT_SUCCESS;
}
 

