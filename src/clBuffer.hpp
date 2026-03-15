#ifndef CL_BUFFER_HPP
#define CL_BUFFER_HPP

#define CL_TARGET_OPENCL_VERSION 120

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/opencl.h>
#endif

class clBuffer
{
public:
    clBuffer(cl_context& context, cl_command_queue& commandQueue, size_t size);
    ~clBuffer();

    clBuffer(const clBuffer&) = delete;
    clBuffer& operator=(const clBuffer&) = delete;
    clBuffer(clBuffer&&) = delete;
    clBuffer& operator=(clBuffer&&) = delete;

    void write(const void* input, size_t size);
    void read(void* output, size_t size);

private:
    friend class clKernel;

    cl_command_queue& m_commandQueue;
    cl_mem m_buffer;
};

#endif // CL_BUFFER_HPP
