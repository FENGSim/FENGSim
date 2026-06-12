/*!
  The codes are from the following examples.
  https://pcl.readthedocs.io/projects/tutorials/en/master/iterative_closest_point.html#iterative-closest-point
  FENGSim/toolkit/Geometry/pcl/doc/tutorials/content/sources/registration_api/example2.cpp
*/

#include <pcl/point_types.h>

using namespace pcl;
using namespace pcl::io;

class ICP {
public:
    Eigen::Matrix4f transform;
    Eigen::Matrix4f inverse_transform;
    double Align (PointCloud<PointXYZ>& cloud_source, PointCloud<PointXYZ>& cloud_target, PointCloud<PointXYZ>& cloud_icp);
    void AlignBack (PointCloud<PointXYZ>& cloud_source, PointCloud<PointXYZ>& cloud_target, PointCloud<PointXYZ>& cloud_icp);
};

