#ifndef RSA_RV_INSTRUCTION_HPP_
#define RSA_RV_INSTRUCTION_HPP_

#include <cstdint>
#include <string_view>

namespace rsa
{
	namespace rv
	{
		class instruction
		{
		private:

			std::string_view m_string;
			uint32_t m_value;
			uint32_t m_immd;

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

			~instruction() = default;
		};
	}
}

#endif // RSA_RV_INSTRUCTION_HPP_
