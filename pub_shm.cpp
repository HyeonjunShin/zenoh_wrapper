#include <iostream>
#include <thread>
#include <zenoh.hxx>
#include <cstring>

using namespace zenoh;

int main() {
    auto session = Session::open(Config::create_default());
    auto pub = session.declare_publisher("demo/example");

    // 1. SHM 프로바이더 생성 (64KB 크기)
    PosixShmProvider provider(MemoryLayout(65536, AllocAlignment({2})));

    while (true) {
        std::string data = "SHM Data!";
        
        // 2. SHM 영역에서 메모리 할당 (Zero-copy를 위한 준비)
        auto alloc_result = provider.alloc_gc_defrag_blocking(data.size() + 1);
        
        // 3. 할당된 메모리에 데이터 쓰기
        if (std::holds_alternative<ZShmMut>(alloc_result)) {
            auto& buf = std::get<ZShmMut>(alloc_result);
            std::memcpy(buf.data(), data.c_str(), data.size() + 1);

            // 4. SHM 버퍼 전송 (복사 발생 안 함)
            pub.put(std::move(buf));
            std::cout << "SHM으로 데이터 전송 완료" << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}