# Open CL Framework

## CMake Settings
Ensure you have both the following CMake setting defined:  
CMAKE_INCLUDE_PATH - This should point to the directory that contains your OpenCL include - i.e. the root of CL/opencl.h  
CMAKE_LIBRARY_PATH - This should point to the directory that contains your OpenCL libraries - i.e. the root of libOpenCL.so

To run this in Docker, use the nvidia-docker2 runtime, and then execute it as such:
sudo docker run --runtime=nvidia yourContainerName