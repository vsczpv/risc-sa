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

#include <iostream>
#include <algorithm>

#include <app.hpp>
#include <rv/optimize.hpp>

using namespace rsa;

auto rsa::main(int argc, char* argv[]) -> int
{

	auto error = rsa::parse_cmdline(argc, argv);

	if (error)
	{
		std::cerr << *error << std::endl;
		return EXIT_FAILURE;
	}

	if (rsa::mode == Characterize) rsa::characterize();
	else                           rsa::optimize();

    return EXIT_SUCCESS;
}
