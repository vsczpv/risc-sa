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

#ifndef RSA_FILEMGT_BITSFILE_HPP_
#define RSA_FILEMGT_BITSFILE_HPP_

#include <string>
#include <fstream>
#include <string_view>

namespace rsa
{
	namespace filemgt
	{
		class bitsfile
		{
		private:
			std::ifstream m_file_backend;
			std::string   m_direct_data;

		public:
			bitsfile (std::string_view filename);
			bitsfile (bitsfile&& that);

			[[nodiscard ("getter")]] auto data(void)       const noexcept -> std::string_view;
			[[nodiscard ("pure")]]   auto has_opened(void) const noexcept -> bool;

			bitsfile& operator=(bitsfile&& that);

			~bitsfile() = default;
		};
	}
}

#endif // RSA_FILEMGT_BITSFILE_HPP_
