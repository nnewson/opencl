cmake_minimum_required(VERSION 3.8)

project(OPENCL)

add_executable(opencl src/main.cpp
                      src/clBuffer.cpp
                      src/clDevice.cpp
                      src/clKernel.cpp
                      src/strFile.cpp)

target_compile_features(opencl PUBLIC cxx_std_17)
set_target_properties(opencl PROPERTIES CXX_EXTENSIONS OFF)

find_path(OPENCL_INC NAMES "CL/opencl.h")
target_include_directories(opencl PRIVATE "${OPENCL_INC}")
message(WARNING "OpenCL dir: " ${OPENCL_INC})

find_library(OPENCL_LIB OpenCL)
target_link_libraries(opencl "${OPENCL_LIB}")
message(WARNING "OpenCL dir: " ${OPENCL_LIB})
