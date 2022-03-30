set(CPP_SOURCES main.cpp Window.cpp Bitmap.cpp Camera.cpp shapes/Shape.h shapes/Sphere.cpp shapes/Sphere.h vec_utilities.h shapes/Plane.cpp shapes/Plane.h)

# Generic test that uses conan libs
add_executable(raytracer ${CPP_SOURCES})
target_link_libraries(
        raytracer
  PRIVATE project_options
          project_warnings
          CONAN_PKG::glfw
          CONAN_PKG::glew
          CONAN_PKG::glm
          CONAN_PKG::fmt
          CONAN_PKG::spdlog)
