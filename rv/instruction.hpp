#ifndef RSA_RV_INSTRUCTION_HPP_
#define RSA_RV_INSTRUCTION_HPP_

#include <cstdint>
#include <string_view>
#include <rv/opcode.hpp>

namespace rsa
{
	namespace rv
	{

		constexpr uint32_t OPCODE_MASK      = 0b0000000'00000'00000'000'00000'1111111;
		constexpr uint32_t REGISTER_D_MASK  = 0b0000000'00000'00000'000'11111'0000000;
		constexpr uint32_t REGISTER_S1_MASK = 0b0000000'00000'11111'000'00000'0000000;
		constexpr uint32_t REGISTER_S2_MASK = 0b0000000'11111'00000'000'00000'0000000;
		constexpr uint32_t FUNCT3_MASK      = 0b0000000'00000'00000'111'00000'0000000;
		constexpr uint32_t FUNCT7_MASK      = 0b1111111'00000'00000'000'00000'0000000;

		constexpr std::size_t OPCODE_SHIFT      = 0;
		constexpr std::size_t REGISTER_D_SHIFT  = 7;
		constexpr std::size_t REGISTER_S1_SHIFT = 15;
		constexpr std::size_t REGISTER_S2_SHIFT = 20;
		constexpr std::size_t FUNCT3_SHIFT      = 12;
		constexpr std::size_t FUNCT7_SHIFT      = 26;

		class instruction
		{
		private:

			std::string_view m_string;
			uint32_t m_value;
			uint32_t m_immd;

			InstructionType m_type;

		public:

			instruction(void) noexcept {}
			instruction(std::string_view filedata, std::string_view::iterator& at);

			[[nodiscard ("getter")]] auto OP(void)     const noexcept -> uint8_t;
			[[nodiscard ("getter")]] auto RD(void)     const noexcept -> uint8_t;
			[[nodiscard ("getter")]] auto RS1(void)    const noexcept -> uint8_t;
			[[nodiscard ("getter")]] auto RS2(void)    const noexcept -> uint8_t;
			[[nodiscard ("getter")]] auto FUNCT3(void) const noexcept -> uint8_t;
			[[nodiscard ("getter")]] auto FUNCT7(void) const noexcept -> uint8_t;

			[[nodiscard ("getter")]] auto IMMD(void)   const noexcept -> uint32_t;

			[[nodiscard ("getter")]] auto value(void)  const noexcept -> uint32_t;
			[[nodiscard ("getter")]] auto string(void) const noexcept -> std::string_view;
			[[nodiscard ("getter")]] auto type(void)   const noexcept -> InstructionType;

			~instruction() = default;
		};
	}
}

#endif // RSA_RV_INSTRUCTION_HPP_
