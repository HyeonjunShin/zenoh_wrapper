#include "camera/kinect.hpp"

#include <k4a/k4a.h>
#include <k4a/k4atypes.h>

Kinect::Kinect()
    : device_(NULL),
      config(K4A_DEVICE_CONFIG_INIT_DISABLE_ALL),
      transformation_(NULL) {
    k4a_device_open(K4A_DEVICE_DEFAULT, &device_);

    // Configure the Kinect device with specific settings
    config.color_format = K4A_IMAGE_FORMAT_COLOR_BGRA32;
    config.color_resolution = K4A_COLOR_RESOLUTION_720P;
    config.depth_mode = K4A_DEPTH_MODE_WFOV_2X2BINNED;
    config.camera_fps = K4A_FRAMES_PER_SECOND_30;
    config.synchronized_images_only = true;

    // Congigure color controls
    k4a_device_set_color_control(
        device_, K4A_COLOR_CONTROL_EXPOSURE_TIME_ABSOLUTE,
        K4A_COLOR_CONTROL_MODE_MANUAL, 3000);
    k4a_device_set_color_control(device_, K4A_COLOR_CONTROL_GAIN,
                                 K4A_COLOR_CONTROL_MODE_MANUAL, 100);
    k4a_device_set_color_control(device_,
                                 K4A_COLOR_CONTROL_BRIGHTNESS,
                                 K4A_COLOR_CONTROL_MODE_MANUAL, 4500);
    k4a_device_set_color_control(device_, K4A_COLOR_CONTROL_SHARPNESS,
                                 K4A_COLOR_CONTROL_MODE_MANUAL, 3);
    k4a_device_set_color_control(
        device_, K4A_COLOR_CONTROL_POWERLINE_FREQUENCY,
        K4A_COLOR_CONTROL_MODE_MANUAL, 2);
}

Kinect::~Kinect() {
    k4a_transformation_destroy(transformation_);
    k4a_device_stop_cameras(device_);
    k4a_device_close(device_);
}
bool Kinect::open() {
    if (device_ == NULL) return false;

    k4a_device_start_cameras(device_, &config);

    k4a_calibration_t calibration;
    k4a_device_get_calibration(device_, config.depth_mode,
                               config.color_resolution, &calibration);
    transformation_ = k4a_transformation_create(&calibration);

    return true;
}

bool Kinect::getCapture(cv::Mat& color, cv::Mat& depth) {
    if (device_ == NULL) return false;

    k4a_capture_t capture;
    if (K4A_WAIT_RESULT_SUCCEEDED ==
        k4a_device_get_capture(device_, &capture, 1000)) {
        k4a_image_t color_image =
            k4a_capture_get_color_image(capture);
        if (color_image) {
            cv::Mat color_mat(720, 1280, CV_8UC4,
                              k4a_image_get_buffer(color_image));
            cv::cvtColor(color_mat, color, cv::COLOR_BGRA2BGR);
        }
        k4a_image_release(color_image);

        k4a_image_t depth_image =
            k4a_capture_get_depth_image(capture);
        if (depth_image) {
            k4a_image_t transformed_depth_image = NULL;
            k4a_image_create(K4A_IMAGE_FORMAT_DEPTH16, 1280, 720,
                             1280 * (int)sizeof(uint16_t),
                             &transformed_depth_image);
            k4a_transformation_depth_image_to_color_camera(
                transformation_, depth_image,
                transformed_depth_image);
            depth = cv::Mat(720, 1280, CV_16U,
                            (uint16_t*)(void*)k4a_image_get_buffer(
                                transformed_depth_image))
                        .clone();
            k4a_image_release(transformed_depth_image);
        }
        k4a_image_release(depth_image);
        k4a_capture_release(capture);

        return true;
    }
    return false;
}
