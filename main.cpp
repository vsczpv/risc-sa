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

    return EXIT_SUCCESS;
}
