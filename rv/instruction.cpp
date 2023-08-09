#include <rv/instruction.hpp>

#include <string>

using namespace rsa::rv;

rsa::rv::instruction::instruction(std::string_view filedata, std::string_view::iterator& at)
{

	/* Load bits */

	auto end_it = at;
	while (*end_it != '\n' && *end_it != '\r' && end_it != filedata.cend()) end_it++;

	this->m_string = std::string_view (at, end_it);

	if (*end_it == '\r' || *end_it == '\n') end_it++;
	at = end_it;

	this->m_value = std::stol(this->m_string.data(), nullptr, 2);

	/* Extract immediate */



	return;
}

[[nodiscard]] auto rsa::rv::instruction::OP(void) const noexcept -> uint8_t
{
	return this->m_value & 0b1111111;
}

[[nodiscard]] auto rsa::rv::instruction::value(void) const noexcept -> uint32_t
{
	return this->m_value;
}

[[nodiscard]] auto rsa::rv::instruction::string(void) const noexcept -> std::string_view
{
	return this->m_string;
}
