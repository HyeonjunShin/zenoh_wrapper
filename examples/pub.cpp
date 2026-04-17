#include <chrono>
#include <thread>

#include "uzenoh/uzenoh.hpp"

int main() {
    uzenoh::UZenoh myZenoh("Camera");
    while (true) {
        myZenoh.pub("camera/raw", "Hello Zenoh!");
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return 0;
}