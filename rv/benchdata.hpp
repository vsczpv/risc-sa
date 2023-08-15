#ifndef RSA_RV_BENCHDATA_HPP_
#define RSA_RV_BENCHDATA_HPP_

#include <rsa.hpp>
#include <filemgt/bitsfile.hpp>
#include <rv/opcode.hpp>

#include <map>

namespace rsa
{
	namespace rv
	{
		struct organization
		{
		private:

			bool m_valid = false;

		public:

			std::map <InstructionType, cycles> typeperf;
			double t_clock;

			organization(std::string org);

			[[nodiscard ("pure")]] auto is_valid(void) const noexcept -> bool;
		};

		struct result
		{
			cycles  total_elapsed;
			mcycles cycles_per_instruction;
			double  time_elapsed;
		};
	}
}

#endif // RSA_RV_BENCHDATA_HPP_
