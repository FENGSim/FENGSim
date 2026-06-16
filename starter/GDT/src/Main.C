#include "pcl/filters/uniform_sampling.h"
#include <ctime>
#include "SACIA.h"
#include "ICP.h"

int main (int argc, char** argv) {
    time_t start, end;
    time(&start);
	
    /*!
      step 0 import point cloud
    */
    std::cout << "**import point clouds**" << std::endl;
    Parameters pa;
    ReadParameters(pa);
    PointCloud<PointXYZ> _cloud_source, cloud_source, _cloud_target, cloud_target, cloud_sacia, cloud_icp;
    import_mesh("./../../build-FENGSim-Desktop_Qt_5_12_12_GCC_64bit-Debug/data/mesh/fengsim_mesh.vtk",_cloud_target);
    import_pc("./../../build-FENGSim-Desktop_Qt_5_12_12_GCC_64bit-Debug/data/meas/fengsim_meas_source.vtk",_cloud_source);
    std::cout << "source num: " << _cloud_source.size() << std::endl;
    std::cout << "target num: " << _cloud_target.size() << std::endl;
    
    /*!
      step 1 uniform sampling
    */
    std::cout << "**uniform sampling**" << std::endl;
    UniformSampling<PointXYZ> uniform;
    uniform.setRadiusSearch(pa.uns_radius);
    uniform.setInputCloud(_cloud_source.makeShared());
    uniform.filter(cloud_source);
    uniform.setInputCloud(_cloud_target.makeShared());
    uniform.filter(cloud_target);
    std::cout << "source num: " << cloud_source.size() << std::endl;
    std::cout << "target num: " << cloud_target.size() << std::endl;
    
    /*!
      step 2 sacia
    */
    std::cout << "**sacia**" << std::endl;
    SACIA sacia;
    sacia.Align(cloud_target,cloud_source,cloud_sacia,pa);
    export_pc_to_vtk(cloud_source, "./data/meas/1.vtk");
    export_pc_to_vtk(cloud_sacia, "./data/meas/2.vtk");
    
    /*!
      step 3 icp
    */
    std::cout << "**icp**" << std::endl;
    ICP icp;
    double fit = icp.Align(cloud_sacia,_cloud_source,cloud_icp,pa);
    std::cout << "icp fitness: " << fit << std::endl;
    
    /*!
      step 4 export transform matrix
    */
    std::cout << "**registration done**" << std::endl;
    Eigen::Matrix4f transform = sacia.transform.inverse() * icp.transform.inverse();
    export_matrix(transform, "./data/meas/trans_matrix");
    export_pc_to_vtk(cloud_icp, "./data/meas/3.vtk");
    //transformPointCloud (cloud_source, cloud_icp, transform);
    
    time(&end);
    double diff = difftime(end, start);
    std::cout << "time: " << diff << "s" << std::endl;
    return 0;
}
