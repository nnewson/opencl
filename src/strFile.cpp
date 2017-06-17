#include "strFile.h"

#include <stdexcept>

strFile::strFile(const std::string& fileName)
{
	std::ifstream file(fileName, std::ios::in);
	if (file) {
		std::stringstream buffer;
		buffer << file.rdbuf();
		m_strFile = buffer.str();
	}
	else
	{
		throw std::runtime_error("Failed to open file.");
	}
}

const std::string& strFile::str() const
{
	return m_strFile;
}