#include <app.hpp>
#include <util/util.hpp>

#include <rv/program.hpp>
#include <rv/benchdata.hpp>

#include <optional>
#include <string>
#include <cstring>

using namespace rsa;

std::deque <rv::result>       rsa::results;
std::deque <rv::organization> rsa::organizations;
rv::program                   rsa::program;

[[nodiscard ("pure")]] static std::string usage(void)
{
	return "\n"
		   "Usage: " VT_BOLD "risc-sa" VT_END " {-o " VT_UNDERLINE "<ORG>" VT_END "} ... " VT_UNDERLINE "PROGRAM" VT_END "\n"
		   "\n"
		   "       -o <ORG>     Specifies which organization(s) to use in the benchmark;\n"
		   "\n"
		   "                    The format specified must be in the following format:\n"
		   "\n"
		   "                        R:I:S:B:U:J:TCLK\n"
		   "\n"
		   "                    Where all but TCLK are integer values of how much clockcycles the referred ins-\n"
		   "                    truction format takes to execute, and TCLK is a decimal value of how long it takes\n"
		   "                    for a clock to cycle, in nanoseconds. For example:\n"
		   "\n"
		   "                        2:2:5:4:3:3:2.25\n"
		   "\n"
		   "                    Will specify an organization which takes 2.25 nanoseconds per clock, 2 clocks for\n"
		   "                    R typpe, 2 for I type, 5 for S type, 4 for B type, 3 for U type and 3 for J type.\n"
		   "\n"
		   "                    You must specify atleast" VT_BOLD " one " VT_END "organization.\n"
		   "\n"
		   "       -h | --help  Displays this prompt.\n"
		   "\n"
		   "       --version    Displays version and copyright information.\n"
		   "\n"
		   "    PROGRAM must be a path to a valid, binary-in-ASCII encoded RV32I program.\n"
		   "    The numbers in <ORG> can be any digit readable by strtol(3) [integers] and strtod(3) [floats].\n"
		   "\n"
		   "Ex.:   risc-sa -o 2:2:5:4:3:3:2.25 program.txt\n"
		   "       risc-sa examples/example3.txt -o 2:2:5:4:3:3:2.25 -o 5:4:5:4:4:5:00.5 -o 1:1:1:1:1:1:15.0"
		   "\n"
	;
}

[[nodiscard ("pure")]] static std::string version(void)
{
	return "risc-sa, version " VERSION "\n"
	       "Copyright (C) 2023 Vinícius Schütz Piva\n"
		   "Licensed under GNU GPL-3-or-later <http://gnu.org/licenses/gpl.html>\n"
		   "\n"
		   "This is free software; you are free to change and redistribute it.\n"
		   "There is NO WARRANTY, to the extent permitted by law."
	;
}

[[nodiscard]] auto rsa::parse_cmdline(int argc, char* argv[]) -> std::optional <std::string>
{

	if (argc < 2) return "Error: Not enough arguments" + usage();

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

				else if (std::strcmp(text, "-h") == 0 || std::strcmp(text, "--help") == 0)
					return "" + usage();

				else if (std::strcmp(text, "--version") == 0)
					return "" + version();

				else if (text[0] == '-')
					return "Error: Invalid argument." + usage();

				else
				{
					if (has_a_program)         return "Error: Can only specify one program." + usage();

					has_a_program = true;
					rsa::program  = rv::program(text);

					if (!program.has_opened()) return "Error: Could not open specified program.";
				}
			}
			break;

			case OnOrgExtract:
			{

				rsa::organizations.push_back
				(
					rsa::rv::organization (std::string(text), org_id+1)
				);
				if (!rsa::organizations[org_id].is_valid()) return "Error: Could not parse specified organization." + usage();

				org_id++, state = OnDashAndProgramExpect;
			}
			break;
		}

		index++;
		if (index == argc) break;
	}

	if (has_a_program == false) return "You must specify a program."                + usage();
	if (org_id == 0)            return "You must specify atleast one organization." + usage();

	return std::nullopt;
}
