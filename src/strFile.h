#ifndef STR_FILE_H
#define STR_FILE_H

#include <string>
#include <fstream>
#include <sstream>

class strFile
{
public:
	strFile(const std::string& fileName);

	const std::string& str() const;

private:
	std::string	m_strFile;
};

#endif // STR_FILE_H