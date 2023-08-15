#include <iostream>

#include <rsa.hpp>
#include <rv/program.hpp>
#include <rv/benchdata.hpp>

using namespace rsa::rv;

auto rsa::main(int argc, char* argv[]) -> int
{

	(void) argc, (void) argv;

	auto program = rv::program ("examples/example1.txt");

	if (!program.has_opened())
	{
		std::cout << "Failed to open file." << std::endl;
		return EXIT_FAILURE;
	}

	for (const auto& i : program.instructions())
	{
		std::cout << "Instruction " << i.string() << " of type " << i.type() << " has:";
		std::printf
		(
			"\n\t    OP: %02x"
			"\n\t    RD: %02u"
			"\n\t   RS1: %02u"
			"\n\t   RS2: %02u"
			"\n\tFUNCT3: %02x"
			"\n\tFUNCT7: %02x",
			i.OP(), i.RD(), i.RS1(), i.RS2(), i.FUNCT3(), i.FUNCT7()
		);
		std::cout << std::endl;
	}

	auto organization = rv::organization ("2:2:5:4:3:3:2.25");

	if (!organization.is_valid())
	{
		std::cout << "Failed to load organization" << std::endl;
		return EXIT_FAILURE;
	}

	for (const auto& t : organization.typeperf)
	{
		std::cout << t.first << ":" << t.second << std::endl;
	}
	std::cout << organization.t_clock << std::endl;

	auto result = program.characterize_against(organization);

	std::printf
	(
		"Program ran %u cycles, with total time elapsed of %gns @ %g CPI.\n",
		result.total_elapsed, result.time_elapsed, result.cycles_per_instruction
	);

    return EXIT_SUCCESS;
}
