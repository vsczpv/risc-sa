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

#ifndef RSA_RV_PROGRAM_HPP_
#define RSA_RV_PROGRAM_HPP_

#include <filemgt/bitsfile.hpp>
#include <rv/instruction.hpp>
#include <rv/benchdata.hpp>

#include <span>
#include <map>

namespace rsa
{
	namespace rv
	{
		class program
		{
		private:

			rsa::filemgt::bitsfile m_file;
			std::vector <instruction> m_instructions;

		public:

			program();
			program(std::string_view filename);

			auto characterize_against(rv::organization& org) const noexcept -> rv::result;

			[[nodiscard ("getter")]] auto instructions(void) const noexcept -> std::span <const instruction>;
			[[nodiscard ("pure")]]   auto has_opened(void)   const noexcept -> bool;

		};
	}
}

#endif // RSA_RV_PROGRAM_HPP_
