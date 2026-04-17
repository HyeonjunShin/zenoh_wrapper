#!/bin/bash

echo "Rust 설치를 시작합니다..."
curl --proto '=https' --tlsv1.2 -sSf https://rustup.rs | sh -s -- -y

source "$HOME/.cargo/env"

# 3. 설치 확인
if command -v rustc >/dev/null 2>&1; then
    echo "-------------------------------------------"
    echo "축하합니다! Rust 설치가 완료되었습니다."
    rustc --version
    echo "-------------------------------------------"
else
    echo "설치 중 문제가 발생했습니다. 네트워크 상태를 확인해 주세요."
fi


wget https://github.com/eclipse-zenoh/zenoh-c/archive/refs/tags/1.8.0.tar.gz
tar -xzf 1.8.0.tar.gz
cd ./zenoh-c-1.8.0
cargo build --release
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../zenoh-c/
make -j$(nproc)
make install

wget https://github.com/eclipse-zenoh/zenoh-cpp/archive/refs/tags/1.8.0.tar.gz
tar -xzf 1.8.0.tar.gz
cd ./zenoh-cpp-1.8.0
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../zenoh-cpp/
make -j$(nproc)
make install
