#include <rv/benchdata.hpp>
#include <rv/opcode.hpp>

using namespace rsa::rv;

rsa::rv::organization::organization(std::string org)
{

	auto count = 0ul;
	for (auto c : org) if (c == ':') count++;

	if (count != 6) return;

	InstructionType current_type = InsT_R;

	char* at = org.data();

	while (count != 0)
	{
		char* next;

		this->typeperf[current_type] = strtol(at, &next, 0);

		if (at == next) break;

		at = next;

		if (*at == ':') at++; else break;

		current_type++, count--;
	}

	if (count != 0) return;

	this->t_clock = strtod(at, NULL);
	this->m_valid = true;
}
