# CMakeList.txt : CMake project for RelativisticRaytracer, include source and define
# project specific logic here.
#

file(GLOB_RECURSE src CONFIGURE_DEPENDS "*.cpp" "*.h")

# Add source to this project's executable.
add_executable (RelativisticRaytracer ${src})

target_link_libraries(RelativisticRaytracer raylib)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET RelativisticRaytracer PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
