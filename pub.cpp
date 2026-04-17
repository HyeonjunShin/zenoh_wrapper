#include <iostream>
#include <string>
#include <thread>
#include <zenoh.hxx>

using namespace zenoh;
using namespace std::chrono_literals;

int main() {
    try {
        // 1. 세션 연결 (기본 설정)
        auto session = Session::open(Config::create_default());

        // 2. Publisher 선언
        std::string key = "demo/example/zenoh-cpp-pub";
        auto pub = session.declare_publisher(key);

        std::cout << "Publisher가 '" << key << "'에 데이터를 보냅니다." << std::endl;

        int idx = 0;
        while (true) {
            std::string payload = "[" + std::to_string(idx++) + "] Hello Zenoh!";
            
            // 3. 데이터 전송 (단순 문자열 전송)
            pub.put(payload);
            
            std::cout << "전송 완료: " << payload << std::endl;
            std::this_thread::sleep_for(1s);
        }
    } catch (const std::exception& e) {
        std::cerr << "에러 발생: " << e.what() << std::endl;
    }
    return 0;
}