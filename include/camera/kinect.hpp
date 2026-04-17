#include <k4a/k4a.h>
#include <k4a/k4atypes.h>

#include <opencv2/core/mat.hpp>
#include <opencv2/opencv.hpp>

class Kinect {
   public:
    Kinect();
    ~Kinect();
    bool open();
    bool getCapture(cv::Mat& color, cv::Mat& depth);
    void transformDepthToColor(const k4a_image_t depth_image,
                               k4a_image_t* transformed_depth_image);

   private:
    k4a_device_t device_;
    k4a_device_configuration_t config;
    k4a_transformation_t transformation_;
};