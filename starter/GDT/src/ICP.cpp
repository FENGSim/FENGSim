#include "ICP.h"

double icp_align::align (PointCloud<PointXYZ>& cloud_source, PointCloud<PointXYZ>& cloud_target, PointCloud<PointXYZ>& cloud_icp)
{
    PointCloud<PointXYZ>::Ptr cloud_source_ptr, cloud_target_ptr;
    cloud_source_ptr = cloud_source.makeShared ();
    cloud_target_ptr = cloud_target.makeShared ();
    
    pcl::IterativeClosestPoint<pcl::PointXYZ, pcl::PointXYZ> icp;
    icp.setMaximumIterations(1000);
    icp.setTransformationEpsilon(1e-10);
    icp.setEuclideanFitnessEpsilon(1e-10);
    /*!
      filter nonoverlop parts
     */
    icp.setRANSACIterations(500);
    
    icp.setInputSource(cloud_source_ptr);
    icp.setInputTarget(cloud_target_ptr);
    
    icp.align(cloud_icp);
    for (int i=0; i<4; i++) {
	for (int j=0; j<4; j++) {
	    transform(i,j) = icp.getFinalTransformation()(i,j);
	}
    }

    std::cout << icp.getFinalTransformation() << std::endl;    
    // Check that we have sucessfully converged
    std::cout << "if icp conv: "<< icp.hasConverged() << std::endl;
    // Test that the fitness score is below acceptable threshold
    return icp.getFitnessScore();
}

void icp_align::align_back (PointCloud<PointXYZ>& cloud_source, PointCloud<PointXYZ>& cloud_target, PointCloud<PointXYZ>& cloud_icp)
{
    PointCloud<PointXYZ>::Ptr cloud_source_ptr, cloud_target_ptr;
    cloud_source_ptr = cloud_source.makeShared ();
    cloud_target_ptr = cloud_target.makeShared ();
	
    pcl::IterativeClosestPoint<pcl::PointXYZ, pcl::PointXYZ> icp;
    icp.setMaximumIterations(500);
    icp.setTransformationEpsilon(1e-5);
    icp.setEuclideanFitnessEpsilon(1e-5);
    
    icp.setInputSource(cloud_source_ptr);
    icp.setInputTarget(cloud_target_ptr);
    
    icp.align(cloud_icp);
    
    std::cout << icp.getFinalTransformation() << std::endl;
    Eigen::Matrix4f trans;
    for (int i = 0; i < 4; i++) {
	for (int j = 0; j < 4; j++) {
	    trans(i,j) = icp.getFinalTransformation()(i,j);
	}
    }
    inverse_transform = trans.inverse();
    transformPointCloud (cloud_target, cloud_icp, inverse_transform);
    
    // Check that we have sucessfully converged
    std::cout << "if icp conv: "<< icp.hasConverged() << std::endl;
    // Test that the fitness score is below acceptable threshold
    std::cout << icp.getFitnessScore() << std::endl;
}
