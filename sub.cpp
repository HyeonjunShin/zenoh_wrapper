#include <iostream>
#include <thread>
#include <zenoh.hxx>

using namespace zenoh;
using namespace std::chrono_literals;

int main() {
    try {
        // 1. 세션 연결
        auto session = Session::open(Config::create_default());

        std::string key = "demo/example/**";
        
        // 2. Subscriber 선언
        // 가독성과 빌드 안정성을 위해 인자를 명확히 구분했습니다.
        auto sub = session.declare_subscriber(
            KeyExpr(key), 
            [](const Sample& sample) {
                // 핵심: get_keyexpr()과 as_string_view() 사용
                auto key_view = sample.get_keyexpr().as_string_view();
                auto payload_view = sample.get_payload().as_string();

                std::cout << ">> [수신] 키: " << key_view 
                          << " | 데이터: " << payload_view << std::endl;
            },
            closures::none // on_drop 콜백 (필수 인자)
        );

        std::cout << "'" << key << "' 구독 중... (종료: Ctrl+C)" << std::endl;

        // 3. 수신 대기
        while (true) {
            std::this_thread::sleep_for(1s);
        }
    } catch (const std::exception& e) {
        std::cerr << "에러 발생: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}