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

#include <filemgt/bitsfile.hpp>

#include <sstream>

using namespace rsa::filemgt;

rsa::filemgt::bitsfile::bitsfile (bitsfile&& that)
{

	this->m_file_backend = std::move (that.m_file_backend);
	this->m_direct_data  = std::move (that.m_direct_data);

	return;
}

bitsfile& rsa::filemgt::bitsfile::operator=(bitsfile&& that)
{

	this->m_file_backend = std::move (that.m_file_backend);
	this->m_direct_data  = std::move (that.m_direct_data);

	return *this;
}

rsa::filemgt::bitsfile::bitsfile(std::string_view filename) :

	m_file_backend(filename.data())

{

	if ( !bitsfile::has_opened() ) return;

	std::stringstream stream;

	stream << this->m_file_backend.rdbuf();

	this->m_direct_data = stream.str();

	return;
}

[[nodiscard]] auto rsa::filemgt::bitsfile::data(void) const noexcept -> std::string_view
{
	return this->m_direct_data;
}

[[nodiscard]] auto rsa::filemgt::bitsfile::has_opened(void) const noexcept -> bool
{
	return this->m_file_backend.is_open();
}
