#include "clDevice.h"

#include <array>
#include <iostream>
#include <stdexcept>

clDevice::clDevice(const strFile& kernelFile)
{
	setupDevice(kernelFile);
}

clDevice::~clDevice()
{
	releaseDevice();
}

clKernel& clDevice::createKernel(const std::string& kernelName)
{
	m_kernels.emplace_back(m_program, m_deviceId, m_commandQueue, kernelName);
	return m_kernels.back();
}

clBuffer& clDevice::createBuffer(const size_t size)
{
	m_buffers.emplace_back(m_context, m_commandQueue, size);
	return m_buffers.back();
}

void clDevice::setupDevice(const strFile& kernelFile)
{
	cl_int errorCode;

	errorCode = clGetPlatformIDs(1, &m_platformId, nullptr);
	if (errorCode != CL_SUCCESS)
	{
		throw std::runtime_error("Failed to get platform!\n");
	}

	errorCode = clGetDeviceIDs(m_platformId, CL_DEVICE_TYPE_GPU, 1, &m_deviceId, nullptr);
	if (errorCode != CL_SUCCESS)
	{
		throw std::runtime_error("Failed to create a device group.");
	}

	m_context = clCreateContext(0, 1, &m_deviceId, nullptr, nullptr, &errorCode);
	if (!m_context)
	{
		throw std::runtime_error("Failed to create a compute context.");
	}

	m_commandQueue = clCreateCommandQueue(m_context, m_deviceId, 0, &errorCode);
	if (!m_commandQueue)
	{
		throw std::runtime_error("Failed to create a command queue.");
	}

	auto source = kernelFile.str().c_str();
	m_program = clCreateProgramWithSource(m_context, 1, &source, nullptr, &errorCode);
	if (!m_program)
	{
		throw std::runtime_error("Failed to create compute program.");
	}

	errorCode = clBuildProgram(m_program, 0, nullptr, nullptr, nullptr, nullptr);
	if (errorCode != CL_SUCCESS)
	{
		std::array< char, 2048 > buildLog;
		clGetProgramBuildInfo(m_program, m_deviceId, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog.data(), nullptr);

		std::cerr << "Unable to build program: " << buildLog.data() << std::endl;
		throw std::runtime_error("Failed to build program executable.");
	}
}

void clDevice::releaseDevice()
{
	m_buffers.clear();
	m_kernels.clear();

	clReleaseProgram(m_program);
	clReleaseCommandQueue(m_commandQueue);
	clReleaseContext(m_context);
}