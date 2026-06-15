#ifndef _ODT_PCL_TOOLS_H_
#define _ODT_PCL_TOOLS_H_

#include <pcl/point_types.h>
#include <pcl/common/transforms.h>
#include <fstream>

#include "Tools.h"

void export_pc_to_vtk (pcl::PointCloud<pcl::PointXYZ> pc, std::string filename)
{
    std::ofstream out(filename);
    for (int i = 0; i < pc.size(); i++) {
        out << (pc.points)[i].x << " "
	    << (pc.points)[i].y << " "
	    << (pc.points)[i].z << std::endl;
    }
    out.close();
}

void export_pc_to_vtk (pcl::PointCloud<pcl::PointXYZ>::Ptr pc, std::string filename)
{
    std::ofstream out(filename);
    for (int i = 0; i < pc->size(); i++) {
        out << (pc->points)[i].x << " "
	    << (pc->points)[i].y << " "
	    << (pc->points)[i].z << std::endl;
    }
    out.close();
}

void export_matrix (Eigen::Matrix4f transform, std::string filename)
{
    std::ofstream out(filename);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
	    out << transform(i,j) << " ";
	}
	out << std::endl;
    }
    out.close();
}

void import_pc (std::string filename, pcl::PointCloud<pcl::PointXYZ>::Ptr pc) {
    std::ifstream is(filename);
    const int len = 256;
    char L[len];
    while (is.getline(L,len)) {
        double z[3];
	sscanf(L,"%lf %lf %lf", z, z+1, z+2);
	pc->push_back(pcl::PointXYZ(z[0], z[1], z[2]));
    }
    is.close();
}

void import_pc (std::string filename, pcl::PointCloud<pcl::PointXYZ> &pc) {
    std::ifstream is(filename);
    const int len = 256;
    char L[len];
    while (is.getline(L,len)) {
        double z[3];
	sscanf(L,"%lf %lf %lf", z, z+1, z+2);
	pc.push_back(pcl::PointXYZ(z[0], z[1], z[2]));
    }
    is.close();
}

void import_mesh (std::string filename, pcl::PointCloud<pcl::PointXYZ>::Ptr pc) {
    std::ifstream is(filename);
    const int len = 256;
    char L[len];

    for (int i=0; i<5; i++)
        is.getline(L,len);
    double n;
    sscanf(L,"%*s %lf %*s", &n);
    //std::cout << n << std::endl;

    for (int i=0; i<n; i++) {
        is.getline(L,len);
        double t[3];
	sscanf(L,"%lf %lf %lf", t, t+1, t+2);
	pc->push_back(pcl::PointXYZ(t[0], t[1], t[2]));
    }
    is.close();
}

void import_mesh (std::string filename, pcl::PointCloud<pcl::PointXYZ> &pc) {
    std::ifstream is(filename);
    const int len = 256;
    char L[len];

    for (int i=0; i<5; i++)
        is.getline(L,len);
    double n;
    sscanf(L,"%*s %lf %*s", &n);
    //std::cout << n << std::endl;

    for (int i=0; i<n; i++) {
        is.getline(L,len);
        double t[3];
	sscanf(L,"%lf %lf %lf", t, t+1, t+2);
	pc.push_back(pcl::PointXYZ(t[0], t[1], t[2]));
    }
    is.close();
}

void source_mesh_tran (Eigen::Matrix4f transform_icp, Eigen::Matrix4f transform_sacia)
{
    pcl::PointCloud<pcl::PointXYZ> pc0, pc1, pc2;
    import_pc("./data/meas/fengsim_meas_source_mesh.vtk", pc0);
    transformPointCloud(pc0, pc1, transform_icp);
    transformPointCloud(pc1, pc2, transform_sacia);
    export_pc_to_vtk(pc2, "./data/meas/fengsim_meas_source_mesh_trans.vtk");
}

