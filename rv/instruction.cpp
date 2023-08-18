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

#include <rv/instruction.hpp>

#include <string>

#include <iostream>

using namespace rsa::rv;

rsa::rv::instruction::instruction(std::string_view filedata, std::string_view::iterator& at)
{

	/* Load bits */

	auto end_it = at;
	while (*end_it != '\n' && *end_it != '\r' && end_it != filedata.cend()) end_it++;

	this->m_string = std::string_view (at, end_it);

	if (*end_it == '\r' || *end_it == '\n') end_it++;
	at = end_it;

	this->m_value = std::stol(this->m_string.data(), nullptr, 2);
	this->m_type = rsa::rv::opcode2type::get()[OP()];

	/* Extract immediate */

	// TODO

	return;
}

[[nodiscard]] auto rsa::rv::instruction::OP(void)     const noexcept -> uint8_t { return (this->m_value & OPCODE_MASK)      >> OPCODE_SHIFT;      }
[[nodiscard]] auto rsa::rv::instruction::RD(void)     const noexcept -> uint8_t { return (this->m_value & REGISTER_D_MASK)  >> REGISTER_D_SHIFT;  }
[[nodiscard]] auto rsa::rv::instruction::RS1(void)    const noexcept -> uint8_t { return (this->m_value & REGISTER_S1_MASK) >> REGISTER_S1_SHIFT; }
[[nodiscard]] auto rsa::rv::instruction::RS2(void)    const noexcept -> uint8_t { return (this->m_value & REGISTER_S2_MASK) >> REGISTER_S2_SHIFT; }
[[nodiscard]] auto rsa::rv::instruction::FUNCT3(void) const noexcept -> uint8_t { return (this->m_value & FUNCT3_MASK)      >> FUNCT3_SHIFT;      }
[[nodiscard]] auto rsa::rv::instruction::FUNCT7(void) const noexcept -> uint8_t { return (this->m_value & FUNCT7_MASK)      >> FUNCT7_SHIFT;      }

[[nodiscard]] auto rsa::rv::instruction::IMMD(void)   const noexcept -> uint32_t
{
	return this->m_immd;
}

[[nodiscard]] auto rsa::rv::instruction::value(void) const noexcept -> uint32_t
{
	return this->m_value;
}

[[nodiscard]] auto rsa::rv::instruction::string(void) const noexcept -> std::string_view
{
	return this->m_string;
}

[[nodiscard]] auto rsa::rv::instruction::type(void) const noexcept -> InstructionType
{
	return this->m_type;
}
