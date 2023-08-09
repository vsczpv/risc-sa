#include <iostream>

#include <rsa.hpp>
#include <rv/instruction.hpp>
#include <filemgt/bitsfile.hpp>

#include <string>
#include <string_view>
#include <vector>

using namespace rsa::rv;

auto rsa::main(int argc, char* argv[]) -> int
{

	(void) argc, (void) argv;

	auto file = filemgt::bitsfile ("examples/example1.txt");
	auto data = file.data();

	std::vector <instruction> insts;
	{
		auto newline_count = 0lu;
		for (auto c : data) if (c == '\n') newline_count++;
		insts.reserve(newline_count);
	}

	auto data_view = std::string_view (data);
	auto data_iter = data_view.begin();

	while (data_iter != data_view.cend()) insts.push_back(instruction(data_view, data_iter));

	for (const auto& i : insts)
		std::cout << "Instruction " << i.string() << " has value of " << i.value() << ", OP is " << (int) i.OP() << std::endl;

    return EXIT_SUCCESS;
}
