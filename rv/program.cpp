/*
 * This file is part of risc-sa, an RISC-V RV32I static performance analyzer,
 * made with intention of being university homework. This program has no legal
 * ties to the University of Itajaí Vale, SC, Brazil.
 *
 * Copyright © 2023 Vinícius Schütz Piva
 *
 * risc-sa is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>
 *
 */

#include <rv/program.hpp>
#include <app.hpp>

#include <string_view>

using namespace rsa;
using namespace rsa::rv;

NoParse_t rsa::rv::NoParse;

rsa::rv::program::program(void) : m_file("") {}
rsa::rv::program::program(std::string_view filename)

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

rsa::rv::program::program(std::string_view filename, NoParse_t) : m_file(filename) {}

auto rsa::rv::program::characterize_against(rv::organization& org) const noexcept -> rv::result
{

	rv::result res = { .source_id = org.id };

	if (rsa::characterize_as_pipline)
	{
		/*
		 * Pipelined instructions take the same amount of time, plus the constant
		 * pipeline width
		 */
		res.total_elapsed = 5 + (this->m_instructions.size() - 1);
	}

	else
	{
		for (const auto& i : this->m_instructions) res.total_elapsed += org.typeperf[i.type()];
	}

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

auto rsa::rv::program::push_instruction(instruction ins) noexcept -> void
{
	this->m_instructions.push_back(ins);
}

[[nodiscard ("getter")]] auto rsa::rv::program::mut_instructions(void) -> std::vector <instruction>&
{
	return this->m_instructions;
}

auto rsa::rv::program::clear_nops(void) -> void
{
	std::erase_if(this->m_instructions, [] (instruction i) -> bool
	{
		if (i.value() == rv::NOP_INSTRUCTION) return true;
		else                                  return false;
	});
}
