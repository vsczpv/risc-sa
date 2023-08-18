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

#ifndef RSA_RV_BENCHDATA_HPP_
#define RSA_RV_BENCHDATA_HPP_

#include <rsa.hpp>
#include <filemgt/bitsfile.hpp>
#include <rv/opcode.hpp>

#include <map>

namespace rsa
{
	namespace rv
	{
		struct organization
		{
		private:

			bool m_valid = false;

		public:

			std::map <InstructionType, cycles> typeperf;
			double t_clock;

			const int id;

			organization(std::string org, int id);

			[[nodiscard ("pure")]] auto is_valid(void) const noexcept -> bool;
		};

		struct result
		{

			const int source_id;

			cycles  total_elapsed;
			mcycles cycles_per_instruction;
			double  time_elapsed;

			auto print(void) -> void;

			friend auto compare_results(result& a, result& b) -> std::pair <double, result&>;

			bool seen = false;
		};

		auto compare_results(result& a, result& b) -> std::pair <double, result&>;
	}
}

#endif // RSA_RV_BENCHDATA_HPP_
