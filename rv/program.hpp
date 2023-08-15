#ifndef RSA_RV_PROGRAM_HPP_
#define RSA_RV_PROGRAM_HPP_

#include <filemgt/bitsfile.hpp>
#include <rv/instruction.hpp>

#include <span>

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

			program(std::string_view filename);

			[[nodiscard ("getter")]] auto instructions(void) const noexcept -> std::span <const instruction>;

			[[nodiscard ("pure")]]   auto has_opened(void)   const noexcept -> bool;

		};
	}
}

#endif // RSA_RV_PROGRAM_HPP_
