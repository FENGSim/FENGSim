/*!
  The codes are from the following examples.
  FENGSim/toolkit/Geometry/pcl/test/registration/test_sac_ia.cpp.
*/

#include "pcl/point_types.h"
#include "Tools.h"

using namespace pcl;
using namespace pcl::io;

class SACIA {
public:
    Eigen::Matrix4f transform;
    double Align (PointCloud<PointXYZ>& cloud_source, PointCloud<PointXYZ>& cloud_target,
		  PointCloud<PointXYZ>& cloud_sacia, Parameters pa);
};
