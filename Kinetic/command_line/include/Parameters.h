#include <string>

struct Parameters{
    std::string data = "../supplementary/KSR42_dataset/Intermediate/Barn_laser_2M/barn_laser_2M.ply";   // -data
    float maximum_distance = 0.5;                  // -dist
    unsigned int maximum_angle = 20;               // -angle
    unsigned int k_neighbors = 12;                 // -kn
    unsigned int min_region_size = 250;            // -minp
    bool debug = false;                            // -debug
    bool verbose = false;                          // -verbose
    unsigned int max_octree_depth = 3;             // -odepth
    unsigned int max_octree_node_size = 40;        // -osize
    bool reorient = true;                          // -reorient
    bool regparallel = true;                       // -regparallel
    bool regcoplanar = true;                       // -regcoplanar
    bool regorthogonal = true;                    // -regorthogonal
    bool regsymmetric = false;                     // -regsymmetric
    unsigned int angle_tolerance = 5;              // -regangle
    float maximum_offset = 0.05;                   // -regoff
    unsigned int k_intersections = 2;              // -k
    float graphcut_lambda = 0.6;                   // -lambda
    bool use_ground = false;                       // -ground
    bool with_normals = false;                     // -wnormals
    std::string output_name = "reconstructed.ply"; // -outname
};