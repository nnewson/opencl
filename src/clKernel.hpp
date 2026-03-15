#ifndef CL_KERNEL_HPP
#define CL_KERNEL_HPP

#include <string_view>

#define CL_TARGET_OPENCL_VERSION 120

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/opencl.h>
#endif

#include "clBuffer.hpp"

class clKernel
{
public:
    clKernel(cl_program& program, cl_device_id& deviceId, cl_command_queue& commandQueue,
             std::string_view kernelName);
    ~clKernel();

    clKernel(const clKernel&) = delete;
    clKernel& operator=(const clKernel&) = delete;
    clKernel(clKernel&&) = delete;
    clKernel& operator=(clKernel&&) = delete;

    void bindBuffer(clBuffer& buffer, size_t index);
    void bindConstant(const void* constant, size_t size, size_t index);

    void run(size_t globalWorkSize);
    void join();

private:
    friend class clBuffer;

    cl_command_queue& m_commandQueue;
    cl_kernel m_kernel;
    size_t m_localSize;
};

#endif // CL_KERNEL_HPP
