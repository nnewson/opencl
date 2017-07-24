#ifndef CL_DEVICE_H
#define CL_DEVICE_H

#include <list>

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/opencl.h>
#endif

#include "strFile.h"
#include "clKernel.h"
#include "clBuffer.h"

class clDevice
{
public:
	clDevice(const strFile& kernelFile);
	~clDevice();

	clKernel& createKernel(const std::string& kernelName);
	clBuffer& createBuffer(const size_t size);

protected:
	void setupDevice(const strFile& kernelFile);
	void releaseDevice();

private:
	std::list< clKernel >	m_kernels;
	std::list< clBuffer >	m_buffers;

	cl_platform_id			m_platformId;
	cl_device_id			m_deviceId; 
	cl_context				m_context;
	cl_command_queue		m_commandQueue;
	cl_program				m_program;
};

#endif // CL_DEVICE_H
