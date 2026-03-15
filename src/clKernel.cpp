#include "clKernel.hpp"

#include <stdexcept>
#include <string>

clKernel::clKernel(cl_program& program, cl_device_id& deviceId, cl_command_queue& commandQueue, std::string_view kernelName)
    : m_commandQueue(commandQueue)
{
    cl_int errorCode;
    std::string name{kernelName};

    m_kernel = clCreateKernel(program, name.c_str(), &errorCode);
    if (!m_kernel || errorCode != CL_SUCCESS)
    {
        throw std::runtime_error("Failed to create compute kernel.");
    }

    errorCode = clGetKernelWorkGroupInfo(m_kernel, deviceId, CL_KERNEL_WORK_GROUP_SIZE, sizeof(m_localSize), &m_localSize, nullptr);
    if (errorCode != CL_SUCCESS)
    {
        throw std::runtime_error("Failed to retrieve kernel work group info.");
    }
}

clKernel::~clKernel()
{
    clReleaseKernel(m_kernel);
}

void clKernel::bindBuffer(clBuffer& buffer, size_t index)
{
    cl_int errorCode;

    errorCode = clSetKernelArg(m_kernel, index, sizeof(cl_mem), &buffer.m_buffer);
    if (errorCode != CL_SUCCESS)
    {
        throw std::runtime_error("Failed to bind buffer to kernel.");
    }
}

void clKernel::bindConstant(const void* constant, size_t size, size_t index)
{
    cl_int errorCode;

    errorCode = clSetKernelArg(m_kernel, index, size, constant);
    if (errorCode != CL_SUCCESS)
    {
        throw std::runtime_error("Failed to bind constant to kernel.");
    }
}

void clKernel::run(size_t globalWorkSize)
{
    cl_int errorCode;

    errorCode = clEnqueueNDRangeKernel(m_commandQueue, m_kernel, 1, nullptr, &globalWorkSize, &m_localSize, 0, nullptr, nullptr);
    if (errorCode != CL_SUCCESS)
    {
        throw std::runtime_error("Failed to execute kernel.");
    }
}

void clKernel::join()
{
    clFinish(m_commandQueue);
}
