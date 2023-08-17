#include <iostream>
#include <algorithm>

#include <app.hpp>

using namespace rsa;

auto rsa::main(int argc, char* argv[]) -> int
{

	auto error = rsa::parse_cmdline(argc, argv);

	if (error)
	{
		std::cerr << *error << std::endl;
		return EXIT_FAILURE;
	}

	for (auto& o : rsa::organizations) rsa::results.push_back
	(
		rsa::program.characterize_against(o)
	);

	for (auto& r : rsa::results) r.print();

	std::cout << std::endl;

	for (auto& a : rsa::results) for (auto& b : rsa::results)
	{
		if (a.source_id == b.source_id) continue;
		if (b.seen)                     continue;

		auto comp = rv::compare_results(a, b);

		std::printf
		(
			"%02i vs %02i : Organization %02i is better by a factor of %g.\n",
			a.source_id, b.source_id,
			comp.second.source_id, comp.first
		);

		a.seen = true;
	}

    return EXIT_SUCCESS;
}
