#include <filemgt/bitsfile.hpp>

#include <sstream>

using namespace rsa::filemgt;

rsa::filemgt::bitsfile::bitsfile(std::string_view filename) :

	m_file_backend(filename.data())

{

	std::stringstream stream;

	stream << this->m_file_backend.rdbuf();

	this->m_direct_data = stream.str();

	return;
}

[[nodiscard ]] auto rsa::filemgt::bitsfile::data(void) const noexcept -> std::string_view
{
	return this->m_direct_data;
}

[[nodiscard]] auto rsa::filemgt::bitsfile::has_opened(void) const noexcept -> bool
{
	return this->m_file_backend.is_open();
}
