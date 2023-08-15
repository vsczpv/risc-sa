#include <rv/opcode.hpp>

using namespace rsa::rv;

InstructionType rsa::rv::operator++(InstructionType& type)
{
	type = static_cast<InstructionType>( (type + 1) % InsT_Inval);
	return type;
}

InstructionType rsa::rv::operator++(InstructionType& type, int)
{
	auto res = type;
	++type;
	return res;
}
