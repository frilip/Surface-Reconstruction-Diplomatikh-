#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Kinetic_surface_reconstruction_3.h>
#include <CGAL/Point_set_3.h>
#include <CGAL/Point_set_3/IO.h>
#include <CGAL/IO/polygon_soup_io.h>

using Kernel    = CGAL::Exact_predicates_inexact_constructions_kernel;
using FT        = typename Kernel::FT;
using Point_3   = typename Kernel::Point_3;
using Vector_3  = typename Kernel::Vector_3;
using Segment_3 = typename Kernel::Segment_3;

using Point_set    = CGAL::Point_set_3<Point_3>;
using Point_map    = typename Point_set::Point_map;
using Normal_map   = typename Point_set::Vector_map;

using KSR = CGAL::Kinetic_surface_reconstruction_3<Kernel, Point_set, Point_map, Normal_map>;

int main(int argc, char *argv[]) {
  // Input.
  std::string fname = argc==1?"../CGAL-6.1/data/points_3/building.ply" : argv[1];
  std::string output_name = argc<3 ? "output.ply" : argv[2];
  float lambda = argc<4? 0.7 : std::stof(argv[3]);
  int mrs = argc<5 ? 250 : std::stoi(argv[4]);
 
  Point_set point_set;
  CGAL::IO::read_point_set(CGAL::data_file_path(fname), point_set);

  std::cout << "Read point cloud" << std::endl;
 
  auto param = CGAL::parameters::maximum_distance(0.5) // default: 0.5
    .maximum_angle(10)                                 // default: 10
    .k_neighbors(12)                                   // default: 12
    .minimum_region_size(mrs);                         // default: 250
  
  // Algorithm.
  KSR ksr(point_set, param);
 
  ksr.detection_and_partition(1, param);
 
  std::cout << ksr.detected_planar_shapes().size() << " planar shapes detected" << std::endl;
 
  std::vector<Point_3> vtx;
  std::vector<std::vector<std::size_t> > polylist;
 
  std::cout << "Statring Reconstruction, using lambda = " << lambda << std::endl;
  ksr.reconstruct_with_ground(lambda, std::back_inserter(vtx), std::back_inserter(polylist));
 
  if (polylist.size() > 0) {
    std::cout << polylist.size() << " faces in reconstruction" << std::endl;
    CGAL::IO::write_polygon_soup(output_name, vtx, polylist);
    return EXIT_SUCCESS;
  }
  else {
    std::cout << "Reconstruction empty!" << std::endl;
    return EXIT_FAILURE;
  }
}
