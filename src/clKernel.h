#ifndef CL_KERNEL_H
#define CL_KERNEL_H

#include <string>

#include <CL/opencl.h>

#include "clBuffer.h"

class clKernel
{
public:
	clKernel(cl_program& program, cl_device_id& deviceId, cl_command_queue& commandQueue, const std::string& kernelName);
	~clKernel();

	void bindBuffer(clBuffer& buffer, const size_t index);
	void bindConstant(const void* const constant, const size_t size, const size_t index);

	void run(const size_t globalWorkSize);
	void join();

private:
	friend class		clBuffer;

	cl_command_queue&	m_commandQueue;
	cl_kernel 			m_kernel;

	size_t				m_localSize;
};

#endif // CL_KERNEL_H