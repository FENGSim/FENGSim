#ifndef _TOOLS_H_
#define _TOOLS_H_

#include <pcl/point_types.h>
#include <pcl/common/transforms.h>
#include <fstream>

struct Parameters {
    double uns_radius;
    double sacia_normal_search_radius;
    double sacia_fpfh_search_radius;
    int sacia_number_samples;
    double sacia_min_sample_distance;
    double sacia_max_correspondence_distance;
    int sacia_maximum_iterations;
    int sacia_correspondence_randomness;
    int icp_maximum_iterations;
    double icp_max_correspondence_distance;
    double icp_transformation_epsilon;
    double icp_euclidean_fitness_epsilon;
};

void ReadParameters (Parameters& pa);

void export_pc_to_vtk (pcl::PointCloud<pcl::PointXYZ> pc, std::string filename);
void export_pc_to_vtk (pcl::PointCloud<pcl::PointXYZ>::Ptr pc, std::string filename);
void export_matrix (Eigen::Matrix4f transform, std::string filename);
void import_pc (std::string filename, pcl::PointCloud<pcl::PointXYZ>::Ptr pc);
void import_pc (std::string filename, pcl::PointCloud<pcl::PointXYZ> &pc);
void import_mesh (std::string filename, pcl::PointCloud<pcl::PointXYZ>::Ptr pc);
void import_mesh (std::string filename, pcl::PointCloud<pcl::PointXYZ> &pc);
void source_mesh_tran (Eigen::Matrix4f transform_icp, Eigen::Matrix4f transform_sacia);
void voxel_grid (pcl::PointCloud<pcl::PointXYZ>& pc, double t, std::string filename);

#endif
