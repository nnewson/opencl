#ifndef CL_BUFFER_H
#define CL_BUFFER_H

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/opencl.h>
#endif

class clBuffer
{
public:
	clBuffer(cl_context& context, cl_command_queue& commandQueue, const size_t size);
	~clBuffer();

	void write(const void* const input, const size_t size);
	void read(void* const output, const size_t size);

private:
	friend class		clKernel;

	cl_command_queue&	m_commandQueue;
	cl_mem 				m_buffer;
};

#endif // CL_BUFFER_H
