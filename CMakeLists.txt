cmake_minimum_required(VERSION 3.15)

# Set the project name to your project name, my project isn't very descriptive
project(Raytracer CXX)
include(cmake/StandardProjectSettings.cmake)
include(cmake/PreventInSourceBuilds.cmake)

# Link this 'library' to set the c++ standard / compile-time options requested
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_20)

add_custom_target(format
  COMMAND ${CMAKE_SOURCE_DIR}/scripts/format.sh
  USES_TERMINAL
)

if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
  option(ENABLE_BUILD_WITH_TIME_TRACE "Enable -ftime-trace to generate time tracing .json files on clang" OFF)
  if(ENABLE_BUILD_WITH_TIME_TRACE)
    target_compile_options(project_options INTERFACE -ftime-trace)
  endif()
endif()

# Link this 'library' to use the warnings specified in CompilerWarnings.cmake
add_library(project_warnings INTERFACE)

# enable cache system
include(cmake/Cache.cmake)

# standard compiler warnings
include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

# sanitizer options if supported by compiler
include(cmake/Sanitizers.cmake)
enable_sanitizers(project_options)

# allow for static analysis options
include(cmake/StaticAnalyzers.cmake)

# Set up some extra Conan dependencies based on our needs before loading Conan
set(CONAN_EXTRA_REQUIRES
        glfw/3.3.6
        glew/2.2.0
        glm/0.9.9.8)
set(CONAN_EXTRA_OPTIONS "")

include(cmake/Conan.cmake)
run_conan()

add_subdirectory(src)