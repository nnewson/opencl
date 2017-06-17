#include "clBuffer.h"

#include <stdexcept>

clBuffer::clBuffer(cl_context& context, cl_command_queue& commandQueue, const size_t size)
: m_commandQueue(commandQueue)
{
	m_buffer = clCreateBuffer(context, CL_MEM_READ_WRITE, size, nullptr, nullptr);
	if (!m_buffer)
	{
		throw std::runtime_error("Failed to allocate buffer.");
	}
}

clBuffer::~clBuffer()
{
	clReleaseMemObject(m_buffer);
}

void clBuffer::write(const void* const input, const size_t size)
{
	cl_int errorCode;

	errorCode = clEnqueueWriteBuffer(m_commandQueue, m_buffer, CL_TRUE, 0, size, input, 0, nullptr, nullptr);
	if (errorCode != CL_SUCCESS)
	{
		throw std::runtime_error("Failed to write to buffer.");
	}
}

void clBuffer::read(void* const output, const size_t size)
{
	cl_int errorCode;

	errorCode = clEnqueueReadBuffer(m_commandQueue, m_buffer, CL_TRUE, 0, size, output, 0, nullptr, nullptr);
	if (errorCode != CL_SUCCESS)
	{
		throw std::runtime_error("Failed to read from buffer.");
	}
}