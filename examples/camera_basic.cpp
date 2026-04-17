#include "camera/kinect.hpp"

int main() {
    Kinect kinect;
    kinect.open();

    cv::Mat color;
    cv::Mat depth;

    while (true) {
        kinect.getCapture(color, depth);

        cv::Mat depth_viz, depth_color;
        depth.convertTo(depth_viz, CV_8U, 255.0 / 5000.0);
        cv::applyColorMap(depth_viz, depth_color, cv::COLORMAP_JET);

        cv::Mat blended;
        double alpha = 0.5;
        cv::addWeighted(color, alpha, depth_color, 1.0 - alpha, 0.0,
                        blended);

        cv::imshow("Color", color);
        cv::imshow("RGB-Depth Overlay", blended);

        if (cv::waitKey(1) == 27) break;
    }

    return 0;
}