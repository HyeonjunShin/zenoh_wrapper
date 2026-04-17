enable_testing() # 테스트 기능 활성화

add_executable(my_test main.cpp)

target_link_libraries(my_test PRIVATE uzenoh)

add_test(NAME MyLibraryTest COMMAND my_test)