void voxel_grid (pcl::PointCloud<pcl::PointXYZ>& pc, double t, std::string filename) {
    double xmax = (pc.points)[0].x;
    double ymax = (pc.points)[0].y;
    double zmax = (pc.points)[0].z;
    double xmin = (pc.points)[0].x;
    double ymin = (pc.points)[0].y;
    double zmin = (pc.points)[0].z;
    for (int i = 0; i < pc.size(); i++) {
        if ((pc.points)[i].x > xmax) xmax = (pc.points)[i].x;
	if ((pc.points)[i].y > ymax) ymax = (pc.points)[i].y;
	if ((pc.points)[i].z > zmax) zmax = (pc.points)[i].z;
	
	if ((pc.points)[i].x < xmin) xmin = (pc.points)[i].x;
	if ((pc.points)[i].y < ymin) ymin = (pc.points)[i].y;
	if ((pc.points)[i].z < zmin) zmin = (pc.points)[i].z;
    }
    int nx = std::floor((xmax - xmin) / t);
    int ny = std::floor((ymax - ymin) / t);
    int nz = std::floor((zmax - zmin) / t);
    nx++;
    ny++;
    nz++;
    std::cout << std::endl << "box numbers: " << nx << " " << ny << " " << nz << std::endl << std::endl;
    
    for (int i = 0; i < pc.size(); i++) {
        std::cout << "coordinates: " << (pc.points)[i].x << " " << (pc.points)[i].y << " " << (pc.points)[i].z << std::endl;
        std::cout << "box id: " << static_cast<int> (std::floor ((pc.points)[i].x / t)) << " ";
	std::cout << static_cast<int> (std::floor ((pc.points)[i].y / t)) << " ";
	std::cout << static_cast<int> (std::floor ((pc.points)[i].z / t)) << std::endl;
	double x,y,z;
	x = static_cast<int> (std::floor ((pc.points)[i].x / t))*t + 0.5*t;
	y = static_cast<int> (std::floor ((pc.points)[i].y / t))*t + 0.5*t;
	z = static_cast<int> (std::floor ((pc.points)[i].z / t))*t + 0.5*t;
	std::cout << "box: (" << static_cast<int> (std::floor ((pc.points)[i].x / t))*t
		  << " " << static_cast<int> (std::floor ((pc.points)[i].x / t))*t + t << ") "<< std::endl
		  << "     (" << static_cast<int> (std::floor ((pc.points)[i].y / t))*t << " "
		  << static_cast<int> (std::floor ((pc.points)[i].y / t))*t + t << ") "<< std::endl
		  << "     (" << 0 << " " << 0 << ") "<< std::endl;
	std::cout << "distance to box center: " << std::sqrt(pow((pc.points)[i].x-x,2) + pow((pc.points)[i].y-y,2) + pow((pc.points)[i].z-z,2))
		  << std::endl << std::endl;
    }


    
    std::ofstream out(filename);
    out << "# vtk DataFile Version 2.0" << std::endl;
    out << "Rectilinear Grid by FENGSim" << std::endl;
    out << "ASCII" << std::endl;
    out << "DATASET RECTILINEAR_GRID" << std::endl;
    out << "DIMENSIONS " << nx+1 << " " << ny+1 << " " << nz+1 << std::endl;
    out << "X_COORDINATES " << nx+1 << " float" << std::endl;
    for (int i=0; i<nx+1; i++) {
        out << xmin + i*t << " ";
    }
    out << std::endl;
    out << "Y_COORDINATES " << ny+1 << " float" << std::endl;
    for (int i=0; i<ny+1; i++) {
        out << ymin + i*t << " ";
    }
    out << std::endl;
    out << "Z_COORDINATES " << nz+1 << " float" << std::endl;
    for (int i=0; i<nz+1; i++) {
        out << zmin + i*t << " ";
    }
    out << std::endl;
    out.close();
}

void ReadParameters (Parameters& pa) {
    const int len = 256;
    char L[len];
    std::ifstream is("./../conf/gdt.conf");

    is.getline(L,len);
    sscanf(L,"%*[^=]=%lf",&(pa.uns_radius));
    std::cout << "uns_radius=" << pa.uns_radius << std::endl;
    
    is.getline(L,len);
    sscanf(L,"%*[^=]=%lf",&(pa.sacia_normal_search_radius));
    std::cout << "sacia_normal_search_radius=" << pa.sacia_normal_search_radius << std::endl;
    
    is.getline(L,len);
    sscanf(L,"%*[^=]=%lf",&(pa.sacia_fpfh_search_radius));
    std::cout << "sacia_fpfh_search_radius=" << pa.sacia_fpfh_search_radius << std::endl;
    
    is.getline(L,len);
    sscanf(L,"%*[^=]=%d",&(pa.sacia_number_samples));
    std::cout << "sacia_number_samples=" << pa.sacia_number_samples << std::endl;
    
    is.getline(L,len);
    sscanf(L,"%*[^=]=%lf",&(pa.sacia_min_sample_distance));
    std::cout << "sacia_min_sample_distance=" << pa.sacia_min_sample_distance << std::endl;
    
    is.getline(L,len);
    sscanf(L,"%*[^=]=%lf",&(pa.sacia_max_correspondence_distance));
    std::cout << "sacia_max_correspondence_distance=" << pa.sacia_max_correspondence_distance << std::endl;

    is.getline(L,len);
    sscanf(L,"%*[^=]=%d",&(pa.sacia_maximum_iterations));
    std::cout << "sacia_maximum_iterations=" << pa.sacia_maximum_iterations << std::endl;
    
    is.getline(L,len);
    sscanf(L,"%*[^=]=%d",&(pa.sacia_correspondence_randomness));
    std::cout << "sacia_correspondence_randomness=" << pa.sacia_correspondence_randomness << std::endl;

    is.getline(L,len);
    sscanf(L,"%*[^=]=%d",&(pa.icp_maximum_iterations));
    std::cout << "icp_maximum_iterations=" << pa.icp_maximum_iterations << std::endl;

    is.getline(L,len);
    sscanf(L,"%*[^=]=%lf",&(pa.icp_max_correspondence_distance));
    std::cout << "icp_max_correspondence_distance=" << pa.icp_max_correspondence_distance << std::endl;
    
    is.getline(L,len);
    sscanf(L,"%*[^=]=%lf",&(pa.icp_transformation_epsilon));
    std::cout << "icp_transformation_epsilon=" << pa.icp_transformation_epsilon << std::endl;

    is.getline(L,len);
    sscanf(L,"%*[^=]=%lf",&(pa.icp_euclidean_fitness_epsilon));
    std::cout << "icp_euclidean_fitness_epsilon=" << pa.icp_euclidean_fitness_epsilon << std::endl;
}

#endif
