#ifndef CCNY_RGBD_CALIBRATE_UNCERTAINTY_COMPARATOR_H 
#define CCNY_RGBD_CALIBRATE_UNCERTAINTY_COMPARATOR_H 

#include <tf/transform_listener.h>
#include <boost/filesystem.hpp>

#include <ccny_rgbd/types.h>

namespace ccny_rgbd
{

class UncertaintyLogger 
{
  public:

    UncertaintyLogger(const ros::NodeHandle& nh, 
              const ros::NodeHandle& nh_private);
    
    virtual ~UncertaintyLogger();

    void RGBDCallback(const ImageMsg::ConstPtr& rgb_msg,
                      const ImageMsg::ConstPtr& depth_msg,
                      const CameraInfoMsg::ConstPtr& info_msg);  

  private:

    ros::NodeHandle nh_;
    ros::NodeHandle nh_private_;

    boost::shared_ptr<RGBDSynchronizer3> sync_;
       
    ImageSubFilter      sub_depth_;
    ImageSubFilter      sub_rgb_;
    CameraInfoSubFilter sub_info_;

    std::string rgb_path_;
    std::string depth_path_;
    std::string stdev_path_;
    std::string stdev_q_path_;
    std::string stdev_qgmm_path_;

    boost::thread input_thread_;
    
    // state variables
    int count_;
    bool logging_;
    bool rgb_saved_;
    
    cv::Mat c_img_;   // uint16t
    cv::Mat m_img_;   // double
    cv::Mat s_img_;   // double
        
    cv::Mat stdev_gt_img_;
    cv::Mat stdev_q_img_;
    cv::Mat stdev_qgmm_img_;     
        
    // parameters   
    int n_depth_;
    int id_;   
    
    std::string path_;

    void prepareDirectories();
    
    void keyboardThread();
    
    double getStDev(int v, int u);

    void buildUncertaintyImages(const cv::Mat& depth_img);
};

} // namespace ccny_rgbd

#endif // CCNY_RGBD_CALIBRATE_UNCERTAINTY_COMPARATOR_H 
