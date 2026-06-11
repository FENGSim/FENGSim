/*!
  the codes from FENGSim/toolkit/Geometry/pcl/test/registration/test_sac_ia.cpp
*/

#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/features/normal_3d.h>
#include <pcl/features/fpfh.h>
#include <pcl/registration/ia_ransac.h>
#include <pcl/registration/sample_consensus_prerejective.h>
#include <pcl/features/pfh.h>
#include <pcl/features/normal_3d_omp.h>
#include "Tools.h"


using namespace pcl;
using namespace pcl::io;

class sacia_align {
 public:
    Eigen::Matrix4f transform;
    double align (PointCloud<PointXYZ>& cloud_source, PointCloud<PointXYZ>& cloud_target,
		  PointCloud<PointXYZ>& cloud_sacia, double radius=1, double itnum=2000);
};
