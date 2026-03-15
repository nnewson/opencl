FROM ubuntu:24.04 AS build

RUN apt-get update && apt-get install -y \
    build-essential cmake ninja-build git curl zip unzip tar pkg-config ocl-icd-opencl-dev \
    gcc-14 g++-14 \
    && rm -rf /var/lib/apt/lists/*

ENV CC=gcc-14
ENV CXX=g++-14

# Install vcpkg
RUN git clone https://github.com/microsoft/vcpkg.git /opt/vcpkg && \
    /opt/vcpkg/bootstrap-vcpkg.sh
ENV VCPKG_ROOT=/opt/vcpkg

WORKDIR /src
COPY vcpkg.json vcpkg-configuration.json CMakeLists.txt CMakePresets.json ./
COPY src/ src/
COPY cl/ cl/

RUN cmake --preset vcpkg
RUN cmake --build build

FROM ubuntu:24.04
RUN apt-get update && apt-get install -y libstdc++6 ocl-icd-libopencl1 pocl-opencl-icd && rm -rf /var/lib/apt/lists/*
COPY --from=build /src/build/opencl /usr/local/bin/opencl
COPY --from=build /src/cl/kernel.cl /usr/local/bin/kernel.cl
ENTRYPOINT ["opencl"]