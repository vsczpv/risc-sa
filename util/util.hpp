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

#ifndef RSA_UTIL_UTIL_HPP_
#define RSA_UTIL_UTIL_HPP_

#include <tuple>
#include <vector>

#include <iostream>

#define VT_BOLD      "\033[1m"
#define VT_UNDERLINE "\033[4m"

#define VT_END       "\033[0m"

namespace util
{
	template <typename T> class lookup_table
	{
	private:
		std::vector <T> m_elements;
	public:
		lookup_table(void) {}
		lookup_table(std::initializer_list<std::tuple<T, std::size_t>> elems, T def, std::size_t highest_item)
		{

			this->m_elements.resize(highest_item);
			for (std::size_t i = 0; i < highest_item; i++) this->m_elements[i] = def;

			for (auto& e : elems)
			{
				auto& [first, second] = e;
				this->m_elements[second] = first;
			}

		}
		~lookup_table() = default;

		T& operator[] (unsigned long long int i) { return this->m_elements[i]; }
	};
}

#endif // RSA_UTIL_UTIL_HPP_
