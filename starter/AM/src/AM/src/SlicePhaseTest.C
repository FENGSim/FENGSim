// author: Jiping Xin

#include "SlicePhaseTest.h"

/*!
  The original codes are in the path "FENGSim/toolkit/cura_engine/tests/integration/SlicePhaseTest.cpp"
*/

void SlicePhaseTestMain (int argc, char** argv) {
    std::ifstream is;
    is.open(std::string("./AM/conf/slicing.conf").c_str());
    const int len = 512;
    char L[len];
    is.getline(L,len);
    is.getline(L,len);
    std::string stlfile = L;
    is.getline(L,len);
    std::string vtkfile = L;
    is.getline(L,len);
    std::string vtkfile4pathplanning = L;
    is.getline(L,len);
    std::string clifile4meshing = L;
    is.getline(L,len);
    double layer_height_0 = 0.2;
    sscanf(L,"%lf", &layer_height_0);
    is.getline(L,len);
    double layer_height = 0.25;
    sscanf(L,"%lf", &layer_height);
    
    std::cout << stlfile << std::endl;
    std::cout << vtkfile << std::endl;
    std::cout << vtkfile4pathplanning << std::endl;
    std::cout << clifile4meshing << std::endl;
    std::cout << layer_height_0 << std::endl;
    std::cout << layer_height << std::endl;
    
    /*!
      Configuration
    */
    cura::Application::getInstance().current_slice = new cura::Slice(1);
    /*!
      And a few settings that we want to default.
    */
    cura::Scene& scene = cura::Application::getInstance().current_slice->scene;    
    scene.settings.add("slicing_tolerance", "middle");
    scene.settings.add("layer_height_0", std::to_string(layer_height_0));
    scene.settings.add("layer_height", std::to_string(layer_height));
    scene.settings.add("magic_mesh_surface_mode", "normal");
    scene.settings.add("meshfix_extensive_stitching", "false");
    scene.settings.add("meshfix_keep_open_polygons", "false");
    scene.settings.add("minimum_polygon_circumference", "1");
    //scene.settings.add("meshfix_maximum_resolution", "0.00001");
    //scene.settings.add("meshfix_maximum_deviation", "0.00001");
    scene.settings.add("meshfix_maximum_resolution", "0.001");
    scene.settings.add("meshfix_maximum_deviation", "0.001");
    scene.settings.add("xy_offset", "0");
    scene.settings.add("xy_offset_layer_0", "0");
    
    /*!
      Import stl mesh.
    */
    cura::MeshGroup& mesh_group = scene.mesh_groups.back();
    const cura::FMatrix3x3 transformation;
    cura::loadMeshIntoMeshGroup(&mesh_group, stlfile.c_str(), transformation, scene.settings);
    cura::Mesh& cube_mesh = mesh_group.meshes[0];
    
    /*!
      Generate slices.
    */
    const cura::coord_t layer_thickness = scene.settings.get<cura::coord_t>("layer_height");
    const cura::coord_t initial_layer_thickness = scene.settings.get<cura::coord_t>("layer_height_0");
    constexpr bool variable_layer_height = false;
    constexpr std::vector<cura::AdaptiveLayer>* variable_layer_height_values = nullptr;
    /*!
      Since Cura expects input in meters but converts it to millimeters,
      the height will be scaled by a factor of 1000.
    */
    const size_t num_layers = (cube_mesh.getAABB().max.z - initial_layer_thickness) / layer_thickness + 1;
    cura::Slicer slicer(&cube_mesh,layer_thickness,num_layers,variable_layer_height,variable_layer_height_values);
    std::cout << "The number of layers in the output must equal the requested number of layers." << std::endl 
	      << " " << slicer.layers.size() << " " << num_layers
	      << " "  << layer_thickness << std::endl;
    
    /*!
      Export slices for visualization.
    */
    Export2VTK(vtkfile,slicer,initial_layer_thickness,layer_thickness);
    /*!                                                                          
      Export slices for path planning.
      The difference between Export2VTK and Export2VTK4PathPlanning lies in the initial layer.
      Note that the initial layer is the slice of the model at the middle of the initial layer height,
      rather than being a slice generated directly at the initial layer height.
      0    0.0 -> 0.3    0.15 mm    Z = 0.3 mm
      1	   0.3 -> 0.5    0.40 mm    Z = 0.5 mm
      2    0.5 -> 0.7    0.60 mm    Z = 0.7 mm
      3    0.7 -> 0.9    0.80 mm    Z = 0.9 mm
    */
    Export2VTK4PathPlanning(vtkfile4pathplanning,slicer,initial_layer_thickness,layer_thickness);
    /*!
      Export slices for meshing (CLI format).
    */
    Export2Cli4Mesh(clifile4meshing, slicer, initial_layer_thickness, layer_thickness, cube_mesh.getAABB().min.z);
}
