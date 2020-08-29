# Download Ubuntu 20.04
FROM ubuntu:20.04

RUN apt-get update && apt-get install -y ocl-icd-opencl-dev

# Copy the executable into the container
COPY build/opencl /home/
COPY cl/kernel.cl /home/

# Run the executable
WORKDIR /home
CMD ./opencl
