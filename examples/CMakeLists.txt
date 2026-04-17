# option(BUILD_EXAMPLES "Build example applications" ON)

# if(BUILD_EXAMPLES)
add_executable(pub_ex pub.cpp)
add_executable(sub_ex sub.cpp)
add_executable(camera_basic camera_basic.cpp)

target_link_libraries(pub_ex PRIVATE uzenoh)
target_link_libraries(sub_ex PRIVATE uzenoh)
target_link_libraries(camera_basic PUBLIC kinect)
# target_include_directories(camera_basic PUBLIC ${OpenCV_INCLUDE_DIRS})


install(TARGETS pub_ex sub_ex camera_basic
        RUNTIME DESTINATION bin)

install(DIRECTORY examples/ 
        DESTINATION examples
        FILES_MATCHING PATTERN "*.cpp" PATTERN "*.hpp")
# endif()
