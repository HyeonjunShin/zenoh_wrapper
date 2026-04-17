cmake_minimum_required(VERSION 3.16)
project(uzenoh VERSION 1.0.0)

# set(CMAKE_CXX_STANDARD 17)

# add_executable(zenoh_app main.cpp)
# add_executable(zenoh_pub pub.cpp)
# add_executable(zenoh_sub sub.cpp)
# add_executable(zenoh_pub_shm pub_shm.cpp)

# target_link_libraries(zenoh_app PUBLIC zenohcxx::zenohc)
# target_link_libraries(zenoh_pub PUBLIC zenohcxx::zenohc)
# target_link_libraries(zenoh_sub PUBLIC zenohcxx::zenohc)
# target_link_libraries(zenoh_pub_shm PUBLIC zenohcxx::zenohc)

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(examples)

install(EXPORT uzenohTargets
        FILE uzenohConfig.cmake
        NAMESPACE uzenoh::
        DESTINATION lib/cmake/uzenoh)
