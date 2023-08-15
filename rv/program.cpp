#include <rv/program.hpp>

#include <string_view>

using namespace rsa;
using namespace rsa::rv;

rsa::rv::program::program (std::string_view filename)

	: m_file(filename)

{

	auto data = this->m_file.data();

	auto newline_count = 0lu;
	for (auto c : data) if (c == '\n') newline_count++;
	this->m_instructions.reserve(newline_count);

	auto data_view = std::string_view (data);
	auto data_iter = data_view.begin();

	while (data_iter != data_view.cend()) this->m_instructions.push_back(instruction(data_view, data_iter));

}

auto rsa::rv::program::characterize_against(rv::organization& org) const noexcept -> rv::result
{

	rv::result res = { 0 };

	for (const auto& i : this->m_instructions) res.total_elapsed += org.typeperf[i.type()];

	res.time_elapsed = res.total_elapsed * org.t_clock;
	res.cycles_per_instruction = (double) res.total_elapsed / (double) this->m_instructions.size();

	return res;
}

[[nodiscard]] auto rsa::rv::program::instructions(void) const noexcept -> std::span <const instruction>
{
	return this->m_instructions;
}

[[nodiscard]] auto rsa::rv::program::has_opened(void) const noexcept -> bool
{
	return this->m_file.has_opened();
}
