#include <chrono>
#include <thread>

#include "uzenoh/uzenoh.hpp"

int main() {
    Kinect kinect;
    kinect.open();

    cv::Mat color;
    cv::Mat depth;

    uzenoh::UZenoh myZenoh("Camera", true);
    while (true) {
        kinect.getCapture(color, depth);

        cv::Mat depth_viz, depth_color;
        depth.convertTo(depth_viz, CV_8U, 255.0 / 5000.0);
        cv::applyColorMap(depth_viz, depth_color, cv::COLORMAP_JET);
 
        cv::Mat blended;
        double alpha = 0.5;
        cv::addWeighted(color, alpha, depth_color, 1.0 - alpha, 0.0, blended);

        cv::imshow("Color", color);
        cv::imshow("RGB-Depth Overlay", blended);
        myZenoh.pub("camera/raw", color);

        if (cv::waitKey(1) == 27) break;

        // std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    myZenoh.stop();
    kinect.stop();
    return 0;
}