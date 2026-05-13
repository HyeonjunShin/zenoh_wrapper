#pragma once
#include <string>
#include <zenoh.hxx>

#include "camera/kinect.hpp"

namespace uzenoh {
class UZenoh {
   public:
    UZenoh(const std::string& id, bool use_shm = false);
    zenoh::Publisher& get_or_create_publisher(const std::string& key);
    void pub(const std::string& key, const std::string& payload);
    void pub(const std::string& key, const cv::Mat& image);
    void sub(const std::string& key, std::function<void(const zenoh::Sample&)> callback);
    void stop();

   private:
    std::string id_;
    bool use_shm_;
    zenoh::Session session_;
    std::unordered_map<std::string, zenoh::Publisher> publishers_;
    std::vector<zenoh::Subscriber<void>> subscribers_;
};
}  // namespace uzenoh
