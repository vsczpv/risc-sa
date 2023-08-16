#include <iostream>

#include <rsa.hpp>
#include <rv/program.hpp>
#include <rv/benchdata.hpp>

using namespace rsa;

auto rsa::main(int argc, char* argv[]) -> int
{

	(void) argc, (void) argv;

	auto program = rv::program ("examples/example3.txt");

	if (!program.has_opened())
	{
		std::cout << "Failed to open file." << std::endl;
		return EXIT_FAILURE;
	}

	auto org1 = rv::organization ("2:2:5:4:3:3:2.25", 1);
	auto org2 = rv::organization ("5:4:5:4:4:5:00.5", 2);

	if (!org1.is_valid() || !org2.is_valid())
	{
		std::cout << "Failed to load organization" << std::endl;
		return EXIT_FAILURE;
	}

	auto res1 = program.characterize_against(org1);
	auto res2 = program.characterize_against(org2);

	res1.print();
	res2.print();

	auto comp = rv::compare_results(res1, res2);

	std::printf("Organization %02i is the better one, on a ratio of %g to 1.\n", comp.second.source_id, comp.first);

    return EXIT_SUCCESS;
}
