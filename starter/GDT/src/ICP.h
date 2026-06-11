/*!
  https://pcl.readthedocs.io/projects/tutorials/en/master/iterative_closest_point.html#iterative-closest-point
  FENGSim/toolkit/Geometry/pcl/doc/tutorials/content/sources/registration_api/example2.cpp
*/

#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/features/normal_3d.h>
#include <pcl/registration/registration.h>
#include <pcl/registration/icp.h>
#include <pcl/registration/joint_icp.h>
#include <pcl/registration/icp_nl.h>
#include <pcl/registration/gicp.h>
#include <pcl/registration/gicp6d.h>
#include <pcl/registration/transformation_estimation_point_to_plane.h>
#include <pcl/registration/transformation_validation_euclidean.h>
#include <pcl/registration/correspondence_rejection_median_distance.h>
#include <pcl/registration/correspondence_rejection_sample_consensus.h>
#include <pcl/registration/correspondence_rejection_surface_normal.h>
#include <pcl/registration/correspondence_estimation_normal_shooting.h>
#include <pcl/registration/pyramid_feature_matching.h>
#include <pcl/features/ppf.h>
#include <pcl/registration/ppf_registration.h>
#include <pcl/filters/voxel_grid.h>
// We need Histogram<2> to function, so we'll explicitly add kdtree_flann.hpp here
#include <pcl/kdtree/impl/kdtree_flann.hpp>
//(pcl::Histogram<2>)

using namespace pcl;
using namespace pcl::io;

class icp_align {
 public:
    Eigen::Matrix4f transform;
    Eigen::Matrix4f inverse_transform;
    double align (PointCloud<PointXYZ>& cloud_source, PointCloud<PointXYZ>& cloud_target, PointCloud<PointXYZ>& cloud_icp);
    void align_back (PointCloud<PointXYZ>& cloud_source, PointCloud<PointXYZ>& cloud_target, PointCloud<PointXYZ>& cloud_icp);
};

