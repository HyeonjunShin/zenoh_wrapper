add_library(kinect kinect.cpp)

find_package(k4a REQUIRED)
find_package(OpenCV REQUIRED)

target_link_libraries(kinect PUBLIC k4a::k4a ${OpenCV_LIBS})
target_include_directories(kinect PUBLIC ${OpenCV_INCLUDE_DIRS})

target_include_directories(kinect
    PUBLIC 
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
)