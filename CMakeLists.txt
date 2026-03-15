cmake_minimum_required(VERSION 3.20)

project(opencl
  VERSION 0.1.0
  DESCRIPTION "OpenCL example project"
  LANGUAGES CXX
)

add_executable(opencl
  src/main.cpp
  src/clBuffer.cpp
  src/clDevice.cpp
  src/clKernel.cpp
  src/strFile.cpp
)

find_package(OpenCL REQUIRED)

# Link OpenCL using CMake's built-in FindOpenCL module
# Suppress macOS OpenCL deprecation warnings (Apple deprecated OpenCL in favor of Metal)
target_link_libraries(opencl OpenCL::OpenCL)
target_compile_features(opencl PUBLIC cxx_std_23)
target_compile_definitions(opencl PRIVATE CL_SILENCE_DEPRECATION)

# Add a command to copy the OpenCL files into the binary directory for usage
add_custom_command(TARGET opencl POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_SOURCE_DIR}/cl
  $<TARGET_FILE_DIR:opencl>
)
