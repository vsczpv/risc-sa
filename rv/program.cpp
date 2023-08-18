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

#include <string_view>

using namespace rsa;
using namespace rsa::rv;

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

auto rsa::rv::program::characterize_against(rv::organization& org) const noexcept -> rv::result
{

	rv::result res = { .source_id = org.id };

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
