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

			const int id;

			organization(std::string org, int id);

			[[nodiscard ("pure")]] auto is_valid(void) const noexcept -> bool;
		};

		struct result
		{

			const int source_id;

			cycles  total_elapsed;
			mcycles cycles_per_instruction;
			double  time_elapsed;

			auto print(void) -> void;

			friend auto compare_results(result& a, result& b) -> std::pair <double, result&>;

			bool seen = false;
		};

		auto compare_results(result& a, result& b) -> std::pair <double, result&>;
	}
}

#endif // RSA_RV_BENCHDATA_HPP_
