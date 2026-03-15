#ifndef CL_DEVICE_HPP
#define CL_DEVICE_HPP

#include <list>
#include <string>
#include <string_view>

#define CL_TARGET_OPENCL_VERSION 120

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/opencl.h>
#endif

#include "clBuffer.hpp"
#include "clKernel.hpp"

class clDevice
{
public:
    clDevice(const std::string& kernelSource);
    ~clDevice();

    clDevice(const clDevice&) = delete;
    clDevice& operator=(const clDevice&) = delete;
    clDevice(clDevice&&) = delete;
    clDevice& operator=(clDevice&&) = delete;

    clKernel& createKernel(std::string_view kernelName);
    clBuffer& createBuffer(size_t size);

protected:
    void setupDevice(const std::string& kernelSource);
    void releaseDevice();

private:
    std::list<clKernel> m_kernels;
    std::list<clBuffer> m_buffers;

    cl_platform_id m_platformId;
    cl_device_id m_deviceId;
    cl_context m_context;
    cl_command_queue m_commandQueue;
    cl_program m_program;
};

#endif // CL_DEVICE_HPP
