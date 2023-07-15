project(tests)

find_package(GTest)

set(SOURCE_FILES
    test_cc_premultiplied_trilinear.cpp
    test_matrix_3d.cpp
    test_window_sinc.cpp
)

add_executable(tests ${SOURCE_FILES})

target_link_libraries(
    tests
    caster_lib
    gmock_main
    gmock
    gtest::gtest
)

include(GoogleTest)
gtest_discover_tests(tests)
