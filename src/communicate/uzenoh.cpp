#include "uzenoh/uzenoh.hpp"

#include <iostream>

namespace uzenoh {

static zenoh::Config create_zenoh_config(bool use_shm) {
    auto config = zenoh::Config::create_default();
    if (use_shm) {
        config.insert_json5("transport/shared_memory/enabled", "true");
    } else {
        config.insert_json5("transport/shared_memory/enabled", "false");
    }
    return config;
}

UZenoh::UZenoh(const std::string& id, bool use_shm)
    : id_(id), session_(zenoh::Session::open(create_zenoh_config(use_shm))) {
    std::cout << "[Zenoh] ID: " << id_ << (use_shm ? " (SHM Mode)" : " (Network Mode)")
              << std::endl;
}

zenoh::Publisher& UZenoh::get_or_create_publisher(const std::string& key) {
    auto it = publishers_.find(key);
    if (it == publishers_.end()) {
        auto [new_it, success] =
            publishers_.emplace(key, session_.declare_publisher(key));
        return new_it->second;
    }
    return it->second;
}

void UZenoh::pub(const std::string& key, const std::string& payload) {
    try {
        get_or_create_publisher(key).put(payload);
    } catch (const std::exception& e) {
        std::cerr << "String Pub 에러: " << e.what() << std::endl;
    }
}

void UZenoh::pub(const std::string& key, const cv::Mat& image) {
    if (image.empty()) return;

    try {
        if (use_shm_) {
            // [수정] Deleter가 uint8_t* 인자를 받도록 람다 함수로 전달
            if (image.isContinuous()) {
                get_or_create_publisher(key).put(zenoh::Bytes(
                    image.data, image.total() * image.elemSize(),
                    [](uint8_t* /*ptr*/) { /* 아무것도 하지 않음 (OpenCV가 관리) */ }));
            } else {
                // 연속적이지 않은 데이터는 안전하게 복사 후 전송
                cv::Mat continuous_img = image.clone();
                std::vector<uint8_t> buffer(
                    continuous_img.data,
                    continuous_img.data +
                        (continuous_img.total() * continuous_img.elemSize()));
                get_or_create_publisher(key).put(zenoh::Bytes(std::move(buffer)));
            }
        } else {
            // Network 모드 (JPEG 압축)
            std::vector<uint8_t> buffer;
            cv::imencode(".jpg", image, buffer);
            get_or_create_publisher(key).put(zenoh::Bytes(std::move(buffer)));
        }
    } catch (const std::exception& e) {
        std::cerr << "Image Pub 에러: " << e.what() << std::endl;
    }
}

void UZenoh::sub(const std::string& key,
                 std::function<void(const zenoh::Sample&)> callback) {
    try {
        auto sub = session_.declare_subscriber(key, callback, zenoh::closures::none);
        subscribers_.push_back(std::move(sub));
    } catch (const std::exception& e) {
        std::cerr << "에러 발생: " << e.what() << std::endl;
    }
}

void UZenoh::stop() { session_.close(); }

}  // namespace uzenoh
