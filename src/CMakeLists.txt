
# # set(Zenoh_USE_STATIC_LIBS ON)

# # set(zenohc_DIR "~/.local/lib/cmake/zenohc")
# # find_package(zenohc REQUIRED)

# # set(zenohcxx_DIR "~/.local/lib/cmake/zenohcxx")
# # find_package(zenohcxx REQUIRED)

# # target_link_libraries(uzenoh PUBLIC zenohcxx::zenohc)

# add_library(uzenoh uzenoh.cpp)

# target_compile_definitions(uzenoh PUBLIC ZENOHCXX_ZENOHC)
# set(ZENOH_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/zenoh")
# target_include_directories(uzenoh
#     PUBLIC 
#         $<BUILD_INTERFACE:${ZENOH_ROOT}/include>
#         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
#         $<INSTALL_INTERFACE:include>
# )

# target_link_libraries(uzenoh 
#     PUBLIC 
#         "${ZENOH_ROOT}/lib/libzenohc.a"
#         pthread 
#         dl
# )

# # make install targets
# install(TARGETS uzenoh
#         EXPORT uzenohTargets
#         LIBRARY DESTINATION lib    # dynamic library .so / .dylib 저장
#         ARCHIVE DESTINATION lib    # static library .a 저장
#         RUNTIME DESTINATION bin)   # .exe / .dll 저장

# install(DIRECTORY ../include/uzenoh DESTINATION include) # 헤더 복사
# install(DIRECTORY ${ZENOH_ROOT}/include/ DESTINATION include)
add_subdirectory(communicate)
add_subdirectory(camera)