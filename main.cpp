#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <zenoh.hxx>

using namespace zenoh;
using namespace std::chrono_literals;

int main() {
    try {
        // 1. 기본 설정으로 세션 열기
        auto config = Config::create_default();
        std::cout << "Opening session..." << std::endl;
        auto session = Session::open(std::move(config));

        // 2. Publisher 선언 (전송할 주소 설정)
        const std::string keyexpr = "demo/example/zenoh-cpp-pub";
        std::cout << "Declaring Publisher on '" << keyexpr << "'..." << std::endl;
        auto pub = session.declare_publisher(keyexpr);

        // 3. 루프를 돌며 데이터 전송
        int idx = 0;
        while (true) {
            std::string payload = "[" + std::to_string(idx++) + "] Hello Zenoh from C++!";
            
            std::cout << "Putting Data: " << payload << std::endl;
            
            // 데이터를 전송 (Zenoh가 자동으로 적절한 버퍼링 처리)
            pub.put(payload);

            std::this_thread::sleep_for(1s);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}