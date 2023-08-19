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

#include <rv/benchdata.hpp>
#include <rv/opcode.hpp>

using namespace rsa::rv;

rsa::rv::organization::organization(std::string org, int id)

	: id(id)

{

	auto count = 0ul;
	for (auto c : org) if (c == ':') count++;

	if (count != InsT_amount) return;

	InstructionType current_type = InsT_R;

	char* at = org.data();

	while (count != 0)
	{
		char* next;

		this->typeperf[current_type] = strtol(at, &next, 0);

		if (at == next) break;

		at = next;

		if (*at == ':') at++; else break;

		current_type++, count--;
	}

	if (count != 0) return;

	this->t_clock = strtod(at, NULL);
	this->m_valid = true;
}

[[nodiscard]] auto rsa::rv::organization::is_valid(void) const noexcept -> bool
{
	return this->m_valid;
}

auto rsa::rv::result::print(void) -> void
{
	std::printf
	(
		"Organization %02i : Program ran %u cycles, with total time elapsed of %gns @ %g CPI.\n",
		this->source_id,
		this->total_elapsed, this->time_elapsed, this->cycles_per_instruction
	);
}

auto rsa::rv::compare_results(result& a, result& b) -> std::pair <double, result&>
{

	auto r_a = 1.f / a.time_elapsed;
	auto r_b = 1.f / b.time_elapsed;

	if (r_a > r_b) return {r_a / r_b, a};
	else           return {r_b / r_a, b};

}
