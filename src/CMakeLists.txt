set(HEADER_FILES
    ../include/Array.h
    ../include/seconds.h
    AABoundingBox.hpp
    AnaglyphCamera.hpp
    BCCLattice.hpp
    Camera.hpp
    CameraAbs.hpp
    CameraFactory.hpp
    CameraModifier.hpp
    CameraModifierFactory.hpp
    Caster.hpp
    CCBSpline.hpp
    CCCatmullRom.hpp
    CCInterpolator.hpp
    CCLattice.hpp
    CCPrefilteredBSpline.hpp
    CCPremultipliedTrilinear.hpp
    CCTrilinear.hpp
    CCWindowSinc.hpp
    ColourAnaglyphCamera.hpp
    CrossEyeCamera.hpp
    DuboisAnaglyphCamera.hpp
    FCCLattice.hpp
    FrameBuffer.hpp
    FrameBufferAbs.hpp
    GradientFactory.hpp
    HalfColourAnaglyphCamera.hpp
    HighlightModifierDecorator.hpp
    IlluminationModelFactory.hpp
    Interpolator.hpp
    InterpolatorFactory.hpp
    Lattice.hpp
    LatticeFactory.hpp
    Matrix3.hpp
    Matrix3D.hpp
    NullCameraModifier.hpp
    NullModifier.hpp
    OptimisedAnaglyphCamera.hpp
    Pair.hpp
    PerlinModifierDecorator.hpp
    PointModifier.hpp
    PointModifierFactory.hpp
    PreviewBufferDecorator.hpp
    Quaternion.hpp
    Settings.hpp
    ShadingModifierDecorator.hpp
    simplex.hpp
    Sphere.hpp
    StereoCamera.hpp
    TransferFunction.hpp
    Util.hpp
    Vector.hpp
    Vector4.hpp
    WindowFactory.hpp
)

set(SOURCE_FILES
    AABoundingBox.cpp
    AnaglyphCamera.cpp
    BCCLattice.cpp
    Camera.cpp
    CameraFactory.cpp
    CameraModifier.cpp
    CameraModifierFactory.cpp
    Caster.cpp
    CCBSpline.cpp
    CCCatmullRom.cpp
    CCLattice.cpp
    CCPrefilteredBSpline.cpp
    CCPremultipliedTrilinear.cpp
    CCTrilinear.cpp
    CCWindowSinc.cpp
    ColourAnaglyphCamera.cpp
    CrossEyeCamera.cpp
    DuboisAnaglyphCamera.cpp
    FCCLattice.cpp
    FrameBuffer.cpp
    GradientFactory.cpp
    HalfColourAnaglyphCamera.cpp
    HighlightModifierDecorator.cpp
    IlluminationModelFactory.cpp
    InterpolatorFactory.cpp
    Lattice.cpp
    LatticeFactory.cpp
    Matrix3.cpp
    Matrix3D.cpp
    NullCameraModifier.cpp
    NullModifier.cpp
    OptimisedAnaglyphCamera.cpp
    Pair.cpp
    PerlinModifierDecorator.cpp
    PointModifier.cpp
    PointModifierFactory.cpp
    PreviewBufferDecorator.cpp
    Quaternion.cpp
    Settings.cpp
    ShadingModifierDecorator.cpp
    simplex.cpp
    Sphere.cpp
    StereoCamera.cpp
    TransferFunction.cpp
    Util.cpp
    Vector.cpp
    Vector4.cpp
    WindowFactory.cpp
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
