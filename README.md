# Open CL Framework

## CMake Settings
Ensure you have both the following CMake setting defined:  
`CMAKE_INCLUDE_PATH` - This should point to the directory that contains your OpenCL include - i.e. the root of `CL/opencl.h`

`CMAKE_LIBRARY_PATH` - This should point to the directory that contains your OpenCL libraries - i.e. the root of `libOpenCL.so`

## Docker Settings
Build the Docker container in the working directory as:
```
docker build --tag opencl:VERSION_NUMBER
```
To run it, use the nvidia-docker2 runtime:
```
docker run --runtime=nvidia opencl:VERSION_NUMBER
```