# Download Nvidia/OpenCL Ubuntu 18.04
FROM nvidia/opencl:runtime-ubuntu18.04

# Copy the executable into the container
COPY cmake-build-release/opencl /home/
COPY cl/kernel.cl /home/

# Run the executable
WORKDIR /home
CMD ./opencl