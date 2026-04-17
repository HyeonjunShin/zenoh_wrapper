#include "uzenoh/uzenoh.hpp"

#include <iostream>

namespace uzenoh {
UZenoh::UZenoh(const std::string& id)
    : id_(id),
      session_(
          zenoh::Session::open(zenoh::Config::create_default())) {
    // try {
    // session =
    // zenoh::Session::open(zenoh::Config::create_default());
    // } catch (const std::exception& e) {
    // std::cerr << "에러 발생: " << e.what() << std::endl;
    // }
}

void UZenoh::pub(std::string key, std::string payload) {
    try {
        // while (true) {
        // std::string key = "demo/example/zenoh-cpp-pub";
        // std::string payload = "Hello Zenoh!";

        auto pub = session_.declare_publisher(key);
        pub.put(payload);
        std::cout << "전송 완료: " << payload << std::endl;
        // }
    } catch (const std::exception& e) {
        std::cerr << "에러 발생: " << e.what() << std::endl;
    }
}

void UZenoh::sub(std::string key,
                 std::function<void(const zenoh::Sample&)> callback) {
    try {
        auto sub = session_.declare_subscriber(key, callback,
                                               zenoh::closures::none);
        subscribers_.push_back(std::move(sub));
    } catch (const std::exception& e) {
        std::cerr << "에러 발생: " << e.what() << std::endl;
    }
}

}  // namespace uzenoh
