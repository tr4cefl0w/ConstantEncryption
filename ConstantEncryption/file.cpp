#include "file.h"
#include <fstream>
#include <stdexcept>

bool file::ImportFile(std::string_view import_file) 
{
	std::ifstream input{ import_file.data() , std::ios::binary };

	if (!input.good()) {
		return false;
	}

	m_file = { std::istreambuf_iterator<i8>(input), std::istreambuf_iterator<i8>() };

	return true;
}

bool file::ExportFile(std::string_view output_file) const 
{
	std::ofstream output{ output_file.data() , std::ios::binary };

	if (!output) {
		return false;
	}

	output.write(m_file.data(), static_cast<std::streamsize>(m_file.size()));

	return true;
}
