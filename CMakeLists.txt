cmake_minimum_required(VERSION 3.8)

project(OPENCL)

add_executable(opencl src/main.cpp
                      src/clBuffer.cpp
                      src/clDevice.cpp
                      src/clKernel.cpp
                      src/strFile.cpp)

# Use C++17, without compiler specific extensions
target_compile_features(opencl PUBLIC cxx_std_17)
set_target_properties(opencl PROPERTIES CXX_EXTENSIONS OFF)

# Setup the OpenCL include directory
find_path(OPENCL_INC NAMES "CL/opencl.h")
target_include_directories(opencl PRIVATE "${OPENCL_INC}")

# Setup the OpenCL library directory
find_library(OPENCL_LIB OpenCL)
target_link_libraries(opencl "${OPENCL_LIB}")

# Add a command to copy the OpenCL files into the binary directory for usage
add_custom_command(TARGET opencl POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/cl
                   $<TARGET_FILE_DIR:opencl>)