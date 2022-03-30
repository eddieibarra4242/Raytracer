set(CPP_SOURCES main.cpp Window.cpp Bitmap.cpp Camera.cpp shapes/Sphere.cpp shapes/Plane.cpp Scene.cpp)

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
