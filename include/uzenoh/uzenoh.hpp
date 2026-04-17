#pragma once
#include <string>

#include "zenoh.hxx"

namespace uzenoh {
class UZenoh {
   public:
    UZenoh(const std::string& id);
    void pub(std::string key, std::string payload);
    void sub(std::string key,
             std::function<void(const zenoh::Sample&)> callback);

   private:
    std::string id_;
    zenoh::Session session_;
    std::vector<zenoh::Subscriber<void>> subscribers_;
};
}  // namespace uzenoh
