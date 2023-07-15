set(HEADER_FILES
    ../include/Array.h
    ../include/seconds.h
    aa_bounding_box.hpp
    anaglyph_camera.hpp
    bcc_lattice.hpp
    camera.hpp
    camera_abs.hpp
    camera_factory.hpp
    camera_modifier.hpp
    camera_modifier_factory.hpp
    caster.hpp
    cc_bspline.hpp
    cc_catmull_rom.hpp
    cc_interpolator.hpp
    cc_lattice.hpp
    cc_prefiltered_bspline.hpp
    cc_premultiplied_trilinear.hpp
    cc_trilinear.hpp
    cc_window_sinc.hpp
    colour_anaglyph_camera.hpp
    cross_eye_camera.hpp
    dubois_anaglyph_camera.hpp
    fcc_lattice.hpp
    frame_buffer.hpp
    frame_buffer_abs.hpp
    gradient_factory.hpp
    half_colour_anaglyph_camera.hpp
    highlight_modifier_decorator.hpp
    illumination_model_factory.hpp
    interpolator.hpp
    interpolator_factory.hpp
    lattice.hpp
    lattice_factory.hpp
    matrix3.hpp
    matrix_3d.hpp
    null_camera_modifier.hpp
    null_modifier.hpp
    optimised_anaglyph_camera.hpp
    pair.hpp
    perlin_modifier_decorator.hpp
    point_modifier.hpp
    point_modifier_factory.hpp
    preview_buffer_decorator.hpp
    quaternion.hpp
    settings.hpp
    shading_modifier_decorator.hpp
    simplex.hpp
    sphere.hpp
    stereo_camera.hpp
    transfer_function.hpp
    util.hpp
    vector.hpp
    vector4.hpp
    window_factory.hpp
)

set(SOURCE_FILES
    aa_bounding_box.cpp
    anaglyph_camera.cpp
    bcc_lattice.cpp
    camera.cpp
    camera_factory.cpp
    camera_modifier.cpp
    camera_modifier_factory.cpp
    caster.cpp
    cc_bspline.cpp
    cc_catmull_rom.cpp
    cc_lattice.cpp
    cc_prefiltered_bspline.cpp
    cc_premultiplied_trilinear.cpp
    cc_trilinear.cpp
    cc_window_sinc.cpp
    colour_anaglyph_camera.cpp
    cross_eye_camera.cpp
    dubois_anaglyph_camera.cpp
    fcc_lattice.cpp
    frame_buffer.cpp
    gradient_factory.cpp
    half_colour_anaglyph_camera.cpp
    highlight_modifier_decorator.cpp
    illumination_model_factory.cpp
    interpolator_factory.cpp
    lattice.cpp
    lattice_factory.cpp
    matrix3.cpp
    matrix_3d.cpp
    null_camera_modifier.cpp
    null_modifier.cpp
    optimised_anaglyph_camera.cpp
    pair.cpp
    perlin_modifier_decorator.cpp
    point_modifier.cpp
    point_modifier_factory.cpp
    preview_buffer_decorator.cpp
    quaternion.cpp
    settings.cpp
    shading_modifier_decorator.cpp
    simplex.cpp
    sphere.cpp
    stereo_camera.cpp
    transfer_function.cpp
    util.cpp
    vector.cpp
    vector4.cpp
    window_factory.cpp
)

# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "findFFTW")
# find_package(FFTW)
# if (FFTW_FOUND)
#     include_directories(${FFTW_INCLUDE_DIRS})
# endif()

find_package(OpenMP REQUIRED)
find_package(cimg)
find_package(picojson)

add_library(caster_lib STATIC ${HEADER_FILES} ${SOURCE_FILES} )
target_link_libraries(
    caster_lib
    ${FFTW_LIBRARIES}
    OpenMP::OpenMP_CXX
    cimg::cimg
    picojson::picojson
)

add_executable(gcaster main.cpp)
target_link_libraries(gcaster caster_lib )
