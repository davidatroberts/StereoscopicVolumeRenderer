project(tests)

include(FetchContent)
FetchContent_Declare(
    googletest
    https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(SOURCE_FILES
    test_cc_premultiplied_trilinear.cpp
    test_matrix_3d.cpp
    test_window_sinc.cpp
)

target_link_libraries(
    tests
    caster_lib
    gmock_main
    gmock
    gtest
)

include(GoogleTest)
gtest_discover_tests()
