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

#ifndef RSA_APP_HPP_
#define RSA_APP_HPP_

#include <rv/program.hpp>
#include <rv/benchdata.hpp>

#include <deque>
#include <optional>
#include <string>

namespace rsa
{

	enum Mode
	{
		Characterize,
		Optimize
	};

	enum HazardsMode
	{
		InsertOnly = 0,
		Foward     = 1,
		Reorder    = 2,
		Both       = 3
	};

	extern std::deque <rv::result>       results;
	extern std::deque <rv::organization> organizations;
	extern rv::program  program;
	extern std::ofstream output;
	extern Mode mode;
	extern HazardsMode hzmode;
	extern bool characterize_as_pipline;

	auto parse_cmdline(int argc, char* argv[]) -> std::optional <std::string>;
}

#endif // RSA_APP_HPP_
