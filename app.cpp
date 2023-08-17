#include <app.hpp>

#include <rv/program.hpp>
#include <rv/benchdata.hpp>

#include <optional>
#include <string>
#include <cstring>

using namespace rsa;

std::deque <rv::organization> rsa::organizations;
rv::program                   rsa::program;

auto parse_cmdline(int argc, char* argv[]) -> std::optional <std::string>
{

	/*
	 * risc-sa -o ORG PRG.txt
	 */
//	if (argc < 4) return "Not enough arguments";

	enum CmdState
	{
		OnDashAndProgramExpect,
		OnOrgExtract
	}
	state = OnDashAndProgramExpect;

	bool running = true;
	int  index   = 1;

	int  org_id = 0;
	bool has_a_program   = false;

	while (running)
	{

		auto& text = argv[index];

		switch (state)
		{
			case OnDashAndProgramExpect:
			{
				if (std::strcmp(text, "-o") == 0)
				{
					state = OnOrgExtract;
					break;
				}

				else if (text[0] == '-') return "Invalid argument";

				else
				{
					if (has_a_program)         return "Can only specify one program";

					has_a_program = true;
					rsa::program  = rv::program(text);

					if (!program.has_opened()) return "Could not open specified program";
				}
			}
			break;

			case OnOrgExtract:
			{

				rsa::organizations.push_back
				(
					rsa::rv::organization (std::string(text), org_id+1)
				);
				if (!rsa::organizations[org_id].is_valid()) return "Could not parse specified organization.";

				org_id++, state = OnDashAndProgramExpect;
			}
			break;
		}

		index++;
		if (index == argc) break;
	}

	if (has_a_program == false) return "You must specify a program.";
	if (org_id == 0)            return "You must specify atleast one organization.";

	return std::nullopt;
}
