#pragma once
#include <vector>

#include "includes.hpp"
#include <string_view>

class file
{
protected:
	std::vector<i8> m_file;
public:

	[[nodiscard]]
	bool ImportFile(std::string_view);
	[[nodiscard]]
	bool ExportFile(std::string_view) const;
};
